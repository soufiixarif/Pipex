/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:14:58 by sarif             #+#    #+#             */
/*   Updated: 2024/04/30 15:58:45 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	execute_cmd(int *fd, char *commande, char **env)
{
	char	**cmd;
	char	*pathline;
	char	*line;

	printf("dkhalt l execute cmd\n");
	cmd = ft_split(commande, ' ');
	printf("%s\n",cmd[0]);
	pathline = ft_getenv("PATH=", env);
	pathline += 5;
	line = getlinepath(pathline, *cmd);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	if (execve(line, cmd, env) == -1)
	{
		ft_2dfree(cmd);
		free(line);
		perror("Error: ");
	}
}

void	pipex(int infile, int outfile, char **av, char **env)
{
	int		i;
	int		argc;
	int		fd[2];
	pid_t	pid;
	int		fdd;

	i = 2;
	fdd = 20;
	argc = ft_argvcounter(av);
	while (i <= (argc - 2))
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			printf("dkhalt l child\n");
			if (i == 2)
			{
				dup2(infile, STDIN_FILENO);
				close(infile);
			}
			else
				dup2(fd[0], STDIN_FILENO);
			if (i == argc - 2)
				dup2(fd[1], outfile);
			else
				dup2(fd[1], STDOUT_FILENO);
			close (fd[1]);
			close (fd[0]);
			execute_cmd(fd, av[i], env);
		}
		dup2(fd[1],fdd);
		i++;
	}
}

int	main(int ac, char **av, char **env)
{
	int	outfile;
	int	infile;

	infile = open(av[1], O_RDONLY);
	if (infile == -1)
		return (0); // print error
	outfile = open (av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (outfile == -1)
		return (close(infile), 0);
	pipex (infile, outfile, av, env);
	while (wait(NULL) != -1);
	close(infile);
	close(outfile);
}
