/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiri <adiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 11:27:41 by yjazouli          #+#    #+#             */
/*   Updated: 2025/09/13 08:46:09 by adiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	pixel_put(int x, int y, int color)
{
	t_mlx	*mlx;
	int		pos;

	mlx = &get_game()->mlx;
	if (x < 0 || x >= mlx->width || y < 0 || y >= mlx->height)
		return ;
	pos = (y * mlx->line + x * (mlx->bpp / 8));
	*(unsigned int *)(mlx->addr + pos) = color;
}

void	draw_tile(int x, int y, int color)
{
	int	i;
	int	j;
	int	tile_size;

	i = 0;
	tile_size = 10;
	while (i < tile_size)
	{
		j = 0;
		while (j < tile_size)
		{
			pixel_put(x * tile_size + j, y * tile_size + i, color);
			j++;
		}
		i++;
	}
}

void	render_background(void)
{
	int		x;
	int		y;
	t_mlx	*mlx;
	t_game	*game;

	y = 0;
	game = get_game();
	mlx = &game->mlx;
	while (y < HALF_HEIGHT)
	{
		x = -1;
		while (++x < mlx->width)
			pixel_put(x, y, game->scene.ceiling_col);
		y++;
	}
	while (y < mlx->height)
	{
		x = -1;
		while (x++ < mlx->width)
			pixel_put(x, y, game->scene.floor_col);
		y++;
	}
}

void	clear_image(void)
{
	t_mlx	*mlx;
	int		size;

	mlx = &get_game()->mlx;
	size = mlx->height * mlx->line;
	ft_bzero(mlx->addr, size);
}

void	put_image(void)
{
	mlx_put_image_to_window(get_game()->mlx.mlx, get_game()->mlx.win, \
	get_game()->mlx.img, 0, 0);
}
