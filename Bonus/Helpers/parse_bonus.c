/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:30:30 by yjazouli          #+#    #+#             */
/*   Updated: 2025/08/20 13:03:33 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_game	*get_game(void)
{
	static t_game	game;

	return (&game);
}

t_parse	*get_parse(void)
{
	t_game	*game;

	game = get_game();
	return (&game->parse);
}

t_map	*get_map(void)
{
	t_game	*game;

	game = get_game();
	return (&game->map);
}
