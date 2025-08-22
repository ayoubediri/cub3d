/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:23:31 by yjazouli          #+#    #+#             */
/*   Updated: 2025/08/22 09:41:16 by yjazouli         ###   ########.fr       */
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


int	check_corners(double corners[4][2])
{
	t_game		*game;
	t_map		*map;
	int	map_x;
	int	map_y;
	int	i;

	game = get_game();
	map = &game->map;
	if (!map || !map->grid || !map->doors_grid)
		return (1);
	i = 0;
	while (i < 4)
	{
		map_x = (int)corners[i][0];
		map_y = (int)corners[i][1];
		if (map_x < 0 || map_x >= map->width
			|| map_y < 0 || map_y >= map->height)
			return (1);
		if (map->grid[map_y * map->width + map_x] > 0)
			return (1);
		i++;
	}
	return (0);
}

int	check_collision(double new_x, double new_y)
{
	double		corners[4][2];
	double		buffer;

	buffer = 0.05;
	corners[0][0] = new_x - buffer;
	corners[0][1] = new_y - buffer;
	corners[1][0] = new_x + buffer;
	corners[1][1] = new_y - buffer;
	corners[2][0] = new_x - buffer;
	corners[2][1] = new_y + buffer;
	corners[3][0] = new_x + buffer;
	corners[3][1] = new_y + buffer;
	if (check_corners(corners))
		return (1);
	return (0);
}

void move_player(int direction)
{
	t_entity	*ent;
	double		new_x;
	double		new_y;

	ent = get_game()->gameplay.player.ent;
	new_x = ent->pos.x + ent->dir.x * ent->vel.x * direction;
	new_y = ent->pos.y + ent->dir.y * ent->vel.x * direction;
	if (check_collision(new_x, new_y))
		return ;
	ent->prev.x = ent->pos.x;
	ent->prev.y = ent->pos.y;
	ent->pos.x = new_x;
	ent->pos.y = new_y;
}

// void	rotate_player(t_player *p, double dir)
// {
// 	double	dir_x;
// 	double	dir_y;
// 	double	angle;

// 	if (!p)
// 		return ;
// 	angle = dir * ROT_SPEED;
// 	dir_x = p->ent->dir.x * ;
// 	// p->dir_x = p->dir_x * cos(angle) - p->dir_y * sin(angle);
// 	// p->dir_y = p->dir_x * sin(angle) + p->dir_y * cos(angle);
// 	// old_planex = p->plane_x;
// 	// p->plane_x = old_planex * cos(angle) - p->plane_y * sin(angle);
// 	// p->plane_y = old_planex * sin(angle) + p->plane_y * cos(angle);
// }

void move_sideways(t_entity *ent, int direction)
{
	double	sx;
	double	sy;
	double	new_x;
	double	new_y;

	if (!ent)
		return ;
	if (direction < 0)
	{
		sx = -ent->dir.y;
		sy = ent->dir.x;
	}
	else
	{
		sx = ent->dir.y;
		sy = -ent->dir.x;
	}
	new_x = ent->pos.x + sx * ent->vel.x;
	new_y = ent->pos.y + sy * ent->vel.x;
	if (check_collision(new_x, new_y))
		return ;
	ent->prev.x = ent->pos.x;
	ent->prev.y = ent->pos.y;
	ent->pos.x = new_x;
	ent->pos.y = new_y;
}

void update_movement(void)
{
	t_game		*game;
	t_gameplay	*gameplay;
	t_player	*player;
	t_entity	*ent;

	game = get_game();
	gameplay = &game->gameplay;
	player = &gameplay->player;
	ent = player->ent;
	ent->vel = (t_vec2){MOVE_SPEED, MOVE_SPEED};
	if (game->keys[KEY_W])
		move_player(1);
	if (game->keys[KEY_S])
		move_player(-1);
	if (game->keys[KEY_A])
		move_sideways(ent, 1);
	if (game->keys[KEY_D])
		move_sideways(ent, -1);
	// if (game->keys[KEY_LEFT])
	// 	rotate_player(ent, 1);
	// if (game->keys[KEY_RIGHT])
	// 	rotate_player(ent, -1);
}

void update_camera(void)
{
	t_gameplay	*gameplay;
	t_camera	*camera;

	gameplay = get_gameplay();
	camera = &gameplay->camera;
	camera->pos.x = gameplay->player.ent->pos.x;
	camera->pos.y = gameplay->player.ent->pos.y;
	camera->dir.x = gameplay->player.ent->dir.x;
	camera->dir.y = gameplay->player.ent->dir.y;
	camera->plane.x = -camera->dir.y * camera->plane_scale;
	camera->plane.y = camera->dir.x * camera->plane_scale;
}

void	game_update(double dt)
{
	(void)dt;

	update_movement();
	update_camera();
	minimap_update(dt);
}

void init_raycasting(int x)
{
	t_camera	*camera;
	t_ray		*ray;

	camera = get_camera();
	ray = &camera->ray;
	ray->camera_x = 2 * x / (double)WIDTH - 1;
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
		if (ray->map_x < 0 || ray->map_x >= map->width || 
			ray->map_y < 0 || ray->map_y >= map->height)
			break;
		if (map->grid[ray->map_y * map->width + ray->map_x] > 0)
			break;
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
		if (y <= camera->ray.start)
			pixel_put(x, y, 0xFF000000);
		else if (y >= camera->ray.end)
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
	printf("Raycasting started...\n");
	printf("camera pos: (%.2f, %.2f)\n", get_camera()->pos.x, get_camera()->pos.y);
	printf("camera dir: (%.2f, %.2f)\n", get_camera()->dir.x, get_camera()->dir.y);
	printf("camera plane: (%.2f, %.2f)\n", get_camera()->plane.x, get_camera()->plane.y);
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
	minimap_render();
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
