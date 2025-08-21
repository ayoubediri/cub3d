/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 09:55:36 by yjazouli          #+#    #+#             */
/*   Updated: 2025/08/21 10:38:31 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	count_entities(void)
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
			if (parse->map[y][x] == 'X' || parse->map[y][x] == 'N'
				|| parse->map[y][x] == 'S' || parse->map[y][x] == 'E'
				|| parse->map[y][x] == 'W')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

void	start_entities(void)
{
	int			total;
	t_gameplay	*gameplay;

	total = count_entities();
	gameplay = get_gameplay();
	gameplay->entity_count = total;
	gameplay->entities = ft_calloc(total, sizeof(t_entity));
}

int	add_entity(int x, int y)
{
	int			idx;
	t_gameplay	*gameplay;

	gameplay = get_gameplay();
    idx = gameplay->entity_count++;
    gamepl
}
