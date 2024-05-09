/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:15:22 by sarif             #+#    #+#             */
/*   Updated: 2024/05/09 14:44:06 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "get_next_line.h"
# include <stdbool.h>

typedef struct s_data
{
	int		fd[2];
	bool	hrdc;
	int		infile;
	int		outfile;
	int		fdd;
}	t_data;

extern char	**environ;

//libft------------------
char	**ft_split(char *s, char c);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
int		ft_countword(char *str, char c);
size_t	ft_strlen(char *s);
int		ft_strncmp(char *s1, char *s2, size_t n);
char	*ft_strdup(char *s1);
char	*ft_strcat(char *dest, char *src);
char	*ft_strcpy(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(char *s1, char *s2);

//pipex----------------
void	pipex(t_data *d, char **av, int ac);
int		ft_argvcounter(char **av);
void	execute_cmd(char *commande);
char	*ft_getenv(char *var);
char	*getlinepath(char *path, char *commande);
int		ft_2dfree(char **s);
void	redirectpipes(t_data *d, int i, int ac);
void	here_doc_handler(t_data *d, char **av, int ac);




#endif