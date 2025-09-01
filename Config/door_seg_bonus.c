/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_seg_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 13:34:59 by yjazouli          #+#    #+#             */
/*   Updated: 2025/09/01 13:37:17 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	add_door_segment(t_mash *mash, t_door *door, uint32_t door_color)
{
	t_seg	seg;
	t_map	*map;

	map = get_map();
	if (is_wall(map, door->x - 1, door->y) || is_wall(map, door->x + 1,
			door->y))
	{
		seg.x = door->x;
		seg.y = door->y;
		seg.dir = SEG_DIR_HORIZ;
		seg.len = 1;
	}
	else
	{
		seg.x = door->x;
		seg.y = door->y;
		seg.dir = SEG_DIR_VERT;
		seg.len = 1;
	}
	add_seg(mash, &seg, door_color);
}

void	build_door_segs(t_mash *mash, t_map *map, uint32_t color)
{
	int		x;
	int		y;
	t_door	*door;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			door = get_door_at(get_game(), x, y);
			if (door)
				add_door_segment(mash, door, color);
			x++;
		}
		y++;
	}
}
