/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrazek <kdrazek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:16:29 by kdrazek           #+#    #+#             */
/*   Updated: 2025/04/16 17:08:18 by kdrazek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "so_long.h"

char	*ft_joinfree(char *buf, char *tmp)
{
	char	*tmp2;

	tmp2 = buf;
	buf = ft_strjoin(buf, tmp);
	free(tmp2);
	return (buf);
}

char	*get_rest_file(char *buf)
{
	int		i;
	int		j;
	char	*tmp_buf;

	i = 0;
	j = 0;
	if (!buf[i])
	{
		free(buf);
		return (NULL);
	}
	while (buf[i] && buf[i] != '\n')
		++i;
	tmp_buf = ft_calloc(ft_strlen(buf) - i + 1, sizeof(char));
	if (!tmp_buf)
	{
		free(tmp_buf);
		free(buf);
		return (NULL);
	}
	while (buf[i])
		tmp_buf[j++] = buf[i++ + 1];
	free(buf);
	buf = NULL;
	return (tmp_buf);
}

char	*get_one_line(char *buf)
{
	int		i;
	char	*one_line;

	i = 0;
	if (!buf[i])
		return (NULL);
	while (buf[i] && buf[i] != '\n')
		++i;
	one_line = ft_calloc(i + 2, sizeof(char));
	if (!one_line)
		return (NULL);
	i = 0;
	while (buf[i] && buf[i] != '\n')
	{
		one_line[i] = buf[i];
		++i;
	}
	if (buf[i] && buf[i] == '\n')
		one_line[i] = '\n';
	return (one_line);
}

char	*read_line(int fd, char *buf)
{
	int		bytes_read;
	char	*tmp;

	tmp = malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (!tmp)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, tmp, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buf);
			free(tmp);
			return (NULL);
		}
		tmp[bytes_read] = 0;
		buf = ft_joinfree(buf, tmp);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	free(tmp);
	return (buf);
}

char	*get_next_line(int fd)
{
	static char	*buf;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buf)
		buf = ft_calloc(1, 1);
	buf = read_line(fd, buf);
	if (!buf)
		return (NULL);
	line = get_one_line(buf);
	buf = get_rest_file(buf);
	return (line);
}
