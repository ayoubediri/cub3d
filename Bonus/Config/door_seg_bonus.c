/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_seg_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 13:34:59 by yjazouli          #+#    #+#             */
/*   Updated: 2025/09/03 10:23:14 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	add_door_segment_at(t_mash *mash, int x, int y, uint32_t door_color)
{
	t_seg	seg;
	t_map	*map;

	seg.x = x;
	seg.y = y;
	seg.len = 1;
	map = get_map();
	if (is_wall(map, x - 1, y) || is_wall(map, x + 1, y))
		seg.dir = SEG_DIR_HORIZ;
	else
		seg.dir = SEG_DIR_VERT;
	add_seg(mash, &seg, door_color);
}

void	build_door_segs(t_mash *mash, t_map *map, uint32_t color)
{
	int			x;
	int			y;
	int			w;
	int			h;
	int			idx;

	w = map->width;
	h = map->height;
	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			idx = y * w + x;
			if (map->grid[idx] == 3 || map->grid[idx] == 4)
				add_door_segment_at(mash, x, y, color);
			x++;
		}
		y++;
	}
}
