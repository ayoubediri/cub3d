/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:29:53 by yjazouli          #+#    #+#             */
/*   Updated: 2025/08/20 16:46:57 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	count_doors(void)
{
	int		x;
	int		y;
	int		len;
	int		count;
	t_parse	*parse;

	y = 0;
	count = 0;
	parse = get_parse();
	while (y < parse->height)
	{
		x = 0;
		len = strlen(parse->map[y]);
		while (x < len)
		{
			if (parse->map[y][x] == 'D')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}
