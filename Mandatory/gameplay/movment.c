/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 22:42:33 by yjazouli          #+#    #+#             */
/*   Updated: 2025/09/13 11:22:06 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid(double x, double y)
{
	t_game	*game;
	int		map_x;
	int		map_y;

	game = get_game();
	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_y < 0 || map_x >= game->map.width
		|| map_y >= game->map.height)
		return (0);
	return (game->map.grid[map_y][map_x] == 0);
}

static void	move_straight(t_player *player, bool *keys)
{
	double	new_x;
	double	new_y;
	double	move_step;

	if (keys[KEY_W] || keys[KEY_S])
	{
		if (keys[KEY_W])
			move_step = player->move_speed;
		else
			move_step = -player->move_speed;
		new_x = player->pos_x + player->dir_x * move_step;
		new_y = player->pos_y + player->dir_y * move_step;
		if (is_valid(new_x, player->pos_y))
			player->pos_x = new_x;
		if (is_valid(player->pos_x, new_y))
			player->pos_y = new_y;
	}
}

static void	move_lateral(t_player *player, bool *keys)
{
	double	new_x;
	double	new_y;
	double	move_step;

	if (keys[KEY_A] || keys[KEY_D])
	{
		if (keys[KEY_D])
			move_step = player->move_speed;
		else
			move_step = -player->move_speed;
		new_x = player->pos_x + player->plane_x * move_step;
		new_y = player->pos_y + player->plane_y * move_step;
		if (is_valid(new_x, player->pos_y))
			player->pos_x = new_x;
		if (is_valid(player->pos_x, new_y))
			player->pos_y = new_y;
	}
}

static void	rotate_camera(t_player *player, bool *keys)
{
	double	rotation;
	double	old_dir_x;
	double	old_plane_x;
	double	cos_rotation;
	double	sin_rotation;

	if (keys[KEY_RIGHT] || keys[KEY_LEFT])
	{
		if (keys[KEY_RIGHT])
			rotation = player->rot_speed;
		else
			rotation = -player->rot_speed;
		cos_rotation = cos(rotation);
		sin_rotation = sin(rotation);
		old_dir_x = player->dir_x;
		old_plane_x = player->plane_x;
		player->dir_x = player->dir_x * cos_rotation - player->dir_y
			* sin_rotation;
		player->dir_y = old_dir_x * sin_rotation + player->dir_y * cos_rotation;
		player->plane_x = player->plane_x * cos_rotation - player->plane_y
			* sin_rotation;
		player->plane_y = old_plane_x * sin_rotation + player->plane_y
			* cos_rotation;
	}
}

void	process_movement(void)
{
	t_game		*game;
	t_player	*player;

	game = get_game();
	player = &game->player;
	move_straight(player, game->keys);
	move_lateral(player, game->keys);
	rotate_camera(player, game->keys);
}
