/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:36:51 by sarif             #+#    #+#             */
/*   Updated: 2024/04/28 18:38:35 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_argvcounter(char **av)
{
	int	c;

	c = 0;
	while (av[c])
	{
		c++;
	}
	return (c);
}

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
	return (NULL);
}

char	*ft_getenv(char *var, char **env)
{
	char	*tmp;
	int		i;

	i = 0;
	while (env[i])
	{
		tmp = ft_strdup(env[i]);
		if (ft_strncmp(var, env[i], ft_strlen(var)) == 0)
			return (tmp);
		free(tmp);
		i++;
	}
	return (NULL);
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