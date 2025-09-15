/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiri <adiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 06:47:35 by adiri             #+#    #+#             */
/*   Updated: 2025/09/15 16:46:56 by adiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_texture	load_texture(char *path)
{
	t_mlx		*mlx;
	t_texture	texture;

	mlx = get_mlx();
	memset(&texture, 0, sizeof(t_texture));
	texture.img_ptr = mlx_xpm_file_to_image(mlx->mlx, path, &texture.width,
			&texture.height);
	if (!texture.img_ptr)
	{
		report_error("mlx", "failed to load texture from path");
		leave_game(1);
	}
	texture.addr = mlx_get_data_addr(texture.img_ptr, &texture.bpp,
			&texture.line_length, &texture.endian);
	if (!texture.addr)
	{
		report_error("mlx", "failed to get texture data address");
		mlx_destroy_image(mlx->mlx, texture.img_ptr);
		leave_game(1);
	}
	texture.path = path;
	return (texture);
}

void	load_enemy(t_texture **enemy)
{
	enemy[0][0] = load_texture(ENEMY1_TEXTURE_MED);
	enemy[0][1] = load_texture(ENEMY1_TEXTURE_DOWN);
	enemy[0][2] = enemy[0][0];
	enemy[0][3] = load_texture(ENEMY1_TEXTURE_UP);
	enemy[1][0] = load_texture(ENEMY2_TEXTURE_MED);
	enemy[1][1] = load_texture(ENEMY2_TEXTURE_DOWN);
	enemy[1][2] = enemy[1][0];
	enemy[1][3] = load_texture(ENEMY2_TEXTURE_UP);
	enemy[2][0] = load_texture(ENEMY3_TEXTURE_MED);
	enemy[2][1] = load_texture(ENEMY3_TEXTURE_DOWN);
	enemy[2][2] = enemy[2][0];
	enemy[2][3] = load_texture(ENEMY3_TEXTURE_UP);
	enemy[3][0] = load_texture(ENEMY4_TEXTURE_MED);
	enemy[3][1] = load_texture(ENEMY4_TEXTURE_DOWN);
	enemy[3][2] = enemy[3][0];
	enemy[3][3] = load_texture(ENEMY4_TEXTURE_UP);
}

void	load_wall_textures(t_game *game)
{
	t_parse	*parse;

	parse = get_parse();
	game->wall_textures[WALL_NORTH] = load_texture(parse->no_texture);
	game->wall_textures[WALL_SOUTH] = load_texture(parse->so_texture);
	game->wall_textures[WALL_EAST] = load_texture(parse->ea_texture);
	game->wall_textures[WALL_WEST] = load_texture(parse->we_texture);
}

void	load_other_textures(t_game *game)
{
	game->ground_texture = load_texture(GROUND_TEXTURE_PATH);
	game->sky_texture = load_texture(SKY_TEXTURE_PATH);
	game->gameplay.ghost_texture = (t_texture){0};
	game->gameplay.pellet_texture = (t_texture){0};
	game->gameplay.door_texture_close = load_texture(DOOR_TEXTURE_CLOSE_PATH);
}

void	load_coins_textures(void)
{
	t_texture	*coin_textures;
	int			i;
	char		*path;

	coin_textures = get_coin_texture();
	i = 0;
	while (i < 34)
	{
		path = get_coin_texture_path(i + 1);
		if (!path)
		{
			report_error("malloc", "failed to allocate memory for coin \
texture path");
			leave_game(1);
		}
		coin_textures[i] = load_texture(path);
		i++;
	}
}
