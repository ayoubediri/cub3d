/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 20:49:02 by yjazouli          #+#    #+#             */
/*   Updated: 2025/08/24 21:05:51 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

double	vec2_dist_sq(t_vec2 a, t_vec2 b)
{
	double	dx;
	double	dy;

	dx = a.x - b.x;
	dy = a.y - b.y;
	return (dx * dx + dy * dy);
}

double	vec2_dist(t_vec2 a, t_vec2 b)
{
	return (sqrt(vec2_dist_sq(a, b)));
}

double	vec2_dir_and_dist(t_vec2 from, t_vec2 to, t_vec2 *out_dir)
{
	double	dx;
	double	dy;
	double	d2;
	double	d;

	dx = to.x - from.x;
	dy = to.y - from.y;
	d2 = dx * dx + dy * dy;
	d = sqrt(d2);
	if (out_dir)
	{
		if (d > 1e-9)
		{
			out_dir->x = dx / d;
			out_dir->y = dy / d;
		}
		else
		{
			out_dir->x = 0.0;
			out_dir->y = 0.0;
		}
	}
	return (d);
}

