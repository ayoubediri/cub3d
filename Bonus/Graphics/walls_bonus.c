/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 11:12:33 by yjazouli          #+#    #+#             */
/*   Updated: 2025/09/03 10:20:12 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static t_shape	fill_door_coords(t_seg *seg)
{
	int		px0;
	int		py0;
	int		px1;
	int		py1;
	t_shape	d;

	if (seg->dir == SEG_DIR_HORIZ)
	{
		world_to_minimap((double)(seg->x), (double)(seg->y) + 0.5, &px0, &py0);
		world_to_minimap((double)(seg->x + seg->len), (double)(seg->y) + 0.5,
			&px1, &py1);
	}
	else
	{
		world_to_minimap((double)(seg->x) + 0.5, (double)(seg->y), &px0, &py0);
		world_to_minimap((double)(seg->x) + 0.5, (double)(seg->y + seg->len),
			&px1, &py1);
	}
	d.p1.x = px0;
	d.p1.y = py0;
	d.p2.x = px1;
	d.p2.y = py1;
	return (d);
}

static void	draw_door(t_minimap *mm, t_seg *seg, int enabled)
{
	t_shape	d;
	double	inset;

	d = fill_door_coords(seg);
	d.tmp_dx = d.p2.x - d.p1.x;
	d.tmp_dy = d.p2.y - d.p1.y;
	d.tmp_dist = sqrt(d.tmp_dx * d.tmp_dx + d.tmp_dy * d.tmp_dy);
	inset = mm->cell_px / 5;
	if (inset < 1.0)
		inset = 1.0;
	d.tmp_nx = d.tmp_dx / d.tmp_dist;
	d.tmp_ny = d.tmp_dy / d.tmp_dist;
	d.p1.x += (int)(round(d.tmp_nx * inset));
	d.p1.y += (int)(round(d.tmp_ny * inset));
	d.p2.x -= (int)(round(d.tmp_nx * inset));
	d.p2.y -= (int)(round(d.tmp_ny * inset));
	d.color = seg->color;
	if (enabled)
		d.color = 0x00FF00;
	d.clip_x = mm->ox + 2;
	d.clip_y = mm->oy + 2;
	d.clip_w = mm->size_px - 4;
	d.clip_h = mm->size_px - 4;
	draw_line(d);
}

static void	draw_wall(t_minimap *mm, t_seg *seg)
{
	int		px0;
	int		py0;
	int		px1;
	int		py1;
	t_shape	wall;

	world_to_minimap((double)seg->x, (double)seg->y, &px0, &py0);
	if (seg->dir == SEG_DIR_HORIZ)
		world_to_minimap((double)(seg->x + seg->len), (double)seg->y, &px1,
			&py1);
	else
		world_to_minimap((double)seg->x, (double)(seg->y + seg->len), &px1,
			&py1);
	wall.p1.x = px0;
	wall.p1.y = py0;
	wall.p2.x = px1;
	wall.p2.y = py1;
	wall.color = seg->color;
	wall.clip_x = mm->ox + 2;
	wall.clip_y = mm->oy + 2;
	wall.clip_w = mm->size_px - 4;
	wall.clip_h = mm->size_px - 4;
	draw_line(wall);
}

static void	draw_segment(t_minimap *mm, t_seg *seg)
{
	int	enabled;

	if (door_exists(seg->x, seg->y) && seg->color != mm->col_wall)
	{
		enabled = door_is_open(seg->x, seg->y);
		draw_door(mm, seg, enabled);
	}
	else
	{
		draw_wall(mm, seg);
	}
}

void	draw_walls(t_minimap *mm)
{
	int		i;
	t_seg	*seg;

	i = 0;
	while (i < mm->mash.seg_count)
	{
		seg = &mm->mash.segs[i];
		draw_segment(mm, seg);
		i++;
	}
}
