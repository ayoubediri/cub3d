/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:23:31 by yjazouli          #+#    #+#             */
/*   Updated: 2025/08/20 20:21:29 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	game_loop(void)
{
	t_engine	*engine;

	engine = get_engine();
	game_tick(engine);
	return (0);
}

static int	leave_game(void)
{
	clean_exit(0);
	return (1);
}

void	game_update(double dt)
{
	(void)dt;
}

void init_raycasting(int x)
{
	t_camera	*camera;
	t_mlx		*mlx;
	t_ray		*ray;

	camera = get_camera();
	mlx = get_mlx();
	ray = &camera->ray;

	ray->camera_x = 2 * x / (double)mlx->width - 1;
	ray->dir.x = camera->dir.x + camera->plane.x * ray->camera_x;
	ray->dir.y = camera->dir.y + camera->plane.y * ray->camera_x;
	ray->map_x = (int)camera->pos.x;
	ray->map_y = (int)camera->pos.y;
	ray->delta_dist.x = fabs(1 / ray->dir.x);
	ray->delta_dist.y = fabs(1 / ray->dir.y);
	ray->hit_side = 0;
	ray->perp_wall_dist = 0.0;
}

void init_steps(void)
{
	t_camera	*camera;
	t_ray		*ray;

	camera = get_camera();
	ray = &camera->ray;
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (camera->pos.x - ray->map_x) * ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map_x + 1.0 - camera->pos.x) * ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (camera->pos.y - ray->map_y) * ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map_y + 1.0 - camera->pos.y) * ray->delta_dist.y;
	}
}

void perform_dda(void)
{
	t_camera	*camera;
	t_ray		*ray;
	t_map		*map;

	camera = get_camera();
	ray = &camera->ray;
	map = get_map();
	while (1)
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
		if (map->grid[ray->map_y * WIDTH + ray->map_x] > 0)
			break ;
	}
}

void calc_perp_wall_dist(void)
{
	t_camera	*camera;
	t_ray		*ray;

	camera = get_camera();
	ray = &camera->ray;
	if (ray->hit_side == 0)
		ray->perp_wall_dist = (ray->map_x - camera->pos.x + (1 - ray->step.x) / 2) / ray->dir.x;
	else
		ray->perp_wall_dist = (ray->map_y - camera->pos.y + (1 - ray->step.y) / 2) / ray->dir.y;
	ray->height = (int)(HEIGHT / ray->perp_wall_dist);
	ray->start = -ray->height / 2 + HEIGHT / 2;
	if (ray->start < 0)
		ray->start = 0;
	ray->end = ray->height / 2 + HEIGHT / 2;
	if (ray->end >= HEIGHT)
		ray->end = HEIGHT - 1;
}

void calc_texture(void)
{
	calc_perp_wall_dist();
}

void draw_ceiling_and_floor(int x)
{
	t_camera	*camera;
	int		y;

	camera = get_camera();
	y = 0;
	while (y < HEIGHT)
	{
		if (y < camera->ray.start)
			pixel_put(x, y, 0xFFC00CCC);
		else if (y > camera->ray.end)
			pixel_put(x, y, 0xFF888888);
		y++;
	}
}

void draw_wall(int x)
{
	t_camera	*camera;
	t_ray		*ray;
	int			y;
	int			color;

	camera = get_camera();
	ray = &camera->ray;
	y = ray->start;
	while (y < ray->end)
	{
		color = 0xFF0000FF;
		pixel_put(x, y, color);
		y++;
	}
}

void raycasting(void)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		init_raycasting(x);
		init_steps();
		perform_dda();
		calc_texture();
		draw_ceiling_and_floor(x);
		draw_wall(x);
		x++;
	}
}

void	game_render(double alpha)
{
	(void)alpha;
	// clear_image();
	raycasting();
	// minimap
	put_image();
}

void	start_game(void)
{
	t_mlx	*mlx;

	mlx = get_mlx();
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
	{
		report_error("mlx", "failed to initialize session");
		clean_exit(1);
	}
	mlx->win = mlx_new_window(mlx->mlx, mlx->width, mlx->height, "Cub3d");
	if (!mlx->win)
	{
		report_error("mlx", "failed to create window");
		clean_exit(1);
	}
	mlx->img = mlx_new_image(mlx->mlx, mlx->width, mlx->height);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->line,
			&mlx->endian);
	mlx_hook(mlx->win, 17, 1L << 17, leave_game, NULL);
	mlx_hook(mlx->win, 2, 1L << 0, on_keypress, NULL);
	mlx_hook(mlx->win, 3, 1L << 1, on_keyrelease, NULL);
	mlx_loop_hook(mlx->mlx, game_loop, NULL);
	mlx_loop(mlx->mlx);
}
