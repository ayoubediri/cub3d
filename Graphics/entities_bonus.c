/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:16:38 by yjazouli          #+#    #+#             */
/*   Updated: 2025/09/01 14:49:17 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_shape	make_circle_shape(t_entity *ent)
{
	int			x;
	int			y;
	t_minimap	*mm;
	t_shape		circle;

	world_to_minimap(ent->pos.x, ent->pos.y, &x, &y);
	mm = &get_gameplay()->minimap;
	circle.p1.x = x;
	circle.p1.y = y;
	circle.radius = ent->radius * mm->world_to_px;
	circle.clip_x = mm->ox + 2;
	circle.clip_y = mm->oy + 2;
	circle.clip_w = mm->size_px - 4;
	circle.clip_h = mm->size_px - 4;
	return (circle);
}

void	draw_pellet(t_entity *ent)
{
	t_minimap	*mm;
	t_shape		pellet;

	mm = &get_gameplay()->minimap;
	pellet = make_circle_shape(ent);
	pellet.color = mm->col_pellet;
	draw_circle(pellet);
}

void	draw_ghost(t_entity *ent)
{
	t_shape	ghost;

	ghost = make_circle_shape(ent);
	ghost.color = 0xFF0000;
	draw_circle(ghost);
}

void	draw_entities(t_entity *ents)
{
	int			i;
	t_entity	*curr;
	t_gameplay	*gameplay;

	i = 0;
	gameplay = get_gameplay();
	while (i < gameplay->entity_count)
	{
		curr = &ents[i];
		if (curr && !curr->gone && curr->type != ENTITY_PLAYER)
		{
			if (curr->type == ENTITY_PELLET)
				draw_pellet(curr);
			else if (curr->type == ENTITY_GHOST)
				draw_ghost(curr);
		}
		i++;
	}
}
