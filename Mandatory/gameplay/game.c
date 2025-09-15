/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiri <adiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:02:34 by yjazouli          #+#    #+#             */
/*   Updated: 2025/09/15 04:38:17 by adiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	game_loop(void)
{
	process_movement();
	raycasting();
	put_image();
	return (0);
}

int	leave_game(int exit_code)
{
	t_mlx	*mlx;

	mlx = &get_game()->mlx;
	destroy_wall_textures(mlx);
	if (mlx->win)
		mlx_destroy_window(mlx->mlx, mlx->win);
	if (mlx->img)
		mlx_destroy_image(mlx->mlx, mlx->img);
	if (mlx->mlx)
	{
		mlx_destroy_display(mlx->mlx);
		free(mlx->mlx);
	}
	clean_exit(exit_code);
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
		leave_game(1);
	}
	mlx->win = mlx_new_window(mlx->mlx, mlx->width, mlx->height, "Cub3d");
	if (!mlx->win)
	{
		report_error("mlx", "failed to create window");
		leave_game(1);
	}
	mlx->img = mlx_new_image(mlx->mlx, mlx->width, mlx->height);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->line,
			&mlx->endian);
	setup_textures();
	mlx_hook(mlx->win, 17, 1L << 17, leave_game, NULL);
	mlx_hook(mlx->win, 2, 1L << 0, on_keypress, NULL);
	mlx_hook(mlx->win, 3, 1L << 1, on_keyrelease, NULL);
	mlx_loop_hook(mlx->mlx, game_loop, NULL);
	mlx_loop(mlx->mlx);
}
