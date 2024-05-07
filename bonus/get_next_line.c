/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 22:12:37 by sarif             #+#    #+#             */
/*   Updated: 2023/12/27 20:18:31 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static char	*ft_strjoin(char *reserve, char *buffer)
{
	char	*new_reserve;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!reserve)
		return (ft_strdup(buffer));
	new_reserve = (char *)malloc(ft_strlen(reserve) + ft_strlen(buffer) + 1);
	if (!new_reserve)
		return (free(reserve), reserve = NULL, NULL);
	while (reserve[i])
	{
		new_reserve[i] = reserve[i];
		i++;
	}
	while (buffer[j])
		new_reserve[i++] = buffer[j++];
	new_reserve[i] = '\0';
	free(reserve);
	reserve = NULL;
	return (new_reserve);
}

static int	ft_checknl(char *reserve)
{
	int	i;

	i = 0;
	if (!reserve)
		return (0);
	while (reserve[i])
	{
		if (reserve[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_read(int fd, char *reserve)
{
	int		rindex;
	char	*buffer;

	rindex = 1;
	while (!ft_checknl(reserve) && rindex > 0)
	{
		buffer = (char *)malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
		if (!buffer)
			return (free(reserve), reserve = NULL, NULL);
		rindex = read(fd, buffer, BUFFER_SIZE);
		if (rindex == -1)
			return (free(buffer), buffer = NULL, NULL);
		if (rindex == 0)
			return (free(buffer), buffer = NULL, reserve);
		buffer[rindex] = '\0';
		reserve = ft_strjoin(reserve, buffer);
		free(buffer);
	}
	return (reserve);
}

char	*get_next_line(int fd)
{
	static char	*reserve;
	char		*line;

	if (fd < 0 || fd > OPEN_MAX)
		return (NULL);
	if (read(fd, 0, 0) == -1 || BUFFER_SIZE <= 0)
		return (free(reserve), reserve = NULL, NULL);
	reserve = ft_read(fd, reserve);
	if (!reserve || !*reserve)
		return (free(reserve), reserve = NULL, NULL);
	line = ft_getline(reserve);
	if (!line)
		return (free(reserve), reserve = NULL, NULL);
	reserve = ft_update(reserve);
	return (line);
}
