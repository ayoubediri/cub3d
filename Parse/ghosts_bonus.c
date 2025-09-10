/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ghosts_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 14:15:53 by yjazouli          #+#    #+#             */
/*   Updated: 2025/09/01 17:17:31 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	count_ghosts(void)
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
			if (parse->map[y][x] == 'X')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

int	create_ghost_entity(int x, int y)
{
	int			idx;
	t_ghost		*curr;
	t_gameplay	*gameplay;

	idx = add_entity(x, y);
	gameplay = get_gameplay();
	gameplay->entities[idx].type = ENTITY_GHOST;
	if (gameplay->ghosts && gameplay->ghost_count < gameplay->ghost_capacity)
	{
		curr = gameplay->ghosts + gameplay->ghost_count;
		curr->ent = &gameplay->entities[idx];
		curr->spawn_point = gameplay->entities[idx].pos;
		curr->state = GHOST_STATE_IDLE;
		curr->color = 0x00FF0000;
		curr->base_speed = 2.0;
		curr->frightened_speed = 1.6;
		curr->eaten_speed = 4.0;
		gameplay->ghost_count++;
	}
	return (idx);
}
