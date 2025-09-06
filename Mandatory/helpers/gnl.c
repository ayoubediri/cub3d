/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 14:41:49 by yjazouli          #+#    #+#             */
/*   Updated: 2025/06/15 15:29:48 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	char	*temp;
	char	old_char;

	old_char = buffer[len];
	buffer[len] = '\0';
	temp = ft_strjoin2(line, buffer);
	buffer[len] = old_char;
	return (temp);
}

static int	handle_line(char **line, char *buffer, int *pos, int bytes_read)
{
	int	nl;

	nl = find_newline(buffer + *pos);
	if (nl >= 0)
	{
		*line = add_char(*line, buffer + *pos, nl);
		*pos += nl + 1;
		return (1);
	}
	*line = add_char(*line, buffer + *pos, ft_strlen(buffer + *pos));
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
