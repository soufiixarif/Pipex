/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 00:59:52 by sarif             #+#    #+#             */
/*   Updated: 2024/05/09 16:52:47 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	childone(int *fd, int infile, char **av)
{
	char	**commande;
	char	*pathline;
	char	*line;

	commande = ft_split(av[2], ' ');
	if (!commande)
		return ;
	pathline = ft_getenv("PATH=");
	if (!pathline && !ft_2dfree(commande))
		return ;
	line = getlinepath(pathline + 5, *commande);
	if (!line && !ft_2dfree(commande))
		printerror(av[0], commande[0]);
	close(fd[0]);
	dup2(infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	if (execve(line, commande, environ) == -1)
	{
		ft_2dfree(commande);
		free(line);
		free(pathline);
		perror("Error: ");
		exit(EXIT_FAILURE);
	}
}

void	childtwo(int *fd, int outfile, char **av)
{
	char	**commande2;
	char	*pathline;
	char	*line2;

	commande2 = ft_split(av[3], ' ');
	if (!commande2)
		return ;
	pathline = ft_getenv("PATH=");
	if (!pathline && !ft_2dfree(commande2))
		return ;
	pathline += 5;
	line2 = getlinepath(pathline, *commande2);
	if (!line2)
		printerror(av[0], commande2[0]);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(fd[0]);
	if (execve(line2, commande2, environ) == -1)
	{
		ft_2dfree(commande2);
		free(line2);
		perror("Error: ");
		exit(EXIT_FAILURE);
	}
}

void	printerror(char *bash, char *commande)
{
	write(2, bash, ft_strlen(bash));
	write(2, ": ", 2);
	write(2, commande, ft_strlen(commande));
	write(2, ": ", 2);
	write(2, "command not found\n", 19);
	exit(EXIT_FAILURE);
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
