/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 22:11:40 by sarif             #+#    #+#             */
/*   Updated: 2024/03/28 21:23:52 by sarif            ###   ########.fr       */
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
void	*ft_freestr(char **str, int j);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
int		ft_countword(char *str, char c);
size_t	ft_strlen(const char *s);
char	*ft_getenv(char *var);
int		ft_strncmp(char *s1, char *s2, size_t n);
void	pipex(int infile, int outfile, char **av);
char	*ft_strdup(char *s1);
char	*getlinepath(char *path, char *commande);
char	*ft_strcat(char *dest, char *src);
char	*ft_strcpy(char *s1, char *s2);
void	childone(int *fd, int infile, char **av);
void	childtwo(int *fd, int outfile, char **av);
void	printerror(char *bash, char *commande);
int	ft_2dfree(char **s);

#endif
