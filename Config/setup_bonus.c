/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:32:58 by yjazouli          #+#    #+#             */
/*   Updated: 2025/08/20 20:13:58 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	config_mlx(void)
{
	t_mlx	*mlx;

	mlx = get_mlx();
	mlx->width = WIDTH;
	mlx->height = HEIGHT;
}

static void	config_engine(void)
{
	t_engine	*engine;

	engine = get_engine();
	engine->target_fps = FPS;
	engine->dt = 1.0 / (double)engine->target_fps;
	engine->last = now_seconds();
	engine->acc = 0.0;
	engine->update = game_update;
	engine->render = game_render;
}

void	setup_config(void)
{
	config_mlx();
	config_engine();
}
