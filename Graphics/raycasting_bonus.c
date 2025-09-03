/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 16:00:52 by yjazouli          #+#    #+#             */
/*   Updated: 2025/09/03 10:16:25 by yjazouli         ###   ########.fr       */
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
	ray->is_door = 0;
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

void calc_door_texture(t_ray *ray)
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

void calc_texture(void)
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
	while (y <= HEIGHT)
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

void	sort_sprites_by_distance(t_entity *player, t_rend_ents *ents)
{
	t_gameplay	*gameplay;
	int			i;
	int			j;
	double		dist[2];
	t_rend_ents	temp;

	gameplay = get_gameplay();
	i = 0;
	while (i < gameplay->rend_ent_count - 1)
	{
		j = 0;
		while (j < gameplay->rend_ent_count - i - 1)
		{
			dist[0] = (player->pos.x - ents[j].ent->pos.x) * (player->pos.x - ents[j].ent->pos.x)
				+ (player->pos.y - ents[j].ent->pos.y) * (player->pos.y - ents[j].ent->pos.y);
			dist[1] = (player->pos.x - ents[j + 1].ent->pos.x) * (player->pos.x - ents[j + 1].ent->pos.x)
				+ (player->pos.y - ents[j + 1].ent->pos.y) * (player->pos.y - ents[j + 1].ent->pos.y);
			if (dist[0] < dist[1])
			{
				temp = ents[j];
				ents[j] = ents[j + 1];
				ents[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}
static void calculate_sprite_transform(t_entity *player, t_entity *sprite, t_sprite_info *s)
{
    double sprite_x;
    double sprite_y;
    double inv_det;
	double plane_x;
	double plane_y;

    sprite_x = sprite->pos.x - player->pos.x;
    sprite_y = sprite->pos.y - player->pos.y;

	plane_x = -player->dir.y * get_camera()->plane_scale;
	plane_y = player->dir.x * get_camera()->plane_scale;
    inv_det = 1.0 / (plane_x * player->dir.y - player->dir.x * plane_y);
    s->transform_x = inv_det * (player->dir.y * sprite_x - player->dir.x * sprite_y);
    s->transform_y = inv_det * (-plane_y * sprite_x + plane_x * sprite_y);

    s->screen_x = (int)((WIDTH / 2) * (1 + s->transform_x / s->transform_y));
    s->height = abs((int)(HEIGHT / s->transform_y)) / s->v_div;
    s->width = abs((int)(HEIGHT / s->transform_y)) / s->u_div;

    s->draw_start_y = -s->height / 2 + HEIGHT / 2;
    if (s->draw_start_y < 0) s->draw_start_y = 0;
    s->draw_end_y = s->height / 2 + HEIGHT / 2;
    if (s->draw_end_y >= HEIGHT) s->draw_end_y = HEIGHT - 1;

    s->draw_start_x = -s->width / 2 + s->screen_x;
    if (s->draw_start_x < 0) s->draw_start_x = 0;
    s->draw_end_x = s->width / 2 + s->screen_x;
    if (s->draw_end_x >= WIDTH) s->draw_end_x = WIDTH - 1;
}

void draw_sprite_stripe(t_sprite_info *s, int stripe, double *z_buffer, t_texture *texture)
{
	int     y;
	int     tex_y;
	int     color;
	double  step;
	double  tex_pos;

	if (s->transform_y > 0 && stripe > 0 && stripe < WIDTH && s->transform_y < z_buffer[stripe])
	{
		step = 1.0 * texture->height / s->height;
		tex_pos = (s->draw_start_y - HALF_HEIGHT + s->height / 2) * step;
		y = s->draw_start_y;
		while (y < s->draw_end_y)
		{
			tex_y = (int)tex_pos & (texture->height - 1);
			tex_pos += step;
			color = get_texture_color(texture, s->tex_x, tex_y);
			if ((color != 0x000000))
				pixel_put(stripe, y, color);
			y+= 1;
		}
	}
}

void init_div(t_sprite_info *s)
{
	if (s->type == ENTITY_PELLET)
	{
		s->u_div = PELLET_U_DIV;
		s->v_div = PELLET_V_DIV;
	}
	else
	{
		s->u_div = GHOST_U_DIV;
		s->v_div = GHOST_V_DIV;
	}
}

void render_sprites(double *z_buffer)
{
	t_gameplay  	*gameplay;
    t_rend_ents    	*ent;
    t_sprite_info   s_info;
    int             i;
    int             stripe;

	gameplay = get_gameplay();
	ent = gameplay->rend_ents;
	sort_sprites_by_distance(gameplay->player.ent, ent);
	i = 0;
	while (i < gameplay->rend_ent_count)
    {
        if (gameplay->rend_ents[i].ent->type == ENTITY_PLAYER || gameplay->rend_ents[i].ent->gone)
        {
            i++;
            continue ;
        }
		s_info.type = gameplay->rend_ents[i].ent->type;
		init_div(&s_info);
		calculate_sprite_transform(gameplay->player.ent, ent[i].ent, &s_info);
		stripe = s_info.draw_start_x;
		while (stripe < s_info.draw_end_x)
		{
			if (s_info.type == ENTITY_GHOST)
			{
				if (gameplay->rend_ents[i].ent->texture)
				{
					s_info.tex_x = (int)(512 * (stripe - (-s_info.width / 2 + s_info.screen_x)) *
								  gameplay->rend_ents[i].ent->texture->width / s_info.width) / 512;
					draw_sprite_stripe(&s_info, stripe, z_buffer, gameplay->rend_ents[i].ent->texture);
				}
			}
			else if (s_info.type == ENTITY_PELLET)
			{
				s_info.tex_x = (int)(512 * (stripe - (-s_info.width / 2 + s_info.screen_x)) *
							  gameplay->pellet_texture.width / s_info.width) / 512;
				draw_sprite_stripe(&s_info, stripe, z_buffer, &gameplay->pellet_texture);
			}
			stripe++;
		}
        i++;
    }
}

void draw_sprites(double *z_buffer)
{
	t_gameplay	*gameplay;

	gameplay = get_gameplay();
	if (gameplay->entity_count > 1)
		render_sprites(z_buffer);
}

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
	draw_sprites(z_buffer);
}
