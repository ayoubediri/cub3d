/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 20:08:37 by yjazouli          #+#    #+#             */
/*   Updated: 2025/09/02 21:49:02 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

double	now_seconds(void)
{
	struct timespec	ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (ts.tv_sec + ts.tv_nsec * 1e-9);
}

static void	framecap(double start, double dt)
{
	struct timespec	rq;
	double			now;
	double			elapsed;
	double			to_sleep;

	now = now_seconds();
	elapsed = now - start;
	to_sleep = dt - elapsed;
	if (to_sleep <= 0.0)
		return ;
	if (to_sleep < 1e-4)
		return ;
	rq.tv_sec = (time_t)floor(to_sleep);
	rq.tv_nsec = (long)((to_sleep - floor(to_sleep)) * 1e9);
	nanosleep(&rq, NULL);
}

void	game_tick(t_engine *engine)
{
	double	now;
	double	alpha;
	double	start;
	double	elapsed;

	start = now_seconds();
	now = start;
	elapsed = now - engine->last;
	engine->last = now;
	engine->acc += elapsed;
	while (engine->acc >= engine->dt)
	{
		engine->update(engine->dt);
		engine->acc -= engine->dt;
	}
	alpha = engine->acc / engine->dt;
	engine->render(alpha);
	if (engine->num_frames == 60)
		engine->num_frames = 0;
	framecap(start, engine->dt);
}
