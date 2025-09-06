/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:25:23 by yjazouli          #+#    #+#             */
/*   Updated: 2025/09/05 17:18:43 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	create_map(void)
{
	t_parse	*scene;
	t_game	*game;
	t_map	*map;
	int		y;

	y = 0;
	game = get_game();
	map = &game->map;
	scene = &game->scene;
	map->width = scene->width;
	map->height = scene->height;
	map->grid = ft_malloc(sizeof(int *) * map->height);
	while (y < map->height)
	{
		map->grid[y] = ft_malloc(sizeof(int) * map->width);
		y++;
	}
}

static void	fill_map(t_map *map, char key, int y, int x)
{
	t_parse	*scene;
	t_game	*game;
	int		c;

	game = get_game();
	scene = &game->scene;
	if (key == '1' || key == ' ' || x >= ft_strlen(scene->map[y]))
		c = 1;
	else
		c = 0;
	if (key == 'N' || key == 'S' || key == 'E' || key == 'W')
	{
		map->player_dir = key;
		map->player_x = x;
		map->player_y = y;
	}
	map->grid[y][x] = c;
}

void	build_map(void)
{
	t_parse	*scene;
	t_game	*game;
	t_map	*map;
	int		y;
	int		x;

	y = 0;
	game = get_game();
	scene = &game->scene;
	map = &game->map;
	create_map();
	while (y < scene->height)
	{
		x = 0;
		while (x < map->width)
		{
			fill_map(map, scene->map[y][x], y, x);
			x++;
		}
		y++;
	}
}
