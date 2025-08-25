/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:15:18 by yjazouli          #+#    #+#             */
/*   Updated: 2025/08/24 12:03:55 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	move_player(int direction)
{
	t_entity	*ent;
	double		dx;
	double		dy;

	if (direction == 0)
		return ;
	ent = get_game()->gameplay.player.ent;
	if (!ent)
		return ;
	dx = ent->dir.x * ent->vel.x * (double)direction;
	dy = ent->dir.y * ent->vel.x * (double)direction;
	entity_try_move_by(ent, dx, dy);
}

void	move_sideways(t_entity *ent, int direction)
{
	double	sx;
	double	sy;
	double	dx;
	double	dy;

	if (!ent)
		return ;
	if (direction < 0)
	{
		sx = -ent->dir.y;
		sy = ent->dir.x;
	}
	else
	{
		sx = ent->dir.y;
		sy = -ent->dir.x;
	}
	dx = sx * ent->vel.x;
	dy = sy * ent->vel.x;
	entity_try_move_by(ent, dx, dy);
}

void	rotate_player(t_entity *ent, double angle)
{
	double	old_x;

	old_x = ent->dir.x;
	ent->dir.x = ent->dir.x * cos(angle) - ent->dir.y * sin(angle);
	ent->dir.y = old_x * sin(angle) + ent->dir.y * cos(angle);
}

void	update_movement(void)
{
	t_game		*game;
	t_gameplay	*gameplay;
	t_player	*player;
	t_entity	*ent;

	game = get_game();
	gameplay = &game->gameplay;
	player = &gameplay->player;
	ent = player->ent;
	ent->vel = (t_vec2){MOVE_SPEED, MOVE_SPEED};
	if (game->keys[KEY_W])
		move_player(1);
	if (game->keys[KEY_S])
		move_player(-1);
	if (game->keys[KEY_A])
		move_sideways(ent, 1);
	if (game->keys[KEY_D])
		move_sideways(ent, -1);
	if (game->keys[KEY_LEFT])
		rotate_player(ent, -ROT_SPEED);
	if (game->keys[KEY_RIGHT])
		rotate_player(ent, ROT_SPEED);
}
