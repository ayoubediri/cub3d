/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   health_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 16:29:36 by yjazouli@st       #+#    #+#             */
/*   Updated: 2025/09/01 09:49:51 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_border(int x, int y, int w, int h)
{
	t_shape	border;

	border.p1.x = x - 2;
	border.p1.y = y - 2;
	border.width = w + 4;
	border.height = h + 4;
	border.color = 0xFFFFFF;
	border.clip_x = 0;
	border.clip_y = 0;
	border.clip_w = WIDTH;
	border.clip_h = HEIGHT;
	draw_rect(border);
}

void	draw_background(int x, int y, int w, int h)
{
	t_shape	background;

	background.p1.x = x;
	background.p1.y = y;
	background.width = w;
	background.height = h;
	background.color = 0x000000;
	background.clip_x = 0;
	background.clip_y = 0;
	background.clip_w = WIDTH;
	background.clip_h = HEIGHT;
	draw_rect(background);
}

void	draw_health(int x, int y, int w, int h)
{
	t_player	*player;
	t_shape		health_bar;

	player = &get_gameplay()->player;
	health_bar.p1.x = x;
	health_bar.p1.y = y;
	health_bar.width = (w * player->ent->hp) / player->ent->max_hp;
	health_bar.height = h;
	health_bar.color = 0xFF0000;
	health_bar.clip_x = 0;
	health_bar.clip_y = 0;
	health_bar.clip_w = WIDTH;
	health_bar.clip_h = HEIGHT;
	draw_rect(health_bar);
}

void	render_health_ui(void)
{
	int	x;
	int	y;
	int	w;
	int	h;

	w = (int)(WIDTH * 0.22);
	if (w < 100)
		w = 100;
	if (w > 300)
		w = 300;
	h = HEIGHT / 40;
	if (h < 12)
		h = 12;
	x = 20;
	y = HEIGHT - (h + 20);
	draw_border(x, y, w, h);
	draw_background(x, y, w, h);
	draw_health(x, y, w, h);
}
