/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:36:51 by sarif             #+#    #+#             */
/*   Updated: 2024/05/09 17:39:34 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	put_stderr(char *s)
{
	int	fd;

	fd = 2;
	while (*s)
		(write(fd, s, 1), s++);
}

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
