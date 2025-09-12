/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_flood_fill.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiri <adiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:42:56 by adiri             #+#    #+#             */
/*   Updated: 2025/09/11 10:47:41 by adiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	**get_neighbors(void)
{
	static int	north[2] = {0, -1};
	static int	east[2] = {1, 0};
	static int	south[2] = {0, 1};
	static int	west[2] = {-1, 0};
	static int	*neighbors[4] = {north, south, west, east};

	return (neighbors);
}

void	bfs_while(t_bfs *bfs, t_map *map, int *count, t_bfs_info *info)
{
	int	i;

	while (info->front < info->rear)
	{
		info->current = bfs->queue[info->front++];
		info->x = info->current % map->width;
		info->y = info->current / map->width;
		if (map->grid[info->current] == CELL_PELLET)
			(*count)--;
		i = -1;
		while (++i < 4)
		{
			info->nx = info->x + info->neighbors[i][0];
			info->ny = info->y + info->neighbors[i][1];
			if (is_wall(map, info->nx, info->ny))
				continue ;
			info->n_idx = info->ny * map->width + info->nx;
			if (!bfs->visited[info->n_idx])
			{
				bfs->visited[info->n_idx] = 1;
				bfs->queue[info->rear++] = info->n_idx;
			}
		}
	}
}

void	bfs_flood_fill(t_map *map, t_vec2 *start, int *count, int **neighbors)
{
	t_bfs		*bfs;
	t_bfs_info	info;

	bfs = get_bfs();
	info.start_idx = (int)start->y * map->width + (int)start->x;
	info.front = 0;
	info.rear = 0;
	info.neighbors = neighbors;
	bfs->queue[info.rear++] = info.start_idx;
	bfs->visited[info.start_idx] = 1;
	bfs_while(bfs, map, count, &info);
}

void	check_all_pellets(void)
{
	int			num_pellets;
	t_gameplay	*gameplay;
	t_vec2		*start;

	gameplay = get_gameplay();
	num_pellets = gameplay->pellet_count;
	start = &gameplay->player.ent->pos;
	bfs_flood_fill(get_map(), start, &num_pellets, get_neighbors());
	if (num_pellets != 0)
	{
		fprintf(stderr, "Pellets unreachable: %d\n", num_pellets);
		parse_error("Not all pellets are reachable from the player \
start position");
	}
}
