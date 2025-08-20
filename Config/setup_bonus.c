/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:32:58 by yjazouli          #+#    #+#             */
/*   Updated: 2025/08/20 18:33:51 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	config_mlx(void)
{
	t_mlx	*mlx;

	mlx = get_mlx();
	mlx->width = 1920;
	mlx->height = 1080;
}

void	setup_config(void)
{
	config_mlx();
}
