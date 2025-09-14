/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:45:43 by yjazouli          #+#    #+#             */
/*   Updated: 2025/08/20 10:47:56 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	read_to_buffer(int fd, char *buffer)
{
	int	bytes_read;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read > 0)
		buffer[bytes_read] = '\0';
	else
		buffer[0] = '\0';
	return (bytes_read);
}

static int	find_newline(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static char	*add_char(char *line, char *buffer, int len)
{
	size_t	cur_len;
	char	*new_line;

	cur_len = strlen(line);
	new_line = ft_realloc(line, cur_len + len + 1);
	memcpy(new_line + cur_len, buffer, len);
	new_line[cur_len + len] = '\0';
	return (new_line);
}

static int	handle_line(char **line, char *buffer, int *pos, int bytes_read)
{
	int	nl;
	int	chunk_len;

	nl = find_newline(buffer + *pos);
	if (nl >= 0)
	{
		*line = add_char(*line, buffer + *pos, nl);
		if (!*line)
			return (-1);
		*pos += nl + 1;
		return (1);
	}
	chunk_len = strlen(buffer + *pos);
	*line = add_char(*line, buffer + *pos, chunk_len);
	*pos = bytes_read;
	return (0);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	static int	bytes_read;
	static int	pos;
	char		*line;

	if (fd < 0)
		return (NULL);
	line = ft_malloc(1);
	line[0] = '\0';
	while (1)
	{
		if (pos >= bytes_read)
		{
			bytes_read = read_to_buffer(fd, buffer);
			pos = 0;
			if (bytes_read <= 0)
				break ;
		}
		if (handle_line(&line, buffer, &pos, bytes_read))
			return (line);
	}
	if (*line)
		return (line);
	return (NULL);
}
