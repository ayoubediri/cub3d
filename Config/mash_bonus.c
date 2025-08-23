/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mash_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli@student.1337.ma <yjazouli>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 11:01:57 by yjazouli@st       #+#    #+#             */
/*   Updated: 2025/08/23 12:11:27 by yjazouli@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void build_mask(t_mash *mash, t_map *map)
{
    int y;
    int x;
    uint8_t mask;

    x = 0;
    y = 0;
    mask = 0;
    while (y < map->height)
    {
        x = 0;
        while (x < map->width)
        {
            mask = 0;
            if (is_wall(map, x, y))
            {
                if (y > 0 && is_wall(map, x, y - 1))
                    mask |= 1 << 0;
                if (y > 0 && x < map->width - 1 && is_wall(map, x + 1, y - 1))
                    mask |= 1 << 1;
                if (x < map->width - 1 && is_wall(map, x + 1, y))
                    mask |= 1 << 2;
                if (y < map->height - 1 && x < map->width - 1 && is_wall(map, x + 1, y + 1))
                    mask |= 1 << 3;
                if (y < map->height - 1 && is_wall(map, x, y + 1))
                    mask |= 1 << 4;
                if (y < map->height - 1 && x > 0 && is_wall(map, x - 1, y + 1))
                    mask |= 1 << 5;
                if (x > 0 && is_wall(map, x - 1, y))
                    mask |= 1 << 6;
                if (y > 0 && x > 0 && is_wall(map, x - 1, y - 1))
                    mask |= 1 << 7;
            }
            mash->nbr_mask[y * map->width + x] = mask;
            x++;
        }
        y++;
    }
}

void init_mash(t_mash *mash, t_map *map)
{
    if (mash->nbr_mask)
    {
        ft_free(mash->nbr_mask);
        mash->nbr_mask = NULL;
    }
    if (mash->segs)
    {
        ft_free(mash->segs);
        mash->segs = NULL;
    }
    mash->dirty = 1;
    mash->min_x = 0;
    mash->min_y = 0;
    mash->max_x = map->width;
    mash->max_y = map->height;
    mash->segs = NULL;
    mash->seg_count = 0;
    mash->seg_capacity = 0;
    mash->nbr_mask = ft_calloc((size_t)map->width * map->height, sizeof(uint8_t));
    build_mask(mash, map);
}

void minimap_build_cache(t_minimap *mm)
{
    init_mash(&mm->mash, mm->src_map);
    mm->mash.seg_count = 0;
    horirz_seg(&mm->mash, mm->src_map, mm->col_wall);
    vert_seg(&mm->mash, mm->src_map, mm->col_wall);
    mm->mash.dirty = 0;
    mm->build_stamp++;
}

void minimap_ensure_built(t_minimap *minimap)
{
    if (minimap->mash.dirty)
        minimap_build_cache(minimap);
}

