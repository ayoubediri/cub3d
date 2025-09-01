/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions_walls_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 10:33:49 by yjazouli          #+#    #+#             */
/*   Updated: 2025/09/01 17:36:02 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	check_door(int x, int y)
{
	t_game	*game;

	game = get_game();
	if (get_door_at(game, x, y) == NULL)
		return (0);
	return (!door_is_open(x, y));
}

int	check_corners(double corners[4][2])
{
	t_game	*game;
	t_map	*map;
	int		map_x;
	int		map_y;
	int		i;

	game = get_game();
	map = &game->map;
	if (!map || !map->grid || !map->doors_grid)
		return (1);
	i = 0;
	while (i < 4)
	{
		map_x = (int)corners[i][0];
		map_y = (int)corners[i][1];
		if (map_x < 0 || map_x >= map->width || map_y < 0
			|| map_y >= map->height)
			return (1);
		if (map->grid[map_y * map->width + map_x] == 1)
			return (1);
		if (check_door(map_x, map_y))
			return (1);
		i++;
	}
	return (0);
}

int	check_collision(double new_x, double new_y, double radius)
{
	double	corners[4][2];

	if (radius <= 0.0)
		radius = 0.05;
	corners[0][0] = new_x - radius;
	corners[0][1] = new_y - radius;
	corners[1][0] = new_x + radius;
	corners[1][1] = new_y - radius;
	corners[2][0] = new_x - radius;
	corners[2][1] = new_y + radius;
	corners[3][0] = new_x + radius;
	corners[3][1] = new_y + radius;
	if (check_corners(corners))
		return (1);
	return (0);
}

int	entity_try_move_to(t_entity *ent, double nx, double ny)
{
	if (!ent)
		return (0);
	if (check_collision(nx, ny, ent->radius))
		return (0);
	if (resolve_overlap(ent, &nx, &ny))
		return (0);
	ent->prev.x = ent->pos.x;
	ent->prev.y = ent->pos.y;
	ent->pos.x = nx;
	ent->pos.y = ny;
	return (1);
}

int	entity_try_move_by(t_entity *ent, double dx, double dy)
{
	double	nx;
	double	ny;

	if (!ent)
		return (0);
	nx = ent->pos.x + dx;
	ny = ent->pos.y + dy;
	if (entity_try_move_to(ent, nx, ny))
		return (1);
	if (dx != 0.0 && entity_try_move_to(ent, ent->pos.x + dx, ent->pos.y))
		return (1);
	if (dy != 0.0 && entity_try_move_to(ent, ent->pos.x, ent->pos.y + dy))
		return (1);
	return (0);
}
