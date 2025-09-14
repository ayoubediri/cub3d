/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 22:59:38 by yjazouli          #+#    #+#             */
/*   Updated: 2025/09/14 13:28:20 by yjazouli         ###   ########.fr       */
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

static void	calc_wall_height(t_ray *ray, t_player *player, t_mlx *mlx)
{
	(void)player;
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
	ray->line_height = (int)(mlx->height / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + mlx->height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + mlx->height / 2;
	if (ray->draw_end >= mlx->height)
		ray->draw_end = mlx->height - 1;
}

static void	calc_wall_x(t_ray *ray)
{
	t_game		*game;
	t_texture	*texture;

	texture = get_wall_textures();
	game = get_game();
	if (ray->side == 0)
	{
		ray->wall_x = game->player.pos_y + ray->perp_wall_dist * ray->dir_y;
		if (ray->delta_dist_x < 0)
			ray->wall = &texture[WALL_WEST];
		else
			ray->wall = &texture[WALL_EAST];
	}
	else
	{
		ray->wall_x = game->player.pos_x + ray->perp_wall_dist * ray->dir_x;
		if (ray->delta_dist_y < 0)
			ray->wall = &texture[WALL_NORTH];
		else
			ray->wall = &texture[WALL_SOUTH];
	}
	ray->wall_x -= floor(ray->wall_x);
}

t_texture	*wall_side_texture(t_ray *ray)
{
	t_texture	*wall_textures;

	wall_textures = get_wall_textures();
	if (ray->side == 0 && ray->dir_x > 0)
		return (&wall_textures[WALL_WEST]);
	if (ray->side == 0 && ray->dir_x < 0)
		return (&wall_textures[WALL_EAST]);
	if (ray->side == 1 && ray->dir_y > 0)
		return (&wall_textures[WALL_NORTH]);
	return (&wall_textures[WALL_SOUTH]);
}

unsigned int	get_texture_color(t_texture *texture, int x, int y)
{
	char	*dst;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	dst = texture->addr + (y * texture->len_line + x * (texture->bpp / 8));
	return (*(unsigned int *)dst);
}

unsigned int	get_wall_color(int tex_x, double *tex_pos, double step,
		t_texture *texture)
{
	int				tex_y;
	unsigned int	color;

	tex_y = (int)(*tex_pos) & (texture->height - 1);
	*tex_pos += step;
	color = get_texture_color(texture, tex_x, tex_y);
	return (color);
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
	t_game		*game;
	t_texture	*texture;
	int			color;
	double		step;
	double		pos_y;

	texture = wall_side_texture(ray);
	game = get_game();
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

void	calc_tex_x(t_ray *ray)
{
	ray->tex_x = (int)(ray->wall_x * (double)ray->wall->width);
	if (ray->side == 0 && ray->dir_x < 0)
		ray->tex_x = ray->wall->width - ray->tex_x - 1;
	if (ray->side == 1 && ray->dir_y > 0)
		ray->tex_x = ray->wall->width - ray->tex_x - 1;
	if (ray->tex_x >= ray->wall->width)
		ray->tex_x = ray->wall->width - 1;
	else if (ray->tex_x < 0)
		ray->tex_x = 0;
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
