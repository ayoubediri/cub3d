/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algo_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiri <adiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 09:48:08 by adiri             #+#    #+#             */
/*   Updated: 2025/09/12 10:27:20 by adiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_step_x(t_ray *ray, t_camera *camera)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (camera->pos.x - ray->map_x) * ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map_x + 1.0 - camera->pos.x) * \
		ray->delta_dist.x;
	}
}

void	init_step_y(t_ray *ray, t_camera *camera)
{
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (camera->pos.y - ray->map_y) * ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map_y + 1.0 - camera->pos.y) * \
		ray->delta_dist.y;
	}
}

void	init_steps(void)
{
	t_camera		*camera;
	t_ray			*ray;

	camera = get_camera();
	ray = &camera->ray;
	init_step_x(ray, camera);
	init_step_y(ray, camera);
}

void	dda_calculate(t_ray *ray)
{
	if (ray->side_dist.x < ray->side_dist.y)
	{
		ray->side_dist.x += ray->delta_dist.x;
		ray->map_x += ray->step.x;
		ray->hit_side = 0;
	}
	else
	{
		ray->side_dist.y += ray->delta_dist.y;
		ray->map_y += ray->step.y;
		ray->hit_side = 1;
	}
}

void	perform_dda(void)
{
	t_camera		*camera;
	t_ray			*ray;
	t_map			*map;

	camera = get_camera();
	ray = &camera->ray;
	map = get_map();
	ray->is_door = 0;
	while (1)
	{
		dda_calculate(ray);
		if (ray->map_x < 0 || ray->map_x >= map->width || \
			ray->map_y < 0 || ray->map_y >= map->height)
			break ;
		if (map->grid[ray->map_y * map->width + ray->map_x] == 1)
		{
			ray->is_door = 0;
			break ;
		}
		if (map->grid[ray->map_y * map->width + ray->map_x] == 3)
		{
			ray->is_door = 1;
			break ;
		}
	}
}
