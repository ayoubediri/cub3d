/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiri <adiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 10:21:55 by adiri             #+#    #+#             */
/*   Updated: 2025/09/12 11:05:35 by adiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_raycasting(int x)
{
	t_camera	*camera;
	t_ray		*ray;

	camera = get_camera();
	ray = &camera->ray;
	ray->camera_x = 2 * x / (double)WIDTH - 1;
	ray->dir.x = camera->dir.x + camera->plane.x * ray->camera_x;
	ray->dir.y = camera->dir.y + camera->plane.y * ray->camera_x;
	ray->map_x = camera->pos.x;
	ray->map_y = camera->pos.y;
	ray->delta_dist.x = fabs(1 / ray->dir.x);
	ray->delta_dist.y = fabs(1 / ray->dir.y);
	ray->hit_side = 0;
	ray->perp_wall_dist = 0.0;
}

unsigned int	get_texture_color(t_texture *texture, int x, int y)
{
	char	*dst;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	dst = texture->addr + (y * texture->line_length + x * (texture->bpp / 8));
	return (*(unsigned int *)dst);
}

void	draw_ceiling_and_floor(int x)
{
	t_camera	*camera;

	camera = get_camera();
	draw_sky(x);
	draw_floor(x, camera->ray.end);
}

void	raycasting(void)
{
	int				x;
	double			z_buffer[WIDTH];
	t_camera		*camera;

	x = 0;
	camera = get_camera();
	while (x < WIDTH)
	{
		init_raycasting(x);
		init_steps();
		perform_dda();
		calc_texture();
		draw_ceiling_and_floor(x);
		draw_wall_x(x);
		z_buffer[x] = camera->ray.perp_wall_dist;
		x++;
	}
	draw_sprites(z_buffer);
}
