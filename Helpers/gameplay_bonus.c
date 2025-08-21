/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:26:42 by yjazouli          #+#    #+#             */
/*   Updated: 2025/08/21 10:31:31 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_mlx	*get_mlx(void)
{
	t_game	*game;

	game = get_game();
	return (&game->mlx);
}

t_engine	*get_engine(void)
{
	t_game	*game;

	game = get_game();
	return (&game->engine);
}

t_gameplay	*get_gameplay(void)
{
	t_game	*game;

	game = get_game();
	return (&game->gameplay);
}
