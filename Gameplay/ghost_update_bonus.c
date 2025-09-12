/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ghost_update_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiri <adiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 05:25:51 by adiri             #+#    #+#             */
/*   Updated: 2025/09/12 05:28:20 by adiri            ###   ########.fr       */
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
	ghost->ent->vel = (t_vec2){0, 0};
	dx = player->pos.x - ghost->ent->pos.x;
	dy = player->pos.y - ghost->ent->pos.y;
	dist_sq = dx * dx + dy * dy;
	detect_radius = 10.0;
	if (dist_sq <= 1.5)
		ghost->state = GHOST_STATE_ATTACKING;
	else if (dist_sq < detect_radius * detect_radius)
		ghost->state = GHOST_STATE_CHASING;
	else
		ghost->state = GHOST_STATE_IDLE;
}

void	update_enemy_texture(t_ghost *ghost)
{
	t_texture	**enemy;
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

void	ghost_update(t_ghost *ghost, t_entity *player, t_map *map, double dt)
{
	ghost->ent->path_timer += dt;
	update_enemy_texture(ghost);
	if (ghost->state == GHOST_STATE_IDLE)
		return ;
	else if (ghost->state == GHOST_STATE_CHASING)
		update_ghost_movement(ghost, player, map, dt);
	else if (ghost->state == GHOST_STATE_ATTACKING)
		ghost_move_to_attack_player(ghost, player, dt);
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
