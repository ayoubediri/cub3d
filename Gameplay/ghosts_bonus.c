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

#define PATH_REQUEST_INTERVAL 0.2
#define GHOST_BASE_SPEED 2.0
#define PATH_RECALC_DIST    0.9 
#define PATH_MIN_INTERVAL   0.12 
#define PATH_FAIL_BACKOFF   0.6 

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
	{
		ghost->state = GHOST_STATE_CHASING;
	}
	else
	{
		ghost->state = GHOST_STATE_IDLE;
	}
}

void	ghost_update(t_ghost *ghost, t_entity *player, t_map *map, double dt)
{
	t_entity	*e;
	double		speed;

	if (!ghost || !ghost->ent || !player || dt <= 0.0)
		return ;
	e = ghost->ent;
	if (e->gone)
		return ;

	/* --------------- IDLE ---------------- */
	if (ghost->state == GHOST_STATE_IDLE)
	{
		e->vel.x = 0.0;
		e->vel.y = 0.0;
		return ;
	}

	/* --------------- CHASING ---------------- */
	if (ghost->state == GHOST_STATE_CHASING)
	{
		double dx = player->pos.x - e->pos.x;
		double dy = player->pos.y - e->pos.y;
		double dist = sqrt(dx * dx + dy * dy);
		speed = (ghost->base_speed > 0.0) ? ghost->base_speed : GHOST_BASE_SPEED;

		int need_replan = 0;
		if (e->pathfinder.path_length == 0 || e->path_idx >= e->pathfinder.path_length)
			need_replan = 1;
		else
		{
			double pdx = player->pos.x - ghost->last_player_pos.x;
			double pdy = player->pos.y - ghost->last_player_pos.y;
			if (pdx*pdx + pdy*pdy > PATH_RECALC_DIST * PATH_RECALC_DIST)
				need_replan = 1;
		}

		/* cooldown bookkeeping */
		if (ghost->path_recalc_cooldown > 0.0)
			ghost->path_recalc_cooldown -= dt;

		/* request path only when necessary and cooldown expired */
		if (need_replan && ghost->path_recalc_cooldown <= 0.0)
		{
			if (request_path(e, player->pos.x, player->pos.y))
			{
				/* success: remember player pos and short cooldown */
				ghost->last_player_pos = player->pos;
				ghost->path_recalc_cooldown = PATH_MIN_INTERVAL;
			}
			else
			{
				/* failure: back off longer to avoid thrash */
				ghost->path_recalc_cooldown = PATH_FAIL_BACKOFF;
			}
		}

		/* follow path if present; otherwise fallback to smooth direct-steer */
		if (e->pathfinder.path_length > 0 && e->path_idx < e->pathfinder.path_length)
		{
			follow_path(e, dt, speed);
		}
		else
		{
			/* smooth direct steering fallback so ghost keeps moving while waiting */
			if (dist > 1e-6)
			{
				double mvx = (dx / dist) * speed * dt;
				double mvy = (dy / dist) * speed * dt;
				entity_try_move_by(e, mvx, mvy);
			}
		}
	}

	/* --------------- Update facing dir ---------------- */
	{
		double mvx = e->pos.x - e->prev.x;
		double mvy = e->pos.y - e->prev.y;
		double mlen = sqrt(mvx * mvx + mvy * mvy);
		if (mlen > 1e-6)
		{
			e->dir.x = mvx / mlen;
			e->dir.y = mvy / mlen;
		}
	}
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
