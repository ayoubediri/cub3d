/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 16:00:52 by yjazouli          #+#    #+#             */
/*   Updated: 2025/08/22 16:16:14 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d_bonus.h"

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


unsigned int get_texture_color(t_texture *texture, int x, int y)
{
    char    *dst;

    if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
        return (0);
    dst = texture->addr + (y * texture->line_length + x * (texture->bpp / 8));
    return (*(unsigned int*)dst);
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
		if (map->grid[ray->map_y * map->width + ray->map_x] == 1)
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

void calc_wall_tex_idx(void)
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

void calc_tex_x(void)
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

void calc_texture(void)
{
	calc_perp_wall_dist();
	calc_wall_tex_idx();
	calc_tex_x();

}

void draw_floor(int x, int y)
{
	t_camera	*camera;
	t_texture	*floor_txt;
	t_floor		info;

	camera = get_camera();
	floor_txt = &get_game()->floor_texture;
	info.player_z = HALF_HEIGHT;
	info.dir_x0 = camera->dir.x - camera->plane.x;
	info.dir_y0 = camera->dir.y - camera->plane.y;
	info.dir_x1 = camera->dir.x + camera->plane.x;
	info.dir_y1 = camera->dir.y + camera->plane.y;
	while (y < HEIGHT)
	{
		info.row_distance = info.player_z / (y - HEIGHT / 2);
		info.floor_step_x = info.row_distance * (info.dir_x1 - info.dir_x0) / WIDTH;
		info.floor_step_y = info.row_distance * (info.dir_y1 - info.dir_y0) / WIDTH;
		info.floor_x = camera->pos.x + info.row_distance * info.dir_x0 + info.floor_step_x * x;
		info.floor_y = camera->pos.y + info.row_distance * info.dir_y0 + info.floor_step_y * x;
		info.tex_x = (int)(info.floor_x * floor_txt->width) % floor_txt->width;
		info.tex_y = (int)(info.floor_y * floor_txt->height) % floor_txt->height;
		info.color = *(unsigned int *)(floor_txt->addr +
			(info.tex_y * floor_txt->line_length + info.tex_x * (floor_txt->bpp / 8)));
		pixel_put(x, y, info.color);
		y++;
	}
}

void draw_sky(int x)
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
	sky.tex_x = (sky.tex_x % sky.texture->width + sky.texture->width) % sky.texture->width;
	y = 0;
	while (y <= camera->ray.start)
	{
		sky.tex_y = (int)(y * sky.texture->height / (HALF_HEIGHT)) % sky.texture->height;
		sky.color = get_texture_color(sky.texture, sky.tex_x, sky.tex_y);
		pixel_put(x, y, sky.color);
		y++;
	};
}

void draw_ceiling_and_floor(int x)
{
	t_camera	*camera;

	camera = get_camera();
	draw_sky(x);
	draw_floor(x, camera->ray.end);
}

int get_wall_color(t_ray *ray, double step, double *tex_pos)
{
	int			tex_y;
	int			color;
	t_texture 	*texture;

	texture = ray->texture;
	tex_y = (int)(*tex_pos) & (texture->height - 1);
	*tex_pos += step;
	color = get_texture_color(texture, ray->tex_x, tex_y);
	return (color);
}

void draw_wall(int x)
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
	tex_pos = (ray->start - HEIGHT / 2 + ray->height / 2) * step;
	while (y < ray->end)
	{
		pixel_put(x, y, get_wall_color(ray, step, &tex_pos));
		y++;
	}
}


// void render_sprites(double *z_buffer)
// {
// 	t_gameplay	*gameplay;
// 	t_player	*player;

// 	gameplay = get_gameplay();
// 	sort_sprites(player);
// 	for (int i = 0; i < gameplay->sprite_count; i++)
// 	{
// 		init_sprite(i);
// 		calc_sprite_transform();
// 		calc_sprite_screen_pos();
// 		calc_sprite_height();
// 		calc_sprite_width();
// 		draw_sprite(z_buffer);
// 	}
// }

// void draw_sprites(double *z_buffer)
// {
// 	t_gameplay	*gameplay;

// 	gameplay = get_gameplay();
// 	if (gameplay->sprite_count > 0)
// 		render_sprites(z_buffer);
// }

void raycasting(void)
{
	int	x;
	double z_buffer[WIDTH];
	t_camera	*camera;

	x = 0;
	camera = get_camera();
	while (x < WIDTH)
	{
		init_raycasting(x);
		init_steps();
		perform_dda();
		calc_texture();
		draw_ceiling_and_floor(x);
		draw_wall(x);
		z_buffer[x] = camera->ray.perp_wall_dist;
		x++;
	}
	// draw_sprites(z_buffer);
}
