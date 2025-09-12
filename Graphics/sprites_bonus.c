/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiri <adiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 10:36:25 by adiri             #+#    #+#             */
/*   Updated: 2025/09/12 10:45:23 by adiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_sprite_stripe(t_sprite_info *s, int stripe, double *z_buffer, \
	t_texture *texture)
{
	int		y;
	int		tex_y;
	int		color;
	double	step;
	double	tex_pos;

	if (s->transform_y > 0 && stripe > 0 && stripe < WIDTH && \
		s->transform_y < z_buffer[stripe])
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
			y += 1;
		}
	}
}

void	init_div(t_sprite_info *s)
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

void	draw_the_sprite_transform(t_gameplay *gameplay, int ent_index, \
	t_sprite_info *s_info, double *z_buffer)
{
	int			stripe;
	t_rend_ents	*ent;

	stripe = s_info->draw_start_x - 1;
	ent = gameplay->rend_ents;
	while (++stripe < s_info->draw_end_x)
	{
		if (s_info->type == ENTITY_GHOST)
		{
			if (ent[ent_index].ent->texture)
				draw_sprite_type(s_info, stripe, \
					ent[ent_index].ent->texture, z_buffer);
		}
		else if (s_info->type == ENTITY_PELLET)
		{
			draw_sprite_type(s_info, stripe, \
				&gameplay->pellet_texture, z_buffer);
		}
	}
}

void	render_sprites(double *z_buffer)
{
	t_gameplay		*gameplay;
	t_rend_ents		*ent;
	t_sprite_info	s_info;
	int				i;

	gameplay = get_gameplay();
	ent = gameplay->rend_ents;
	sort_sprites_by_distance(gameplay->player.ent, ent);
	i = 0;
	while (i < gameplay->rend_ent_count)
	{
		if (gameplay->rend_ents[i].ent->type == ENTITY_PLAYER || \
			gameplay->rend_ents[i].ent->gone)
		{
			i++;
			continue ;
		}
		s_info.type = gameplay->rend_ents[i].ent->type;
		init_div(&s_info);
		calculate_sprite_transform(gameplay->player.ent, ent[i].ent, &s_info);
		draw_the_sprite_transform(gameplay, i, &s_info, z_buffer);
		i++;
	}
}

void	draw_sprites(double *z_buffer)
{
	t_gameplay	*gameplay;

	gameplay = get_gameplay();
	if (gameplay->entity_count > 1)
		render_sprites(z_buffer);
}
