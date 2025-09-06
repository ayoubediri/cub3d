/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:02:34 by yjazouli          #+#    #+#             */
/*   Updated: 2025/07/15 23:02:02 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	game_loop(void)
{
	clear_image();
	process_movement();
	render_background();
	raycasting();
	put_image();
	return (0);
}

static int	leave_game(void)
{
	clean_exit(0);
	return (1);
}

void	start_game(void)
{
	t_mlx	*mlx;

	mlx = &get_game()->mlx;
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
	{
		report_error("mlx", "failed to initialize session");
		clean_exit(1);
	}
	mlx->win = mlx_new_window(mlx->mlx, mlx->width, mlx->height, "Cub3d");
	if (!mlx->win)
	{
		report_error("mlx", "failed to create window");
		clean_exit(1);
	}
	mlx->img = mlx_new_image(mlx->mlx, mlx->width, mlx->height);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->line,
			&mlx->endian);
	mlx_hook(mlx->win, 17, 1L << 17, leave_game, NULL);
	mlx_hook(mlx->win, 2, 1L << 0, on_keypress, NULL);
	mlx_hook(mlx->win, 3, 1L << 1, on_keyrelease, NULL);
	mlx_loop_hook(mlx->mlx, game_loop, NULL);
	mlx_loop(mlx->mlx);
}
