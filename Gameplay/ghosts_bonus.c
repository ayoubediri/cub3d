/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ghosts_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiri <adiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 05:37:59 by adiri             #+#    #+#             */
/*   Updated: 2025/09/12 05:47:56 by adiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	get_next_move(t_vec2 *next_pos, t_map *map, t_vec2 *ghost, \
	t_vec2 *player)
{
	int		end_idx;
	int		current;
	int		parent;
	t_bfs	*bfs;

	bfs = get_bfs();
	end_idx = (int)player->y * map->width + (int)player->x;
	current = end_idx;
	while (bfs->parent[current] != -1)
	{
		parent = bfs->parent[current];
		if (parent == (int)ghost->y * map->width + (int)ghost->x)
		{
			next_pos->x = current % map->width + 0.5;
			next_pos->y = current / map->width + 0.5;
			break ;
		}
		current = parent;
	}
}

t_vec2	get_next_step(t_bfs *bfs, t_map *map, t_vec2 *ghost, t_vec2 *player)
{
	t_vec2	next_pos;
	t_vec2	*start_pos;
	t_vec2	*end_pos;

	start_pos = ghost;
	end_pos = player;
	next_pos = (t_vec2){ghost->x, ghost->y};
	if (!bfs_find_path(bfs, map, start_pos, end_pos))
		return (next_pos);
	get_next_move(&next_pos, map, ghost, player);
	return (next_pos);
}

void	check_if_ghost_in_next_cell(t_ghost *ghost, t_vec2 direction)
{
	t_call_check	check;
	t_gameplay		*gameplay;
	t_ghost			*other_ghost;

	gameplay = get_gameplay();
	check.margin = 0.5;
	check.target_x = ghost->ent->pos.x + direction.x * check.margin;
	check.target_y = ghost->ent->pos.y + direction.y * check.margin;
	check.i = -1;
	while (++check.i < gameplay->ghost_count)
	{
		other_ghost = &gameplay->ghosts[check.i];
		if (other_ghost == ghost || other_ghost->ent->gone)
			continue ;
		check.dx = fabs(check.target_x - other_ghost->ent->pos.x);
		check.dy = fabs(check.target_y - other_ghost->ent->pos.y);
		if (check.dx < 0.5 && check.dy < 0.5)
		{
			ghost->ent->vel.x = 0;
			ghost->ent->vel.y = 0;
			return ;
		}
	}
	ghost->ent->vel.x = direction.x * ghost->base_speed;
	ghost->ent->vel.y = direction.y * ghost->base_speed;
}

void	get_direction(t_vec2 *direction, t_ghost *ghost, t_vec2 next_step)
{
	double	dx;
	double	dy;

	dx = next_step.x - ghost->ent->pos.x;
	dy = next_step.y - ghost->ent->pos.y;
	if (fabs(dx) > fabs(dy))
	{
		if (dx > 0)
			direction->x = 1;
		else
			direction->x = -1;
		direction->y = 0;
	}
	else
	{
		direction->x = 0;
		if (dy > 0)
			direction->y = 1;
		else
			direction->y = -1;
	}
}

void	update_ghost_movement(t_ghost *ghost, t_entity *player, \
	t_map *map, double dt)
{
	t_bfs	*bfs;
	t_vec2	next_step;
	t_vec2	direction;
	double	length;

	bfs = get_bfs();
	next_step = get_next_step(bfs, map, &ghost->ent->pos, &player->pos);
	direction.x = next_step.x - ghost->ent->pos.x;
	direction.y = next_step.y - ghost->ent->pos.y;
	length = sqrt(direction.x * direction.x + direction.y * direction.y);
	if (length > 0.1)
	{
		direction.x /= length;
		direction.y /= length;
	}
	else
	{
		direction.x = 0;
		direction.y = 0;
	}
	ghost->ent->vel.x = direction.x * ghost->base_speed;
	ghost->ent->vel.y = direction.y * ghost->base_speed;
	check_if_ghost_in_next_cell(ghost, direction);
	move_entity(ghost->ent, map, dt);
}
