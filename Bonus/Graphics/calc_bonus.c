/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiri <adiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 09:44:24 by adiri             #+#    #+#             */
/*   Updated: 2025/09/13 09:58:01 by adiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	calc_perp_wall_dist(void)
{
	t_camera	*camera;
	t_ray		*ray;

	camera = get_camera();
	ray = &camera->ray;
	if (ray->hit_side == 0)
		ray->perp_wall_dist = (ray->map_x - camera->pos.x + \
			(1 - ray->step.x) / 2) / ray->dir.x;
	else
		ray->perp_wall_dist = (ray->map_y - camera->pos.y + \
			(1 - ray->step.y) / 2) / ray->dir.y;
	ray->height = (int)(HEIGHT / ray->perp_wall_dist);
	ray->start = -ray->height / 2 + HALF_HEIGHT;
	if (ray->start < 0)
		ray->start = 0;
	ray->end = ray->height / 2 + HALF_HEIGHT;
	if (ray->end >= HEIGHT)
		ray->end = HEIGHT - 1;
}

void	calc_wall_tex_idx(void)
{
	t_camera	*camera;
	t_ray		*ray;

	camera = get_camera();
	ray = &camera->ray;
	if (ray->hit_side == 0)
	{
		ray->wall_x = camera->pos.y + ray->perp_wall_dist * ray->dir.y;
		if (ray->step.x > 0)
			ray->texture = &get_game()->wall_textures[WALL_EAST];
		else
			ray->texture = &get_game()->wall_textures[WALL_WEST];
	}
	else
	{
		ray->wall_x = camera->pos.x + ray->perp_wall_dist * ray->dir.x;
		if (ray->step.y > 0)
			ray->texture = &get_game()->wall_textures[WALL_SOUTH];
		else
			ray->texture = &get_game()->wall_textures[WALL_NORTH];
	}
	ray->wall_x -= floor(ray->wall_x);
}

void	calc_tex_x(void)
{
	t_ray		*ray;
	int			tex_x;

	ray = &get_camera()->ray;
	tex_x = (int)(ray->wall_x * (double)(ray->texture->width));
	if (ray->hit_side == 0 && ray->dir.x > 0)
		tex_x = ray->texture->width - tex_x - 1;
	if (ray->hit_side == 1 && ray->dir.y < 0)
		tex_x = ray->texture->width - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= ray->texture->width)
		tex_x = ray->texture->width - 1;
	ray->tex_x = tex_x;
}

void	calc_door_texture(t_ray *ray)
{
	t_camera	*camera;

	camera = get_camera();
	ray->texture = &get_gameplay()->door_texture_close;
	if (ray->hit_side == 0)
		ray->wall_x = camera->pos.y + ray->perp_wall_dist * ray->dir.y;
	else
		ray->wall_x = camera->pos.x + ray->perp_wall_dist * ray->dir.x;
	ray->wall_x -= floor(ray->wall_x);
}

void	calc_texture(void)
{
	t_camera	*camera;
	t_ray		*ray;

	camera = get_camera();
	ray = &camera->ray;
	calc_perp_wall_dist();
	if (ray->is_door)
		calc_door_texture(ray);
	else
		calc_wall_tex_idx();
	calc_tex_x();
}
