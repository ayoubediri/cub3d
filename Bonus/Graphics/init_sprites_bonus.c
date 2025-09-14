/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiri <adiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 10:29:52 by adiri             #+#    #+#             */
/*   Updated: 2025/09/12 10:55:15 by adiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_sprite_type(t_sprite_info *s, int stripe, t_texture *text, \
	double *z_buffer)
{
	s->tex_x = (int)(512 * (stripe - (-s->width / 2 + s->screen_x)) * \
		text->width / s->width) / 512;
	draw_sprite_stripe(s, stripe, z_buffer, text);
}

void	get_dist_for_sort(t_entity *player, t_entity *ent, double *dist)
{
	dist[0] = (player->pos.x - ent->pos.x) * (player->pos.x - ent->pos.x)
		+ (player->pos.y - ent->pos.y) * (player->pos.y - ent->pos.y);
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
			get_dist_for_sort(player, ents[j].ent, dist);
			get_dist_for_sort(player, ents[j + 1].ent, &dist[1]);
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

void	init_the_sprite_transform(t_entity *player, t_entity *sprite, \
	t_sprite_info *s)
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;
	double	plane_x;
	double	plane_y;

	sprite_x = sprite->pos.x - player->pos.x;
	sprite_y = sprite->pos.y - player->pos.y;
	plane_x = -player->dir.y * get_camera()->plane_scale;
	plane_y = player->dir.x * get_camera()->plane_scale;
	inv_det = 1.0 / (plane_x * player->dir.y - player->dir.x * plane_y);
	s->transform_x = inv_det * (player->dir.y * sprite_x - \
		player->dir.x * sprite_y);
	s->transform_y = inv_det * (-plane_y * sprite_x + plane_x * sprite_y);
	s->screen_x = (int)(HALF_WIDTH)*(1 + s->transform_x / s->transform_y);
	s->height = abs((int)(HEIGHT / s->transform_y)) / s->v_div;
	s->width = abs((int)(HEIGHT / s->transform_y)) / s->u_div;
}

void	calculate_sprite_transform(t_entity *player, t_entity *sprite, \
	t_sprite_info *s)
{
	init_the_sprite_transform(player, sprite, s);
	s->draw_start_y = -s->height / 2 + HALF_HEIGHT;
	if (s->draw_start_y < 0)
		s->draw_start_y = 0;
	s->draw_end_y = s->height / 2 + HALF_HEIGHT;
	if (s->draw_end_y >= HEIGHT)
		s->draw_end_y = HEIGHT - 1;
	s->draw_start_x = -s->width / 2 + s->screen_x;
	if (s->draw_start_x < 0)
		s->draw_start_x = 0;
	s->draw_end_x = s->width / 2 + s->screen_x;
	if (s->draw_end_x >= WIDTH)
		s->draw_end_x = WIDTH - 1;
}
