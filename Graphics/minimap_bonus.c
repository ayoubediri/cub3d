/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 11:31:18 by yjazouli          #+#    #+#             */
/*   Updated: 2025/09/01 14:50:53 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	draw_border(t_minimap *mm)
{
	t_shape	border;

	border.p1.x = mm->ox;
	border.p1.y = mm->oy;
	border.width = mm->size_px;
	border.height = mm->size_px;
	border.color = mm->col_border;
	border.clip_x = 0;
	border.clip_y = 0;
	border.clip_w = WIDTH;
	border.clip_h = HEIGHT;
	border.tmp_x = 0;
	border.tmp_y = 0;
	border.tmp_err = 0;
	draw_rect(border);
}

static void	draw_background(t_minimap *mm)
{
	t_shape	background;

	background.p1.x = mm->ox + 2;
	background.p1.y = mm->oy + 2;
	background.width = mm->size_px - 4;
	background.height = mm->size_px - 4;
	background.color = mm->col_bg;
	background.clip_x = 0;
	background.clip_y = 0;
	background.clip_w = WIDTH;
	background.clip_h = HEIGHT;
	background.tmp_x = 0;
	background.tmp_y = 0;
	background.tmp_err = 0;
	draw_rect(background);
}

void	world_to_minimap(double wx, double wy, int *px, int *py)
{
	t_minimap	*mm;
	double		map_x;
	double		map_y;

	mm = &get_gameplay()->minimap;
	map_x = (wx - mm->world_offset_x) * mm->world_to_px;
	map_y = (wy - mm->world_offset_y) * mm->world_to_px;
	*px = mm->content_x + (int)map_x;
	*py = mm->content_y + (int)map_y;
}

void	minimap_render(void)
{
	t_minimap	*mm;
	t_gameplay	*gameplay;

	gameplay = get_gameplay();
	mm = &gameplay->minimap;
	draw_border(mm);
	draw_background(mm);
	draw_walls(mm);
	draw_pacman(&mm->pacman);
	draw_entities(gameplay->entities);
}
