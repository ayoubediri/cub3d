/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 22:59:38 by yjazouli          #+#    #+#             */
/*   Updated: 2025/07/28 17:02:46 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	prepare(t_ray *ray, t_player *player)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->pos_x)
			* ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->pos_y)
			* ray->delta_dist_y;
	}
}

static void	perform_dda(t_ray *ray, t_map *map)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_x < 0 || ray->map_y < 0 || ray->map_x >= map->width
			|| ray->map_y >= map->height)
			break ;
		if (map->grid[ray->map_y][ray->map_x] > 0)
			hit = 1;
	}
}

static void	calc_wall_height(t_ray *ray, t_player *player, t_mlx *mlx)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - player->pos_x + (1 - ray->step_x)
				/ 2) / ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - player->pos_y + (1 - ray->step_y)
				/ 2) / ray->dir_y;
	ray->line_height = (int)(mlx->height / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + mlx->height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + mlx->height / 2;
	if (ray->draw_end >= mlx->height)
		ray->draw_end = mlx->height - 1;
}

static void	draw_wall_slice(int x, t_ray *ray)
{
	int	y;
	int	color;

	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			color = 0xFF0000;
		else
			color = 0x00FF00;
	}
	else
	{
		if (ray->step_y > 0)
			color = 0x0000FF;
		else
			color = 0xFFFF00;
	}
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		pixel_put(x, y, color);
		y++;
	}
}

void	raycasting(void)
{
	double		camera_x;
	t_player	*player;
	t_game		*game;
	t_ray		ray;
	int			x;

	x = -1;
	game = get_game();
	player = &game->player;
	while (++x < game->mlx.width)
	{
		camera_x = 2 * x / (double)game->mlx.width - 1;
		ray.dir_x = player->dir_x + player->plane_x * camera_x;
		ray.dir_y = player->dir_y + player->plane_y * camera_x;
		ray.map_x = (int)player->pos_x;
		ray.map_y = (int)player->pos_y;
		ray.delta_dist_x = fabs(1 / ray.dir_x);
		ray.delta_dist_y = fabs(1 / ray.dir_y);
		prepare(&ray, player);
		perform_dda(&ray, &game->map);
		calc_wall_height(&ray, player, &game->mlx);
		draw_wall_slice(x, &ray);
	}
}
