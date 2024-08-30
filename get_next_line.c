/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 19:33:13 by samunyan          #+#    #+#             */
/*   Updated: 2022/04/11 19:33:14 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_line(char **buffer)
{
	char	*line;
	char	*new_buffer;
	size_t	i;

	i = 0;
	while ((*buffer)[i] != '\n')
		i++;
	(*buffer)[i] = '\0';
	line = ft_strjoin(*buffer, "\n");
	if (!line)
	{
		free(*buffer);
		return (NULL);
	}
	new_buffer = ft_strdup(*buffer + i + 1);
	free(*buffer);
	*buffer = new_buffer;
	if (!(*buffer))
	{
		free(line);
		line = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer[OPEN_MAX];
	char		reader[BUFFER_SIZE + 1];
	ssize_t		bytes_read;
	char		*line;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE < 1)
		return (NULL);
	bytes_read = read(fd, reader, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		reader[bytes_read] = '\0';
		if (!append(&(buffer[fd]), reader))
			return (NULL);
		if (ft_strchr(buffer[fd], '\n'))
			return (get_line(&(buffer[fd])));
		bytes_read = read(fd, reader, BUFFER_SIZE);
	}
	line = NULL;
	if (bytes_read == 0 && buffer[fd] && ft_strchr(buffer[fd], '\n'))
		return (get_line(&(buffer[fd])));
	if (bytes_read == 0 && buffer[fd] && *(buffer[fd]))
		line = ft_strdup(buffer[fd]);
	free(buffer[fd]);
	buffer[fd] = NULL;
	return (line);
}
