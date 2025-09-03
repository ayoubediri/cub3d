/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 14:49:31 by yjazouli          #+#    #+#             */
/*   Updated: 2025/09/03 11:13:31 by yjazouli         ###   ########.fr       */
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

static int	find_door_along_ray(double px, double py, double dx, double dy,
        double reach, int *out_x, int *out_y)
{
    int		steps;
    int		i;
    double	len;
    double	nx;
    double	ny;
    double	t;
    double	sx;
    double	sy;
    int		cx;
    int		cy;

    len = sqrt(dx * dx + dy * dy);
    if (len == 0.0)
        return (0);
    nx = dx / len;
    ny = dy / len;

    steps = (int)ceil(reach * 8.0);
    if (steps < 4)
        steps = 4;

    i = 1;
    while (i <= steps)
    {
        t = ((double)i / (double)steps) * reach;
        sx = px + nx * t;
        sy = py + ny * t;
        cx = (int)floor(sx);
        cy = (int)floor(sy);
        if (cx == (int)floor(px) && cy == (int)floor(py))
        {
            i++;
            continue ;
        }
        if (door_exists(cx, cy))
        {
            *out_x = cx;
            *out_y = cy;
            return (1);
        }
        i++;
    }
    return (0);
}

void	toggle_door_in_front(void)
{
    t_gameplay	*gp;
    t_entity	*player;
    int			tx;
    int			ty;
    int			px;
    int			py;
    double		reach;
    int			found;

    gp = get_gameplay();
    if (!gp || !gp->player.ent)
        return ;
    player = gp->player.ent;
    px = (int)floor(player->pos.x);
    py = (int)floor(player->pos.y);

    reach = 1.2;

    found = find_door_along_ray(player->pos.x, player->pos.y,
            player->dir.x, player->dir.y, reach, &tx, &ty);
    if (!found)
        return ;

    if (door_is_open(tx, ty) && tx == px && ty == py)
        return ;

    if (door_is_open(tx, ty))
        close_door(tx, ty);
    else
        open_door(tx, ty);
}
