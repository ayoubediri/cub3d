/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 09:55:41 by yjazouli          #+#    #+#             */
/*   Updated: 2025/08/20 18:34:27 by yjazouli         ###   ########.fr       */
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
	parse(av[1]);
	setup_config();
	start_game();
	return (0);
}
