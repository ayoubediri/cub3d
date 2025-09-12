/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ghost_move_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiri <adiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 05:23:00 by adiri             #+#    #+#             */
/*   Updated: 2025/09/12 05:26:36 by adiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	check_horizontal_movement(t_entity *ent, t_map *map, \
	t_vec2 new_pos, double buffer)
{
	double	check_x;
	double	buffer_value;

	buffer_value = buffer;
	if (ent->vel.x < 0)
		buffer_value = -buffer;
	check_x = new_pos.x + buffer_value;
	if (!is_blocked(map, check_x, ent->pos.y))
	{
		if (!is_blocked(map, check_x, ent->pos.y + buffer) && \
			!is_blocked(map, check_x, ent->pos.y - buffer))
			ent->pos.x = new_pos.x;
		else
			ent->vel.x = 0;
	}
	else
		ent->vel.x = 0;
}

void	check_vertical_movement(t_entity *ent, t_map *map, t_vec2 new_pos, \
	double buffer)
{
	double	check_y;
	double	buffer_value;

	buffer_value = buffer;
	if (ent->vel.y < 0)
		buffer_value = -buffer;
	if (!is_blocked(map, ent->pos.x, new_pos.y + buffer_value))
	{
		check_y = new_pos.y + buffer_value;
		if (!is_blocked(map, ent->pos.x + buffer, check_y) && \
			!is_blocked(map, ent->pos.x - buffer, check_y))
			ent->pos.y = new_pos.y;
		else
			ent->vel.y = 0;
	}
	else
		ent->vel.y = 0;
}

void	check_back_up_position(t_map *map, t_entity *ent, \
	double dt, double buffer)
{
	int	cell_x;
	int	cell_y;

	if (is_blocked(map, ent->pos.x, ent->pos.y) || \
		is_blocked(map, ent->pos.x + buffer, ent->pos.y) || \
		is_blocked(map, ent->pos.x - buffer, ent->pos.y) || \
		is_blocked(map, ent->pos.x, ent->pos.y + buffer) || \
		is_blocked(map, ent->pos.x, ent->pos.y - buffer))
	{
		ent->pos.x = ent->pos.x - ent->vel.x * dt;
		ent->pos.y = ent->pos.y - ent->vel.y * dt;
		ent->vel.x = 0;
		ent->vel.y = 0;
		cell_x = (int)ent->pos.x;
		cell_y = (int)ent->pos.y;
		ent->pos.x = cell_x + 0.5;
		ent->pos.y = cell_y + 0.5;
	}
}

void	move_entity(t_entity *ent, t_map *map, double dt)
{
	t_vec2	new_pos;
	double	buffer;

	buffer = 0.25;
	new_pos.x = ent->pos.x + ent->vel.x * dt;
	new_pos.y = ent->pos.y + ent->vel.y * dt;
	check_horizontal_movement(ent, map, new_pos, buffer);
	check_vertical_movement(ent, map, new_pos, buffer);
	check_back_up_position(map, ent, dt, buffer);
}

void	ghost_move_to_attack_player(t_ghost *ghost, t_entity *player, double dt)
{
	t_vec2	direction;
	double	length;

	direction.x = player->pos.x - ghost->ent->pos.x;
	direction.y = player->pos.y - ghost->ent->pos.y;
	length = sqrt(direction.x * direction.x + direction.y * direction.y);
	if (length != 0)
	{
		direction.x /= length;
		direction.y /= length;
	}
	ghost->ent->vel.x = direction.x * ghost->base_speed;
	ghost->ent->vel.y = direction.y * ghost->base_speed;
	move_entity(ghost->ent, get_map(), dt);
}
