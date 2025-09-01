/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillers_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 10:53:09 by yjazouli          #+#    #+#             */
/*   Updated: 2025/09/01 11:29:11 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
				pixel_put(s.tmp_x, s.tmp_y, s.color);
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

void	line_filler(t_shape s, int e2)
{
	while (1)
	{
		if ((int)s.tmp_x >= s.clip_x && (int)s.tmp_x < s.clip_x + s.clip_w
			&& (int)s.tmp_y >= s.clip_y && (int)s.tmp_y < s.clip_y + s.clip_h)
			pixel_put((int)s.tmp_x, (int)s.tmp_y, s.color);
		if ((int)s.tmp_x == (int)s.p2.x && (int)s.tmp_y == (int)s.p2.y)
			break ;
		e2 = 2 * s.tmp_err;
		if (e2 > -abs((int)s.p2.y - (int)s.tmp_y))
		{
			s.tmp_err -= abs((int)s.tmp_y - (int)s.p2.y);
			if ((int)s.tmp_x < (int)s.p2.x)
				s.tmp_x += 1;
			else
				s.tmp_x -= 1;
		}
		if (e2 < abs((int)s.tmp_x - (int)s.p2.x))
		{
			s.tmp_err += abs((int)s.tmp_x - (int)s.p2.x);
			if ((int)s.tmp_y < (int)s.p2.y)
				s.tmp_y += 1;
			else
				s.tmp_y -= 1;
		}
	}
}
