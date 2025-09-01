/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:29:53 by yjazouli          #+#    #+#             */
/*   Updated: 2025/09/01 17:13:25 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	count_doors(void)
{
	int		x;
	int		y;
	int		len;
	int		count;
	t_parse	*parse;

	y = 0;
	count = 0;
	parse = get_parse();
	while (y < parse->height)
	{
		x = 0;
		len = strlen(parse->map[y]);
		while (x < len)
		{
			if (parse->map[y][x] == 'D')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

void	add_door(int *door_idx, int cell, int x, int y)
{
	int		idx;
	t_map	*map;

	map = get_map();
	idx = (*door_idx)++;
	map->doors[idx].x = x;
	map->doors[idx].y = y;
	map->doors[idx].enabled = 0;
	map->doors[idx].linked_index = -1;
	map->doors_grid[cell] = idx;
}
