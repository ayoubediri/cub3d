/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:21:13 by yjazouli          #+#    #+#             */
/*   Updated: 2025/08/23 16:05:13 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	pixel_put(int x, int y, int color)
{
	t_mlx	*mlx;

	mlx = get_mlx();
	if (x < 0 || x >= mlx->width || y < 0 || y >= mlx->height)
		return ;
	*(unsigned int *)(mlx->addr + (y * mlx->line + x * (mlx->bpp / 8))) = color;
}

void	clear_image(void)
{
	t_mlx	*mlx;

	mlx = get_mlx();
	bzero(mlx->addr, mlx->height * mlx->line);
}

void	put_image(void)
{
	t_mlx	*mlx;

	mlx = get_mlx();
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}
