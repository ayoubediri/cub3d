/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:13:18 by yjazouli          #+#    #+#             */
/*   Updated: 2025/09/14 13:28:46 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	validate_path(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 4)
		parse_error("File must be at least 4 characters long");
	if (ft_strcmp(".cub", path + len - 4))
		parse_error("File must end with the extension .cub");
}

static int	extract_fd(char *path)
{
	int	fd;

	validate_path(path);
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		report_error("open", strerror(errno));
		leave_game(1);
	}
	return (fd);
}

static int	is_element(char *line)
{
	int	i;

	i = 0;
	while (is_space(line[i]))
		i++;
	if (line[i] == 'F' || line[i] == 'C')
		return (is_space(line[i + 1]));
	if (!line[i] || !line[i + 1])
		return (0);
	if ((line[i] == 'N' && line[i + 1] == 'O') || (line[i] == 'S' && line[i
				+ 1] == 'O') || (line[i] == 'W' && line[i + 1] == 'E')
		|| (line[i] == 'E' && line[i + 1] == 'A'))
		return (line[i + 2] == '\0' || is_space(line[i + 2]));
	return (0);
}

static void	determine_section(char *line, t_parse_state *state)
{
	if (*state == ELEMENTS)
	{
		if (is_element(line))
			parse_element(line);
		else
		{
			*state = MAP;
			check_elements();
			parse_map_line(line);
		}
	}
	else
		parse_map_line(line);
}

void	parse_map(char *path)
{
	t_game			*game;
	char			*line;
	t_parse_state	state;

	game = get_game();
	state = ELEMENTS;
	game->fd = extract_fd(path);
	while (1)
	{
		line = get_next_line(game->fd);
		if (!line)
			break ;
		else if (is_empty_line(line))
		{
			if (state == MAP)
				parse_error("Empty lines inside the map");
			else
				continue ;
		}
		else
			determine_section(line, &state);
	}
	validate_map();
	build_map();
}
