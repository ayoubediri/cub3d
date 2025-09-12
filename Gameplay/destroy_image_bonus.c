/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_image_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiri <adiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 05:48:46 by adiri             #+#    #+#             */
/*   Updated: 2025/09/12 05:52:03 by adiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	destroy_enemy_textures(t_mlx *mlx)
{
	t_texture	**enemy;

	enemy = enemy_texture();
	if (!enemy)
		return ;
	mlx_destroy_image(mlx->mlx, enemy[0][0].img_ptr);
	mlx_destroy_image(mlx->mlx, enemy[0][1].img_ptr);
	mlx_destroy_image(mlx->mlx, enemy[0][3].img_ptr);
	mlx_destroy_image(mlx->mlx, enemy[1][0].img_ptr);
	mlx_destroy_image(mlx->mlx, enemy[1][1].img_ptr);
	mlx_destroy_image(mlx->mlx, enemy[1][3].img_ptr);
	mlx_destroy_image(mlx->mlx, enemy[2][0].img_ptr);
	mlx_destroy_image(mlx->mlx, enemy[2][1].img_ptr);
	mlx_destroy_image(mlx->mlx, enemy[2][3].img_ptr);
	mlx_destroy_image(mlx->mlx, enemy[3][0].img_ptr);
	mlx_destroy_image(mlx->mlx, enemy[3][1].img_ptr);
	mlx_destroy_image(mlx->mlx, enemy[3][3].img_ptr);
}

void	destroy_wall(t_mlx *mlx, t_game *game)
{
	int	i;

	i = 0;
	while (i < WALL_TOTAL)
	{
		if (game->wall_textures[i].img_ptr)
			mlx_destroy_image(mlx->mlx, game->wall_textures[i].img_ptr);
		i++;
	}
}

void	destroy_other_textures(t_mlx *mlx, t_game *game)
{
	if (game->gameplay.door_texture_close.img_ptr)
		mlx_destroy_image(mlx->mlx, game->gameplay.door_texture_close.img_ptr);
	if (game->floor_texture.img_ptr)
		mlx_destroy_image(mlx->mlx, game->floor_texture.img_ptr);
	if (game->ceiling_texture.img_ptr)
		mlx_destroy_image(mlx->mlx, game->ceiling_texture.img_ptr);
	if (game->sky_texture.img_ptr)
		mlx_destroy_image(mlx->mlx, game->sky_texture.img_ptr);
}

void	destroy_coin_textures(t_mlx *mlx)
{
	int			i;
	t_texture	*coin_textures;

	i = 0;
	coin_textures = get_coin_texture();
	while (i < NUM_COINS_FRAMES)
	{
		if (coin_textures && coin_textures[i].img_ptr)
		{
			mlx_destroy_image(mlx->mlx, coin_textures[i].img_ptr);
			coin_textures[i] = (t_texture){0};
		}
		i++;
	}
}

void	destroy_mlx(t_mlx *mlx)
{
	if (mlx->img)
		mlx_destroy_image(mlx->mlx, mlx->img);
	if (mlx->win)
		mlx_destroy_window(mlx->mlx, mlx->win);
	if (mlx->mlx)
	{
		mlx_destroy_display(mlx->mlx);
		free(mlx->mlx);
		mlx->mlx = NULL;
	}
}
