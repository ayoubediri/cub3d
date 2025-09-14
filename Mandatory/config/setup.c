/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:41:14 by yjazouli          #+#    #+#             */
/*   Updated: 2025/09/13 10:53:13 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	config_mlx(void)
{
	t_mlx	*mlx;

	mlx = &get_game()->mlx;
	ft_bzero(mlx, sizeof(*mlx));
	mlx->width = WIDTH;
	mlx->height = HEIGHT;
}

void	fill_player(double dx, double dy, double px, double py)
{
	t_player	*player;

	player = &get_game()->player;
	player->dir_x = dx;
	player->dir_y = dy;
	player->plane_x = px;
	player->plane_y = py;
}

void	config_player(void)
{
	t_game	*game;

	game = get_game();
	game->player.pos_x = game->map.player_x + 0.5f;
	game->player.pos_y = game->map.player_y + 0.5f;
	if (game->map.player_dir == 'S')
		fill_player(0, -1, 0.66, 0);
	else if (game->map.player_dir == 'N')
		fill_player(0, 1, -0.66, 0);
	else if (game->map.player_dir == 'E')
		fill_player(1, 0, 0, 0.66);
	else if (game->map.player_dir == 'W')
		fill_player(-1, 0, 0, -0.66);
	game->player.move_speed = PLAYER_SPEED;
	game->player.rot_speed = PLAYER_ROT_SPEED;
}

void	setup_config(void)
{
	config_player();
	config_mlx();
}
