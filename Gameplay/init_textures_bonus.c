/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiri <adiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 06:54:09 by adiri             #+#    #+#             */
/*   Updated: 2025/09/12 06:59:17 by adiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_texture	**enemy_texture(void)
{
	static t_texture	enemy1[4];
	static t_texture	enemy2[4];
	static t_texture	enemy3[4];
	static t_texture	enemy4[4];
	static t_texture	*enemy[4] = {enemy1, enemy2, enemy3, enemy4};

	return (enemy);
}

void	init_ghosts_textures(void)
{
	t_game		*game;
	t_texture	**enemy_textures;
	int			idx;
	int			i;

	game = get_game();
	enemy_textures = enemy_texture();
	i = 0;
	while (i < game->gameplay.ghost_count)
	{
		idx = game->gameplay.ghosts[i].ent->tex_idx;
		if (idx < 0 || idx >= 4)
			idx = 0;
		game->gameplay.ghosts[i].ent->texture = &enemy_textures[idx][0];
		i++;
	}
}

t_texture	*get_coin_texture(void)
{
	static t_texture	coin_textures[34];

	return (coin_textures);
}

char	*get_coin_texture_path(int index)
{
	char	*path;
	int		len;

	len = snprintf(NULL, 0, "%s%d.xpm", COIN_TEXTURE_PATH, index);
	path = ft_malloc(len + 1);
	if (!path)
		return (NULL);
	snprintf(path, len + 1, "%s%d.xpm", COIN_TEXTURE_PATH, index);
	return (path);
}

void	config_textures(void)
{
	t_game		*game;

	game = get_game();
	load_enemy(enemy_texture());
	load_wall_textures(game);
	load_coins_textures();
	load_other_textures(game);
	init_ghosts_textures();
}
