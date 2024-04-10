/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 00:59:52 by sarif             #+#    #+#             */
/*   Updated: 2024/04/08 22:06:04 by sarif            ###   ########.fr       */
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
	pathline += 5;
	line = getlinepath(pathline, *commande);
	if (!line)
		printerror(av[0], commande[0]);
	close(fd[0]);
	dup2(infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	if (execve(line, commande, environ) == -1)
	{
		ft_2dfree(commande);
		free(line);
		// free(pathline);
		perror("Error: ");
	}

}

void	childtwo(int *fd, int outfile, char **av)
{
	char	**commande2;
	char	*pathline;
	char	*line2;

	commande2 = ft_split(av[3], ' ');
	pathline = ft_getenv("PATH=");
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
		//free(pathline);
		perror("Error: ");
	}
}

void	printerror(char *bash, char *commande)
{
	write(1, bash, ft_strlen(bash));
	write(1, ": ", 2);
	write(1, commande, ft_strlen(commande));
	write(1, ": ", 2);
	write(1, "command not found\n", 19);
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
