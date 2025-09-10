/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ghosts_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 16:03:53 by yjazouli          #+#    #+#             */
/*   Updated: 2025/08/25 10:06:55 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	timers_update(double dt)
{
	t_gameplay	*gameplay;
	t_entity	*entities;
	int			i;

	i = 0;
	gameplay = get_gameplay();
	entities = gameplay->entities;
	while (i < gameplay->entity_count)
	{
		entity_update_timers(&entities[i], dt);
		i++;
	}
}

void	detect_state(t_ghost *ghost)
{
	double		dx;
	double		dy;
	double		dist_sq;
	t_entity	*player;
	double		detect_radius;

	player = get_gameplay()->player.ent;
	dx = player->pos.x - ghost->ent->pos.x;
	dy = player->pos.y - ghost->ent->pos.y;
	dist_sq = dx * dx + dy * dy;
	detect_radius = 5.0;
	if (dist_sq < detect_radius * detect_radius)
		ghost->state = GHOST_STATE_CHASING;
	else
		ghost->state = GHOST_STATE_IDLE;
}

void update_enemy_texture(t_ghost *ghost)
{
	t_texture **enemy;
	int			idx;

	if (!ghost || !ghost->ent)
		return ;
	enemy = enemy_texture();
	if (!enemy)
		return ;
	idx = ghost->ent->tex_idx;
	if (ghost->ent->path_timer <= 0.25)
		ghost->ent->texture = &enemy[idx][0];
	else if (ghost->ent->path_timer <= 0.5)
		ghost->ent->texture = &enemy[idx][1];
	else if (ghost->ent->path_timer <= 0.75)
		ghost->ent->texture = &enemy[idx][2];
	else if (ghost->ent->path_timer <= 1.0)
		ghost->ent->texture = &enemy[idx][3];
	else
	{
		ghost->ent->texture = &enemy[idx][0];
		ghost->ent->path_timer = 0.0;
	}
}

void move_entity(t_entity *ent, t_map *map, double dt)
{
	t_vec2	new_pos;

	new_pos.x = ent->pos.x + ent->vel.x * dt;
	new_pos.y = ent->pos.y + ent->vel.y * dt;
	if (!is_wall(map, new_pos.x, ent->pos.y))
		ent->pos.x = new_pos.x;
	if (!is_wall(map, ent->pos.x, new_pos.y))
		ent->pos.y = new_pos.y;
}

// typedef struct s_bfs	t_bfs;

// struct s_bfs
// {
// 	int							*queue;
// 	int							*parent;
// 	int							*visited;
// 	int							width;
// 	int							height;
// 	int							capacity;
// };

// void bfs_init(t_bfs *bfs, int width, int height)
// {
// 	bfs->width = width;
// 	bfs->height = height;
// 	bfs->capacity = width * height;
// 	bfs->visited = ft_malloc(bfs->capacity * sizeof(int));
// 	bfs->parent = ft_malloc(bfs->capacity * sizeof(int));
// 	bfs->queue = ft_malloc(bfs->capacity * sizeof(int));
// 	memset(bfs->visited, 0, bfs->capacity * sizeof(int));
// }

// void add_the_four_dir(t_bfs *bfs, t_map *map, int x, int y, int current)
// {
// 	int	neighbors[4][2] = {
// 		{0, -1}, // Up
// 		{0, 1},  // Down
// 		{-1, 0}, // Left
// 		{1, 0}   // Right
// 	};
// 	for (int i = 0; i < 4; i++)
// 	{
// 		int nx = x + neighbors[i][0];
// 		int ny = y + neighbors[i][1];
// 		if (is_wall(map, nx, ny))
// 			continue ;
// 		int n_idx = ny * map->width + nx;
// 		if (!bfs->visited[n_idx])
// 		{
// 			bfs->visited[n_idx] = 1;
// 			bfs->parent[n_idx] = current;
// 			bfs->queue[bfs->capacity++] = n_idx;
// 		}
// 	}
// }

// void update_ghost_movement(t_ghost *ghost, t_entity *player, t_map *map, double dt)
// {
// 	t_bfs	bfs;

// 	bfs_init(&bfs, map->width, map->height);
// }
// }

void	ghost_update(t_ghost *ghost, t_entity *player, t_map *map, double dt)
{
	(void)map;
	(void)player;
	ghost->ent->path_timer += dt;
	update_enemy_texture(ghost);
	// update_ghost_movement(ghost, player, map, dt);
}


void	ghosts_update(double dt)
{
	t_gameplay	*gameplay;
	t_ghost		*ghost;
	int			i;

	gameplay = get_gameplay();
	i = 0;
	while (i < gameplay->ghost_count)
	{
		ghost = &gameplay->ghosts[i];
		if (ghost->ent->gone)
		{
			i++;
			continue ;
		}
		detect_state(ghost);
		ghost_update(ghost, gameplay->player.ent, get_map(), dt);
		i++;
	}
}
