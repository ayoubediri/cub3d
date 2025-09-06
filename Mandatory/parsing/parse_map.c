/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:50:23 by yjazouli          #+#    #+#             */
/*   Updated: 2025/07/15 23:11:49 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	valid_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W');
}

static void	check_player(char c, int y, int x)
{
	static int	player_found = 0;
	t_parse		*scene;

	scene = &get_game()->scene;
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (player_found)
			parse_error("Multiple player positions found in map");
		scene->dir = c;
		player_found = 1;
		scene->player_x = x;
		scene->player_y = y;
	}
}

void	parse_map_line(char *line)
{
	static int	y = 0;
	t_parse		*scene;
	int			x;

	x = 0;
	scene = &get_game()->scene;
	if (!scene->map)
	{
		scene->map = ft_malloc(sizeof(char *));
		scene->map[0] = NULL;
	}
	scene->map = ft_realloc(scene->map, sizeof(char *) * (y + 2));
	scene->map[y] = ft_strdup(line);
	scene->map[y + 1] = NULL;
	while (line[x])
	{
		if (!valid_char(line[x]))
			parse_error("Invalid character in map");
		check_player(line[x], y, x);
		x++;
	}
	if (x > scene->width)
		scene->width = x;
	scene->height = ++y;
}
