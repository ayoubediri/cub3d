/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiri <adiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:21:53 by adiri             #+#    #+#             */
/*   Updated: 2025/09/15 17:23:26 by adiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_wall_height(t_ray *ray, t_player *player, t_mlx *mlx)
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

void	calc_wall_x(t_ray *ray)
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
