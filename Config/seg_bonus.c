/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seg_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli@student.1337.ma <yjazouli>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 11:25:13 by yjazouli@st       #+#    #+#             */
/*   Updated: 2025/08/23 12:11:04 by yjazouli@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void ensure_seg_capacity(t_mash *mash, int extra)
{
    int newcap;

    if (mash->seg_capacity == 0)
    {
        mash->seg_capacity = 16;    
        mash->segs = ft_calloc((size_t)mash->seg_capacity, sizeof(t_seg));
        return ;
    }
    if (mash->seg_count + extra <= mash->seg_capacity)
        return;
    newcap = mash->seg_capacity;
    while (mash->seg_count + extra > newcap)
        newcap *= 2;
    mash->segs = ft_realloc(mash->segs, sizeof(t_seg) * newcap);
    memset(mash->segs + mash->seg_capacity, 0, sizeof(t_seg) * (newcap - mash->seg_capacity));
    mash->seg_capacity = newcap;
}


void add_seg(t_mash *mash, t_seg *seg, uint32_t color)
{
    ensure_seg_capacity(mash, 1);
    seg->color = color;
    mash->segs[mash->seg_count] = *seg;
    mash->seg_count++;
}

void	horirz_seg(t_mash *mash, t_map *map, uint32_t color)
{
    int		y;
    int		x;
    t_seg	seg;

    y = 0;
    while (y < map->height)
    {
        x = 0;
        while (x < map->width)
        {
            while (x < map->width && !is_wall(map, x, y))
                x++;
            if (x >= map->width)
                break;
            seg.x = x;
            seg.y = y;
            while (x < map->width && is_wall(map, x, y))
                x++;
            seg.len = x - seg.x;
            seg.dir = SEG_DIR_HORIZ;
            if (seg.len > 0)
                add_seg(mash, &seg, color);
        }
        y++;
    }
}

void vert_seg(t_mash *mash, t_map *map, uint32_t color)
{
    int x;
    int y;
    t_seg seg;

    x = 0;
    y = 0;
    while (x < map->width)
    {
        y = 0;
        while (y < map->height)
        {
            while (y < map->height && !is_wall(map, x, y))
                y++;
            if (y >= map->height)
                break;
            seg.x = x;
            seg.y = y;
            while (y < map->height && is_wall(map, x, y))
                y++;
            seg.len = y - seg.y;
            seg.dir = SEG_DIR_VERT;
            add_seg(mash, &seg, color);
        }
        x++;
    }
}
