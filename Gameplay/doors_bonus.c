/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 14:49:31 by yjazouli          #+#    #+#             */
/*   Updated: 2025/09/03 10:29:28 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	door_exists(int x, int y)
{
	t_game	*game;
	t_map	*map;
	int		idx;
	int		val;

	game = get_game();
	if (!game)
		return (0);
	map = &game->map;
	if (!map || x < 0 || x >= map->width || y < 0 || y >= map->height)
		return (0);
	idx = y * map->width + x;
	val = map->grid[idx];
	return (val == 3 || val == 4);
}

int	door_is_open(int x, int y)
{
	t_game	*game;
	t_map	*map;
	int		idx;

	game = get_game();
	if (!game)
		return (0);
	map = &game->map;
	if (!map || x < 0 || x >= map->width || y < 0 || y >= map->height)
		return (0);
	idx = y * map->width + x;
	return (map->grid[idx] == 4);
}

void	open_door(int x, int y)
{
	t_game	*game;
	t_map	*map;
	int		idx;

	game = get_game();
	if (!game)
		return ;
	map = &game->map;
	if (!map || x < 0 || x >= map->width || y < 0 || y >= map->height)
		return ;
	idx = y * map->width + x;
	if (map->grid[idx] == 3)
		map->grid[idx] = 4;
}

void	close_door(int x, int y)
{
	t_game	*game;
	t_map	*map;
	int		idx;

	game = get_game();
	if (!game)
		return ;
	map = &game->map;
	if (!map || x < 0 || x >= map->width || y < 0 || y >= map->height)
		return ;
	idx = y * map->width + x;
	if (map->grid[idx] == 4)
		map->grid[idx] = 3;
}

void	toggle_door_in_front(void)
{
	t_gameplay	*gp;
	t_entity	*player;
	int			tx;
	int			ty;

	gp = get_gameplay();
	player = gp->player.ent;
	tx = (int)round(player->pos.x + player->dir.x);
	ty = (int)round(player->pos.y + player->dir.y);
	if (!door_exists(tx, ty))
		return ;
	if (door_is_open(tx, ty))
		close_door(tx, ty);
	else
		open_door(tx, ty);
}
