/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_update_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 15:07:13 by yjazouli          #+#    #+#             */
/*   Updated: 2025/09/01 14:58:50 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	update_mouth(t_pacman *pac, double dt)
{
	double	cycles;

	pac->anim_time += dt;
	if (pac->mouth_speed > 0.0)
	{
		cycles = pac->anim_time * pac->mouth_speed;
		pac->mouth_open = 0.5 * (1.0 + sin(cycles * 2.0 * M_PI));
		if (pac->mouth_open < 0.05)
			pac->mouth_open = 0.05;
		if (pac->mouth_open > 0.95)
			pac->mouth_open = 0.95;
	}
}

void	minimap_update(double dt)
{
	t_gameplay	*gameplay;
	t_minimap	*minimap;
	t_entity	*player;
	double		screen_cx;
	double		screen_cy;

	gameplay = get_gameplay();
	minimap = &gameplay->minimap;
	update_mouth(&minimap->pacman, dt);
	player = minimap->pacman.ent;
	if (player && minimap->world_to_px > 0.0)
	{
		screen_cx = minimap->ox + (double)minimap->size_px * 0.5;
		screen_cy = minimap->oy + (double)minimap->size_px * 0.5;
		minimap->world_offset_x = player->pos.x - ((screen_cx
					- minimap->content_x) / minimap->world_to_px);
		minimap->world_offset_y = player->pos.y - ((screen_cy
					- minimap->content_y) / minimap->world_to_px);
	}
}
