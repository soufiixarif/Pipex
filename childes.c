/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 00:59:52 by sarif             #+#    #+#             */
/*   Updated: 2024/03/26 03:23:22 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	childone(int *fd, int infile, char **av)
{
	char	**commande;
	char	*pathline;
	char	*line;

	commande = ft_split(av[2], ' ');
	pathline = ft_getenv("PATH=");
	line = getlinepath(pathline, *commande);
	close(fd[0]);
	dup2(infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	execve(line, commande, environ);
}

void	childtwo(int *fd, int outfile, char **av)
{
	char	**commande2;
	char	*pathline;
	char	*line2;

	commande2 = ft_split(av[3], ' ');
	pathline = ft_getenv("PATH=");
	line2 = getlinepath(pathline, *commande2);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(fd[0]);
	execve(line2, commande2, environ);
}

void	printerror(char *bash, char *commande)
{
	write(1, &bash, ft_strlen(bash));
	write(1, ": ", 2);
	write(1, &commande, ft_strlen(commande));
	write(1, ": ", 2);
	write(1, "command not found", 18);
}
