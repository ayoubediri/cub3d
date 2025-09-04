/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions_ent_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 11:05:54 by yjazouli          #+#    #+#             */
/*   Updated: 2025/09/04 12:49:02 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	entities_overlap(t_entity *a, t_entity *b, double x, double y)
{
	double	dx;
	double	dy;
	double	dist_sq;
	double	radius_sum;

	if (!a)
		return (0);
	dx = x - b->pos.x;
	dy = y - b->pos.y;
	dist_sq = dx * dx + dy * dy;
	radius_sum = a->radius + b->radius;
	return (dist_sq < radius_sum * radius_sum);
}

t_entity	*check_ent_overlap(t_entity *ent, double x, double y)
{
	int			i;
	t_entity	*ents;
	t_entity	*target;
	t_gameplay	*gameplay;

	i = 0;
	gameplay = get_gameplay();
	ents = gameplay->entities;
	while (i < gameplay->entity_count)
	{
		target = &ents[i];
		if (target == ent || target->gone)
		{
			i++;
			continue ;
		}
		if (entities_overlap(ent, target, x, y))
			return (target);
		i++;
	}
	return (NULL);
}

void	win_end(void)
{
	t_mlx		*mlx;
	t_texture	win_texture;

	mlx = get_mlx();
	win_texture = load_texture(WIN_TEXTURE_PATH);
	mlx_clear_window(mlx->mlx, mlx->win);
	stop_background_music();
	mlx_put_image_to_window(mlx->mlx, mlx->win, win_texture.img_ptr, HALF_WIDTH
		- 256, HALF_HEIGHT - 256);
	mlx_do_sync(mlx->mlx);
	system("aplay -q " WIN_SOUND_PATH " > /dev/null 2>&1 &");
	mlx_destroy_image(mlx->mlx, win_texture.img_ptr);
	sleep(9);
}

void	try_to_eat_pellet(t_entity *pellet)
{
	t_player	*player;

	player = &get_gameplay()->player;
	pellet->gone = 1;
	system("aplay -q " COIN_SOUND_PATH " > /dev/null 2>&1 &");
	player->pellets_collected++;
	if (player->pellets_collected >= player->pellets_total)
	{
		win_end();
		printf("All pellets collected! You win!\n");
		leave_game(0);
	}
}

int	resolve_overlap(t_entity *ent, double *nx, double *ny)
{
	t_entity	*overlap;

	overlap = check_ent_overlap(ent, *nx, *ny);
	if (overlap)
	{
		if (ent->type == ENTITY_PLAYER && overlap->type == ENTITY_PELLET)
			try_to_eat_pellet(overlap);
		else if (ent->type == ENTITY_PLAYER && overlap->type == ENTITY_GHOST)
			player_take_dmg(overlap->damage);
		else if (ent->type == ENTITY_GHOST && overlap->type == ENTITY_PLAYER)
			player_take_dmg(ent->damage);
		return (0);
	}
	return (0);
}
