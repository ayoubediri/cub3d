/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 10:32:36 by yjazouli          #+#    #+#             */
/*   Updated: 2025/09/11 11:20:57 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_arc(t_shape s)
{
	s.arc_facing = 0.0;
	if (s.p2.x != s.p1.x || s.p2.y != s.p1.y)
		s.arc_facing = atan2(s.p2.y - s.p1.y, s.p2.x - s.p1.x);
	if (s.len)
		s.arc_span = (double)s.len * (M_PI / 180.0);
	else
		s.arc_span = M_PI;
	s.min_x = s.p1.x - s.radius;
	s.min_y = s.p1.y - s.radius;
	s.max_x = s.p1.x + s.radius + 1;
	s.max_y = s.p1.y + s.radius + 1;
	s.tmp_x = s.min_x;
	s.tmp_y = s.min_y;
	if (s.max_x <= s.clip_x || s.max_y <= s.clip_y || s.tmp_x >= s.clip_x
		+ s.clip_w || s.tmp_y >= s.clip_y + s.clip_h)
		return ;
	if (s.tmp_x < s.clip_x)
		s.tmp_x = s.clip_x;
	if (s.tmp_y < s.clip_y)
		s.tmp_y = s.clip_y;
	if (s.max_x > s.clip_x + s.clip_w)
		s.max_x = s.clip_x + s.clip_w;
	if (s.max_y > s.clip_y + s.clip_h)
		s.max_y = s.clip_y + s.clip_h;
	arc_filler(s, s.arc_facing, s.arc_span);
}

void	draw_circle(t_shape s)
{
	s.min_x = s.p1.x - s.radius;
	s.min_y = s.p1.y - s.radius;
	s.max_x = s.p1.x + s.radius + 1;
	s.max_y = s.p1.y + s.radius + 1;
	s.tmp_x = s.min_x;
	s.tmp_y = s.min_y;
	if (s.max_x <= s.clip_x || s.max_y <= s.clip_y || s.tmp_x >= s.clip_x
		+ s.clip_w || s.tmp_y >= s.clip_y + s.clip_h)
		return ;
	if (s.tmp_x < s.clip_x)
		s.tmp_x = s.clip_x;
	if (s.tmp_y < s.clip_y)
		s.tmp_y = s.clip_y;
	if (s.max_x > s.clip_x + s.clip_w)
		s.max_x = s.clip_x + s.clip_w;
	if (s.max_y > s.clip_y + s.clip_h)
		s.max_y = s.clip_y + s.clip_h;
	circle_filler(s);
}

void	draw_rect(t_shape s)
{
	s.min_x = s.p1.x;
	s.min_y = s.p1.y;
	s.max_x = s.p1.x + s.width;
	s.max_y = s.p1.y + s.height;
	s.tmp_x = s.min_x;
	s.tmp_y = s.min_y;
	if (s.max_x <= s.clip_x || s.max_y <= s.clip_y || s.tmp_x >= s.clip_x
		+ s.clip_w || s.tmp_y >= s.clip_y + s.clip_h)
		return ;
	if (s.tmp_x < s.clip_x)
		s.tmp_x = s.clip_x;
	if (s.tmp_y < s.clip_y)
		s.tmp_y = s.clip_y;
	if (s.max_x > s.clip_x + s.clip_w)
		s.max_x = s.clip_x + s.clip_w;
	if (s.max_y > s.clip_y + s.clip_h)
		s.max_y = s.clip_y + s.clip_h;
	rect_filler(s);
}

void	draw_line(t_shape s)
{
	s.tmp_x = (int)s.p1.x;
	s.tmp_y = (int)s.p1.y;
	s.tmp_err = abs((int)s.p2.x - (int)s.tmp_x) - abs((int)s.p2.y
			- (int)s.tmp_y);
	s.min_x = (int)fmin(s.p1.x, s.p2.x);
	s.min_y = (int)fmin(s.p1.y, s.p2.y);
	s.max_x = (int)fmax(s.p1.x, s.p2.x);
	s.max_y = (int)fmax(s.p1.y, s.p2.y);
	s.max_x += 1;
	s.max_y += 1;
	if (s.max_x <= s.clip_x || s.max_y <= s.clip_y || s.min_x >= s.clip_x
		+ s.clip_w || s.min_y >= s.clip_y + s.clip_h)
		return ;
	if (s.min_x < s.clip_x)
		s.min_x = s.clip_x;
	if (s.min_y < s.clip_y)
		s.min_y = s.clip_y;
	if (s.max_x > s.clip_x + s.clip_w)
		s.max_x = s.clip_x + s.clip_w;
	if (s.max_y > s.clip_y + s.clip_h)
		s.max_y = s.clip_y + s.clip_h;
	line_filler(s);
}
