/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 22:11:25 by sarif             #+#    #+#             */
/*   Updated: 2024/05/09 16:55:48 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	pipex(int infile, int outfile, char **av)
{
	int		fd[2];
	pid_t	pid;
	pid_t	pid2;

	pipe(fd);
	pid = fork();
	if (pid == 0)
		childone(fd, infile, av);
	else
	{
		pid2 = fork();
		if (pid2 == 0)
			childtwo(fd, outfile, av);
		else
		{
			close(fd[0]);
			close(fd[1]);
			waitpid(pid, NULL, 0);
			waitpid(pid2, NULL, 0);
		}
	}
}

int	main(int ac, char **av)
{
	int	infile;
	int	outfile;

	if (!environ || !*environ)
		return (0);
	if (ac == 5)
	{
		infile = open(av[1], O_RDONLY);
		if (infile == -1)
			printfderror(av[0], av[1]);
		outfile = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (outfile == -1)
			return (close(infile), 0);
		pipex(infile, outfile, av);
		close(infile);
		close(outfile);
	}
	else
	{
		write(2, "Error: args error", 18);
	}
}
