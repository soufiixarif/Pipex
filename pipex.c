/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 22:11:25 by sarif             #+#    #+#             */
/*   Updated: 2024/03/23 14:09:52 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
char *getlinepath(char *path, char *commande)
{
	char **envpath = ft_split(path,':');
	char *com;
	int i = 0;
	while (envpath[i])
	{
		com = malloc(ft_strlen(envpath[i]) + ft_strlen(commande) + 2);
		com = ft_strcpy(com ,envpath[i]);
		com = ft_strcat(com ,"/");
		com = ft_strcat(com ,commande);
		if (access(com,F_OK) == 0)
			return(com);
		free(com);
		i++;
	}
	return (NULL);
}
char *ft_getenv(char *var,char **env)
{
	char *tmp;
	int i = 0;

	while(env[i])
	{
		tmp = ft_strdup(env[i]);
		if (ft_strncmp(var,env[i],ft_strlen(var)) == 0)
			return(tmp);
		i++;
	}
	return(NULL);
}
void 	pipex(int infile, int outfile, char **av, char **env)
{
	int fd[2];
	char **commande = ft_split(av[2],' ');
	char **commande2 = ft_split(av[3],' ');
	char *pathline = ft_getenv("PATH=",env);
	char *line = getlinepath(pathline,*commande);
	char *line2 = getlinepath(pathline,*commande2);
	pid_t pid;
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(infile, STDIN_FILENO);
		dup2(fd[1],STDOUT_FILENO);
		execve(line,commande,env);
	}
	else
	{
		waitpid(pid,0,0);
		close(fd[1]);
		dup2(fd[0],STDIN_FILENO);
		dup2(outfile,STDOUT_FILENO);
		execve(line2,commande2,env);
	}
}
int	main(int ac, char **av, char **env)
{
	int infile;
	int outfile;
	(void)ac;

	infile = open(av[1], O_RDONLY);
	outfile = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (infile < 0 || outfile < 0)
      return (-1);
	pipex(infile, outfile, av, env);
	
	return(0);
}