/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillers_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 10:53:09 by yjazouli          #+#    #+#             */
/*   Updated: 2025/09/12 11:12:55 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	clip_put(int x, int y, t_shape s)
{
	if (x >= s.clip_x && x < s.clip_x + s.clip_w && y >= s.clip_y
		&& y < s.clip_y + s.clip_h)
		pixel_put(x, y, s.color);
}

void	arc_filler(t_shape s, double facing, double mouth_angle)
{
	while (s.tmp_y < s.max_y)
	{
		s.tmp_x = s.min_x;
		while (s.tmp_x < s.max_x)
		{
			s.tmp_dx = (double)(s.tmp_x - s.p1.x);
			s.tmp_dy = (double)(s.tmp_y - s.p1.y);
			if (s.tmp_dx * s.tmp_dx + s.tmp_dy * s.tmp_dy <= (double)s.radius
				* (double)s.radius)
			{
				s.tmp_ang = atan2(s.tmp_dy, s.tmp_dx);
				s.tmp_diff = s.tmp_ang - facing;
				while (s.tmp_diff <= -M_PI)
					s.tmp_diff += 2.0 * M_PI;
				while (s.tmp_diff > M_PI)
					s.tmp_diff -= 2.0 * M_PI;
				if (fabs(s.tmp_diff) < mouth_angle * 0.5)
					pixel_put(s.tmp_x, s.tmp_y, s.color);
			}
			s.tmp_x++;
		}
		s.tmp_y++;
	}
}

void	circle_filler(t_shape s)
{
	while (s.tmp_y < s.max_y)
	{
		s.tmp_x = s.min_x;
		while (s.tmp_x < s.max_x)
		{
			if ((s.tmp_x - s.p1.x) * (s.tmp_x - s.p1.x) + (s.tmp_y - s.p1.y)
				* (s.tmp_y - s.p1.y) <= s.radius * s.radius)
				clip_put((int)s.tmp_x, (int)s.tmp_y, s);
			s.tmp_x++;
		}
		s.tmp_y++;
	}
}

void	rect_filler(t_shape s)
{
	while (s.tmp_y < s.max_y)
	{
		s.tmp_x = s.min_x;
		while (s.tmp_x < s.max_x)
		{
			pixel_put(s.tmp_x, s.tmp_y, s.color);
			s.tmp_x++;
		}
		s.tmp_y++;
	}
}

void	line_filler(t_shape s)
{
	if ((int)s.p1.y == (int)s.p2.y)
	{
		s.tmp_y = (int)s.p1.y;
		s.tmp_x = s.min_x;
		while (s.tmp_x < s.max_x)
		{
			clip_put((int)s.tmp_x, (int)s.tmp_y, s);
			s.tmp_x++;
		}
		return ;
	}
	if ((int)s.p1.x == (int)s.p2.x)
	{
		s.tmp_x = (int)s.p1.x;
		s.tmp_y = s.min_y;
		while (s.tmp_y < s.max_y)
		{
			clip_put((int)s.tmp_x, (int)s.tmp_y, s);
			s.tmp_y++;
		}
		return ;
	}
}
