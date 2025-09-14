/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pacman_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 10:54:53 by yjazouli          #+#    #+#             */
/*   Updated: 2025/09/01 11:07:46 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	prepare_mouth(t_pacman *pac, t_shape *m, int cx, int cy)
{
	t_minimap	*mm;

	mm = &get_gameplay()->minimap;
	m->p1.x = cx;
	m->p1.y = cy;
	m->radius = pac->radius;
	m->color = mm->col_bg;
	m->clip_x = pac->clip_x;
	m->clip_y = pac->clip_y;
	m->clip_w = pac->clip_w;
	m->clip_h = pac->clip_h;
	m->tmp_x = 0;
	m->tmp_y = 0;
	m->tmp_err = 0;
}

static void	draw_mouth(t_pacman *pac, int cx, int cy)
{
	t_shape		s;
	t_minimap	*mm;

	mm = &get_gameplay()->minimap;
	prepare_mouth(pac, &s, cx, cy);
	if (pac->ent->dir.x == 0.0 && pac->ent->dir.y == 0.0)
	{
		s.p2.x = s.p1.x + 1;
		s.p2.y = s.p1.y;
	}
	else
	{
		s.p2.x = s.p1.x + (int)round(pac->ent->dir.x * 8.0);
		s.p2.y = s.p1.y + (int)round(pac->ent->dir.y * 8.0);
	}
	s.len = (int)round(pac->mouth_open * 108.0);
	s.radius = pac->radius;
	s.color = mm->col_bg;
	s.clip_x = pac->clip_x;
	s.clip_y = pac->clip_y;
	s.clip_w = pac->clip_w;
	s.clip_h = pac->clip_h;
	draw_arc(s);
}

static void	draw_body(t_pacman *pac, int cx, int cy)
{
	t_shape	body;

	body.p1.x = cx;
	body.p1.y = cy;
	body.radius = pac->radius;
	body.color = pac->color;
	body.clip_x = pac->clip_x;
	body.clip_y = pac->clip_y;
	body.clip_w = pac->clip_w;
	body.clip_h = pac->clip_h;
	body.tmp_x = 0;
	body.tmp_y = 0;
	body.tmp_err = 0;
	draw_circle(body);
}

void	draw_pacman(t_pacman *pac)
{
	int	cx;
	int	cy;

	world_to_minimap(pac->ent->pos.x, pac->ent->pos.y, &cx, &cy);
	draw_body(pac, cx, cy);
	draw_mouth(pac, cx, cy);
}
