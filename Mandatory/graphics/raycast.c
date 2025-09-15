/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiri <adiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 22:59:38 by yjazouli          #+#    #+#             */
/*   Updated: 2025/09/15 17:26:02 by adiri            ###   ########.fr       */
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
		if (map->grid[ray->map_y][ray->map_x] == 1)
			hit = 1;
	}
}

void	draw_ceiling_and_floor(int x, int start, int end)
{
	t_game	*game;
	int		y;
	int		color;
	t_mlx	*mlx;

	game = get_game();
	mlx = &game->mlx;
	y = 0;
	color = game->parse.ceiling_col;
	while (y < start)
	{
		pixel_put(x, y, color);
		y++;
	}
	color = game->parse.floor_col;
	y = end;
	while (y < mlx->height)
	{
		pixel_put(x, y, color);
		y++;
	}
}

void	draw_wall(int x, int y, t_ray *ray)
{
	t_texture	*texture;
	int			color;
	double		step;
	double		pos_y;

	texture = wall_side_texture(ray);
	step = 1.0 * texture->height / ray->line_height;
	pos_y = (y - HALF_HEIGHT + ray->line_height / 2) * step;
	draw_ceiling_and_floor(x, y, ray->draw_end);
	while (y < ray->draw_end)
	{
		color = get_wall_color(ray->tex_x, &pos_y, step, texture);
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
		calc_wall_x(&ray);
		calc_tex_x(&ray);
		draw_wall(x, ray.draw_start, &ray);
	}
}
