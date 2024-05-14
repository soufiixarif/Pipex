/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:14:58 by sarif             #+#    #+#             */
/*   Updated: 2024/05/14 19:48:39 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	here_doc_handler(t_data *d, char **av, int ac)
{
	char	*line;

	d->hrdc = true;
	pipe(d->fd);
	while (1)
	{
		line = get_next_line(0);
		(line != NULL) && (line[ft_strlen(line) - 1] = '\0');
		if (!line || !ft_strcmp(line, av[2]))
		{
			free (line);
			break ;
		}
		write(d->fd[1], line, ft_strlen(line));
		write(d->fd[1], "\n", 1);
		free(line);
	}
	close(d->fd[1]);
	d->infile = d->fd[0];
	pipex(d, av, ac);
}

void	redirectpipes(t_data *d, int i, int ac)
{
	if (d->hrdc && i == 3)
	{
		dup2(d->infile, STDIN_FILENO);
	}
	else if (!d->hrdc && i == 2)
		dup2(d->infile, STDIN_FILENO);
	else
		dup2(d->fdd, STDIN_FILENO);
	if (i == ac - 2)
		dup2(d->outfile, STDOUT_FILENO);
	else
		dup2(d->fd[1], STDOUT_FILENO);
	close(d->fd[0]);
}

void	execute_cmd(char *commande)
{
	char	**cmd;
	char	*pathline;
	char	*line;

	cmd = ft_split(commande, ' ');
	if (!cmd)
		return ;
	pathline = ft_getenv("PATH=");
	if (!pathline && !ft_2dfree(cmd))
		return ;
	line = getlinepath(pathline + 5, *cmd);
	if (!line && !ft_2dfree(cmd))
		return (free(pathline));
	if (execve(line, cmd, environ) == -1)
	{
		ft_2dfree(cmd);
		free(line);
		free(pathline);
		perror("Error: ");
		exit(1);
	}
}

void	pipex(t_data *d, char **av, int ac)
{
	int		i;
	pid_t	pid;

	i = 2;
	if (d->hrdc)
		i++;
	while (i < (ac - 1))
	{
		pipe(d->fd);
		pid = fork();
		if (pid == 0)
		{
			redirectpipes(d, i, ac);
			execute_cmd(av[i]);
		}
		else
		{
			wait(NULL);
			close(d->fd[1]);
			d->fdd = d->fd[0];
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data	*d;

	if (!environ || !*environ)
		return (0);
	if (ac >= 5)
	{
		d = malloc(sizeof(t_data));
		if (!d)
			return (1);
		if_heredoc_or_not(ac, av, d);
	}
	else
	{
		write(2, "Error: args error", 18);
	}
}
