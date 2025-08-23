/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli@student.1337.ma <yjazouli>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 13:51:24 by yjazouli          #+#    #+#             */
/*   Updated: 2025/08/23 12:14:17 by yjazouli@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	setup_pacman(t_minimap *minimap, t_gameplay *gameplay)
{
	minimap->pacman.ent = gameplay->player.ent;
	minimap->pacman.anim_time = 0.0;
	minimap->pacman.mouth_open = 0.0;
	minimap->pacman.mouth_speed = 2.5;
	minimap->pacman.scale = 0.9;
}

void	setup_cell_size(t_minimap *minimap, t_map *map)
{
	int			maxdim;
	int			denom_w;
	int			denom_h;
	int			max_denom;
	int			preferred;
	const int	PREFERRED = 16;

	maxdim = imax(map->width, map->height);
	minimap->cell_px = minimap->size_px / maxdim;
	if (minimap->cell_px < 2)
		minimap->cell_px = 2;
	denom_w = imin(map->width, PREFERRED);
	denom_h = imin(map->height, PREFERRED);
	max_denom = imax(denom_w, denom_h);
	preferred = minimap->size_px / max_denom;
	if (preferred > minimap->cell_px)
		minimap->cell_px = preferred;
	if (minimap->cell_px > 64)
		minimap->cell_px = 64;
}

void	setup_defaults(t_minimap *minimap, t_mlx *mlx, t_map *map)
{
	minimap->col_bg = 0x000000;     
	minimap->col_wall = 0xFF0000FF; 
	minimap->col_pacman = 0xFFFFFF00;
	minimap->col_pellet = 0xFFFFFF00;
	minimap->col_border = 0xFFB0B0B0;
	minimap->padding = 4.0;
	minimap->size_px = (int)floor(mlx->height * 0.2);
	minimap->ox = mlx->width - minimap->size_px - 8;
	minimap->oy = 8;
	setup_cell_size(minimap, map);
	minimap->content_w = minimap->cell_px * map->width;
	minimap->content_h = minimap->cell_px * map->height;
	minimap->content_x = minimap->ox + (minimap->size_px - minimap->content_w)
		/ 2;
	minimap->content_y = minimap->oy + (minimap->size_px - minimap->content_h)
		/ 2;
	if (minimap->content_x < minimap->ox)
		minimap->content_x = minimap->ox;
	if (minimap->content_y < minimap->oy)
	{
		minimap->content_y = minimap->oy;
	}
	minimap->world_to_px = (double)minimap->cell_px;
	minimap->world_offset_x = 0.0;
	minimap->world_offset_y = 0.0;
}

void	setup_minimap(void)
{
	t_minimap	*minimap;
	t_gameplay	*gameplay;

	gameplay = get_gameplay();
	minimap = &gameplay->minimap;
	minimap->src_map = get_map();
	setup_pacman(minimap, gameplay);
	setup_defaults(minimap, get_mlx(), minimap->src_map);
	minimap->mash.dirty = 1;
	minimap_ensure_built(minimap);
}
