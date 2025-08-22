/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 16:03:53 by yjazouli          #+#    #+#             */
/*   Updated: 2025/08/22 21:25:42 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	entity_try_move_to(t_entity *ent, double nx, double ny)
{
	if (!ent)
		return (0);
	if (check_collision(nx, ny))
		return (0);
	ent->prev.x = ent->pos.x;
	ent->prev.y = ent->pos.y;
	ent->pos.x = nx;
	ent->pos.y = ny;
	return (1);
}

int	entity_try_move_by(t_entity *ent, double dx, double dy)
{
	double	nx;
	double	ny;

	if (!ent)
		return (0);
	nx = ent->pos.x + dx;
	ny = ent->pos.y + dy;
	if (entity_try_move_to(ent, nx, ny))
		return (1);
	if (dx != 0.0 && entity_try_move_to(ent, ent->pos.x + dx, ent->pos.y))
		return (1);
	if (dy != 0.0 && entity_try_move_to(ent, ent->pos.x, ent->pos.y + dy))
		return (1);
	return (0);
}

static void	entity_follow_path(t_entity *e, double dt)
{
	int	target_tile;

	int tx, ty;
	double target_x, target_y;
	double dx, dy, dist;
	double speed, move_x, move_y;
	if (!e || e->path_idx >= e->pathfinder.path_length)
		return ;
	target_tile = e->pathfinder.path[e->path_idx];
	bfs_idx_to_xy(target_tile, e->pathfinder.width, &tx, &ty);
	target_x = tx + 0.5;
	target_y = ty + 0.5;
	dx = target_x - e->pos.x;
	dy = target_y - e->pos.y;
	dist = sqrt(dx * dx + dy * dy);
	if (dist < 0.3)
	{
		e->path_idx++;
		return ;
	}
	speed = (e->vel.x > 0.0) ? e->vel.x : 2.0;
	move_x = (dx / dist) * speed * dt;
	move_y = (dy / dist) * speed * dt;
	entity_try_move_by(e, move_x, move_y);
}

static void	entity_request_path(t_entity *e, t_entity *player, t_map *map)
{
	int sx, sy, tx, ty;
	if (!e || !player || !map)
		return ;
	sx = (int)floor(e->pos.x);
	sy = (int)floor(e->pos.y);
	tx = (int)floor(player->pos.x);
	ty = (int)floor(player->pos.y);
	if (bfs_find_path(&e->pathfinder, map, sx, sy, tx, ty))
		e->path_idx = 1;
	else
		e->path_idx = e->pathfinder.path_length;
}

static void	enemy_try_damage_player(t_entity *enemy, t_entity *player)
{
    double	dx;
    double	dy;
    double	dist2;
    double	threshold;
    double	r_enemy;
    double	r_player;
    int		dmg;

    if (!enemy || !player || player->hp <= 0)
        return ;
    dx = player->pos.x - enemy->pos.x;
    dy = player->pos.y - enemy->pos.y;
    dist2 = dx * dx + dy * dy;
    r_enemy = (enemy->radius > 0.0 ? enemy->radius : 0.2);
    r_player = (player->radius > 0.0 ? player->radius : 0.25);
    threshold = r_enemy + r_player + 0.15;
    if (dist2 <= threshold * threshold)
    {
        dmg = 25;
       entity_apply_damage(player, dmg);
    }
}

void	entities_update(double dt)
{
    t_gameplay	*gp;
    t_entity	*ents;
    t_entity	*player;
    t_map		*map;
    int			i;

    gp = get_gameplay();
    if (!gp || !gp->entities || gp->entity_count <= 0)
        return ;
    ents = gp->entities;
    player = gp->player.ent;
    map = get_map();
    if (!player || !map)
        return ;
    for (i = 0; i < gp->entity_count; ++i)
    {
        t_entity *e = &ents[i];
        
        entity_update_timers(e, dt);
        
        if (!e || e == player || e->radius <= 0.0)
            continue ;
        e->path_timer += dt;

        
        if (e->path_timer > 0.5 || e->path_idx >= e->pathfinder.path_length)
        {
            entity_request_path(e, player, map);
            e->path_timer = 0.0;
        }
        entity_follow_path(e, dt);

        if (e->hp > 0)
            enemy_try_damage_player(e, player);

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
}
