/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mash_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 11:01:57 by yjazouli@st       #+#    #+#             */
/*   Updated: 2025/09/01 11:36:55 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_mash(t_mash *mash, t_map *map)
{
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
}

void	minimap_build_cache(t_minimap *mm)
{
	init_mash(&mm->mash, mm->src_map);
	mm->mash.seg_count = 0;
	build_border_segs(&mm->mash, mm->src_map, mm->col_wall);
	mm->mash.dirty = 0;
	mm->build_stamp++;
}

void	minimap_ensure_built(t_minimap *minimap)
{
	if (minimap->mash.dirty)
	{
		printf("HERE\n");
		minimap_build_cache(minimap);
	}
}
