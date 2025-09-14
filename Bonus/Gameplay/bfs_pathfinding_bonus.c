/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_pathfinding_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiri <adiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 04:08:07 by adiri             #+#    #+#             */
/*   Updated: 2025/09/12 05:19:00 by adiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	bfs_init(t_bfs *bfs, int width, int height)
{
	bfs->width = width;
	bfs->height = height;
	bfs->capacity = width * height;
	bfs->visited = ft_malloc(bfs->capacity * sizeof(int));
	bfs->parent = ft_malloc(bfs->capacity * sizeof(int));
	bfs->queue = ft_malloc(bfs->capacity * sizeof(int));
	bfs->num_of_moves = ft_malloc(bfs->capacity * sizeof(int));
	memset(bfs->visited, 0, bfs->capacity * sizeof(int));
	memset(bfs->parent, -1, bfs->capacity * sizeof(int));
	memset(bfs->queue, 0, bfs->capacity * sizeof(int));
	memset(bfs->num_of_moves, 0, bfs->capacity * sizeof(int));
}

t_bfs	*get_bfs(void)
{
	static t_bfs	*bfs;

	if (!bfs)
	{
		bfs = ft_malloc(sizeof(t_bfs));
		bfs_init(bfs, get_map()->width, get_map()->height);
	}
	return (bfs);
}

void	init_pathfinding(t_bfs *bfs, t_bfs_info *info)
{
	if (info->start_idx < 0 || info->start_idx >= bfs->capacity || \
		info->end_idx < 0 || info->end_idx >= bfs->capacity)
		return ;
	memset(bfs->visited, 0, bfs->capacity * sizeof(int));
	memset(bfs->parent, -1, bfs->capacity * sizeof(int));
	memset(bfs->queue, 0, bfs->capacity * sizeof(int));
	memset(bfs->num_of_moves, 0, bfs->capacity * sizeof(int));
	info->neighbors = get_neighbors();
	bfs->queue[0] = info->start_idx;
	bfs->visited[info->start_idx] = 1;
	info->front = 0;
	info->rear = 1;
}

void	add_to_queue(t_bfs *bfs, t_map *map, t_bfs_info *info)
{
	int	i;

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
			bfs->parent[info->n_idx] = info->current;
			bfs->num_of_moves[info->n_idx] = \
			bfs->num_of_moves[info->current] + 1;
			bfs->queue[info->rear++] = info->n_idx;
		}
	}
}

int	bfs_find_path(t_bfs *bfs, t_map *map, t_vec2 *start_pos, t_vec2 *end_pos)
{
	t_bfs_info	info;

	memset(&info, 0, sizeof(t_bfs_info));
	info.start_idx = (int)start_pos->y * map->width + (int)start_pos->x;
	info.end_idx = (int)end_pos->y * map->width + (int)end_pos->x;
	init_pathfinding(bfs, &info);
	while (info.front < info.rear)
	{
		info.current = bfs->queue[info.front++];
		if (info.current == info.end_idx)
			return (1);
		if (bfs->num_of_moves[info.current] >= MAX_GHOST_MOVES)
			return (0);
		info.x = info.current % map->width;
		info.y = info.current / map->width;
		add_to_queue(bfs, map, &info);
	}
	return (0);
}
