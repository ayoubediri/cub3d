/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:23:31 by yjazouli          #+#    #+#             */
/*   Updated: 2025/08/20 18:25:13 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	game_loop(void)
{
	clear_image();
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

	mlx = get_mlx();
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
	mlx_loop_hook(mlx->mlx, game_loop, NULL);
	mlx_loop(mlx->mlx);
}
