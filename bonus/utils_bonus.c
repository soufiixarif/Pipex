/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:36:51 by sarif             #+#    #+#             */
/*   Updated: 2024/05/14 19:46:52 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*getlinepath(char *path, char *commande)
{
	char	**envpath;
	char	*com;
	int		i;

	i = 0;
	if (ft_strchr(commande, '/') != NULL)
		return (ft_strdup(commande));
	envpath = ft_split(path, ':');
	while (envpath[i])
	{
		com = ft_calloc(ft_strlen(envpath[i]) + ft_strlen(commande) + 2, 1);
		if (!com)
			return (NULL);
		com = ft_strcpy(com, envpath[i]);
		com = ft_strcat(com, "/");
		com = ft_strcat(com, commande);
		if (access(com, F_OK) == 0)
			return (com);
		free(com);
		i++;
	}
	put_stderr(commande);
	put_stderr(" : commande not found\n");
	exit(1);
	return (NULL);
}

char	*ft_getenv(char *var)
{
	char	*tmp;
	int		i;

	i = 0;
	while (environ[i])
	{
		tmp = ft_strdup(environ[i]);
		if (ft_strncmp(var, environ[i], ft_strlen(var)) == 0)
			return (tmp);
		free(tmp);
		i++;
	}
	return (NULL);
}

int	ft_2dfree(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		s[i] = NULL;
		i++;
	}
	free(s);
	s = NULL;
	return (0);
}

void	printfderror(char *bash, char *infile)
{
	write(2, bash, ft_strlen(bash));
	write(2, ": ", 2);
	write(2, infile, ft_strlen(infile));
	write(2, ": ", 2);
	write(2, "permission denied or file not found\n", 36);
}

void	if_heredoc_or_not(int ac, char **av, t_data *d)
{
	d->hrdc = false;
	d->outfile = open (av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (d->outfile == -1)
		return ;
	if (!ft_strncmp(av[1], "here-doc", ft_strlen("here-doc")))
		here_doc_handler(d, av, ac);
	else
	{
		d->infile = open(av[1], O_RDONLY);
		if (d->infile == -1)
			printfderror(av[0], av[1]);
		pipex (d, av, ac);
	}
	free(d);
	close(d->infile);
	close(d->outfile);
}