/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seg_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 11:25:13 by yjazouli@st       #+#    #+#             */
/*   Updated: 2025/09/01 13:37:21 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	ensure_seg_capacity(t_mash *mash, int extra)
{
	int	newcap;

	if (mash->seg_capacity == 0)
	{
		mash->seg_capacity = 16;
		mash->segs = ft_calloc((size_t)mash->seg_capacity, sizeof(t_seg));
		return ;
	}
	if (mash->seg_count + extra <= mash->seg_capacity)
		return ;
	newcap = mash->seg_capacity;
	while (mash->seg_count + extra > newcap)
		newcap *= 2;
	mash->segs = ft_realloc(mash->segs, sizeof(t_seg) * newcap);
	memset(mash->segs + mash->seg_capacity, 0, sizeof(t_seg) * (newcap
			- mash->seg_capacity));
	mash->seg_capacity = newcap;
}

static void	add_tile_h_edges(t_mash *mash, int x, int y, uint32_t color)
{
	t_seg	seg;
	t_map	*map;

	map = get_map();
	if (y == 0 || !is_wall(map, x, y - 1))
	{
		seg.x = x;
		seg.y = y;
		seg.dir = SEG_DIR_HORIZ;
		seg.len = 1;
		add_seg(mash, &seg, color);
	}
	if (y == map->height - 1 || !is_wall(map, x, y + 1))
	{
		seg.x = x;
		seg.y = y + 1;
		seg.dir = SEG_DIR_HORIZ;
		seg.len = 1;
		add_seg(mash, &seg, color);
	}
}

static void	add_tile_v_edges(t_mash *mash, int x, int y, uint32_t color)
{
	t_seg	seg;
	t_map	*map;

	map = get_map();
	if (x == 0 || !is_wall(map, x - 1, y))
	{
		seg.x = x;
		seg.y = y;
		seg.dir = SEG_DIR_VERT;
		seg.len = 1;
		add_seg(mash, &seg, color);
	}
	if (x == map->width - 1 || !is_wall(map, x + 1, y))
	{
		seg.x = x + 1;
		seg.y = y;
		seg.dir = SEG_DIR_VERT;
		seg.len = 1;
		add_seg(mash, &seg, color);
	}
}

void	add_seg(t_mash *mash, t_seg *seg, uint32_t color)
{
	ensure_seg_capacity(mash, 1);
	seg->color = color;
	mash->segs[mash->seg_count] = *seg;
	mash->seg_count++;
}

void	build_border_segs(t_mash *mash, t_map *map, uint32_t color)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (is_wall(map, x, y))
			{
				add_tile_h_edges(mash, x, y, color);
				add_tile_v_edges(mash, x, y, color);
			}
			x++;
		}
		y++;
	}
	build_door_segs(mash, map, 0xFF0000);
}
