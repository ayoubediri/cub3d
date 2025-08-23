/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli@student.1337.ma <yjazouli>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 10:57:09 by yjazouli@st       #+#    #+#             */
/*   Updated: 2025/08/23 11:00:30 by yjazouli@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int get_idx(int x, int y, int width)
{
    return y * width + x;
}

int is_wall(t_map *map, int x, int y)
{
    if (!map || x < 0 || y < 0 || x >= map->width || y >= map->height)
        return 0;
    if (map->grid)
        return map->grid[y * map->width + x] == 1;
    return 0;
}

