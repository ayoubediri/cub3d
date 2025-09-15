/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiri <adiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 09:45:28 by adiri             #+#    #+#             */
/*   Updated: 2025/09/15 16:46:56 by adiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	calc_floor(t_floor *info, t_camera *camera, t_texture *floor_txt)
{
	info->row_distance = info->player_z / (info->y - HALF_HEIGHT);
	info->floor_step_x = info->row_distance * (info->dir_x1 - \
		info->dir_x0) / WIDTH;
	info->floor_step_y = info->row_distance * (info->dir_y1 - \
		info->dir_y0) / WIDTH;
	info->floor_x = camera->pos.x + info->row_distance * \
	info->dir_x0 + info->floor_step_x * info->x;
	info->floor_y = camera->pos.y + info->row_distance * \
	info->dir_y0 + info->floor_step_y * info->x;
	info->tex_x = (int)(info->floor_x * floor_txt->width) % floor_txt->width;
	info->tex_y = (int)(info->floor_y * floor_txt->height) % floor_txt->height;
	info->color = get_texture_color(floor_txt, info->tex_x, info->tex_y);
}

void	draw_floor(int x, int y)
{
	t_camera	*camera;
	t_texture	*floor_txt;
	t_floor		*info;

	camera = get_camera();
	floor_txt = &get_game()->ground_texture;
	info = &camera->floor;
	info->x = x;
	info->y = y;
	while (info->y < HEIGHT)
	{
		if (info->y == HALF_HEIGHT && info->y++)
			continue ;
		calc_floor(info, camera, floor_txt);
		pixel_put(x, info->y, info->color);
		info->y++;
	}
}

void	draw_sky(int x)
{
	t_camera	*camera;
	t_sky		sky;
	int			y;

	camera = get_camera();
	sky.texture = &get_game()->sky_texture;
	sky.dir_x = camera->dir.x + camera->plane.x * camera->ray.camera_x;
	sky.dir_y = camera->dir.y + camera->plane.y * camera->ray.camera_x;
	sky.angle = atan2(sky.dir_y, sky.dir_x);
	sky.tex_x = (int)((sky.angle / (2 * M_PI)) * sky.texture->width);
	sky.tex_x = (sky.tex_x % sky.texture->width + sky.texture->width) \
	% sky.texture->width;
	y = 0;
	while (y <= HALF_HEIGHT)
	{
		sky.tex_y = (int)(y * sky.texture->height / HEIGHT) % \
		sky.texture->height;
		sky.color = get_texture_color(sky.texture, sky.tex_x, sky.tex_y);
		pixel_put(x, y, sky.color);
		y++;
	}
}

int	get_wall_color(t_ray *ray, double step, double *tex_pos)
{
	int			tex_y;
	int			color;
	t_texture	*texture;

	texture = ray->texture;
	tex_y = (int)(*tex_pos) & (texture->height - 1);
	*tex_pos += step;
	color = get_texture_color(texture, ray->tex_x, tex_y);
	return (color);
}

void	draw_wall_x(int x)
{
	t_camera	*camera;
	t_ray		*ray;
	int			y;
	double		step;
	double		tex_pos;

	camera = get_camera();
	ray = &camera->ray;
	y = ray->start;
	step = (double)ray->texture->height / ray->height;
	tex_pos = (ray->start - HALF_HEIGHT + ray->height / 2) * step;
	while (y < ray->end)
	{
		pixel_put(x, y, get_wall_color(ray, step, &tex_pos));
		y++;
	}
}
