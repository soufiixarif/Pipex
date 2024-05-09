/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 22:11:40 by sarif             #+#    #+#             */
/*   Updated: 2024/05/09 15:53:13 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

extern char	**environ;

typedef struct s_data
{
	char	*file1;
	char	*cmd1;
	char	*file2;
	char	*cmd2;
}	t_data;

//libft------------------
char	**ft_split(char *s, char c);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
int		ft_countword(char *str, char c);
size_t	ft_strlen(const char *s);
int		ft_strncmp(char *s1, char *s2, size_t n);
char	*ft_strdup(char *s1);
char	*ft_strcat(char *dest, char *src);
char	*ft_strcpy(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);

//pipex------------------
void	*ft_freestr(char **str, int j);
void	pipex(int infile, int outfile, char **av);
char	*getlinepath(char *path, char *commande);
void	childone(int *fd, int infile, char **av);
void	childtwo(int *fd, int outfile, char **av);
void	printerror(char *bash, char *commande);
int		ft_2dfree(char **s);
char	*ft_getenv(char *var);
void	printfderror(char *bash, char *infile);
void	put_stderr(char *s);

#endif
