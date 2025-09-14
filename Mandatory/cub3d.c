/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 12:45:15 by yjazouli          #+#    #+#             */
/*   Updated: 2025/09/14 09:40:52 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_game	*get_game(void)
{
	static t_game	game;

	return (&game);
}

void	init_struct(void)
{
	t_game	*game;

	game = get_game();
	game->parse.floor_col = -1;
	game->parse.ceiling_col = -1;
}

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		report_error("Invalid arguments", "Need only path to map");
		clean_exit(1);
	}
	init_struct();
	parse_map(av[1]);
	setup_config();
	start_game();
	return (0);
}
