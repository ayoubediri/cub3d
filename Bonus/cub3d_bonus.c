/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiri <adiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 09:55:41 by yjazouli          #+#    #+#             */
/*   Updated: 2025/09/11 10:43:58 by adiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		report_error("Usage: cub3d_bonus <map.cub>", NULL);
		clean_exit(1);
	}	
	setup_config();
	parse(av[1]);
	setup_minimap();
	check_all_pellets();
	start_game();
	leave_game(0);
	return (0);
}
