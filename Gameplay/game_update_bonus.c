/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_update_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiri <adiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 05:53:27 by adiri             #+#    #+#             */
/*   Updated: 2025/09/12 06:46:53 by adiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	update_camera(void)
{
	t_gameplay	*gameplay;
	t_camera	*camera;

	gameplay = get_gameplay();
	camera = &gameplay->camera;
	camera->pos.x = gameplay->player.ent->pos.x;
	camera->pos.y = gameplay->player.ent->pos.y;
	camera->dir.x = gameplay->player.ent->dir.x;
	camera->dir.y = gameplay->player.ent->dir.y;
	camera->plane.x = -camera->dir.y * camera->plane_scale;
	camera->plane.y = camera->dir.x * camera->plane_scale;
	camera->floor.dir_x0 = camera->dir.x - camera->plane.x;
	camera->floor.dir_y0 = camera->dir.y - camera->plane.y;
	camera->floor.dir_x1 = camera->dir.x + camera->plane.x;
	camera->floor.dir_y1 = camera->dir.y + camera->plane.y;
	camera->floor.player_z = HALF_HEIGHT;
}

void	update_coins_text(double dt)
{
	static double	last_update_time = 0.0;
	int				idx;

	last_update_time += dt;
	if (last_update_time > TOTAL_FRAMES_SECONDS)
		last_update_time -= TOTAL_FRAMES_SECONDS;
	idx = (int)(last_update_time / (FLIB_COINS_ANIM_TIME));
	get_gameplay()->pellet_texture = get_coin_texture()[idx];
}

void	game_update(double dt)
{
	t_gameplay	*gp;

	update_movement();
	update_camera();
	update_coins_text(dt);
	minimap_update(dt);
	ghosts_update(dt);
	timers_update(dt);
	gp = get_gameplay();
	if (gp && gp->player.ent && gp->player.ent->hp <= 0)
	{
		lose_screen();
		fprintf(stderr, "Player died\n");
		leave_game(0);
	}
}
