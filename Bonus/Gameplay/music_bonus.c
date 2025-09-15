/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiri <adiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 06:52:22 by adiri             #+#    #+#             */
/*   Updated: 2025/09/15 17:18:54 by adiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	stop_background_music(void)
{
	t_gameplay	*gameplay;

	gameplay = get_gameplay();
	if (gameplay->start_game_sound && gameplay->pid_sound > 0)
		kill(gameplay->pid_sound, SIGKILL);
	gameplay->start_game_sound = 0;
}

void	*start_music_thread(void *arg)
{
	t_gameplay	*gameplay;

	(void)arg;
	gameplay = get_gameplay();
	while (gameplay->start_game_sound)
	{
		gameplay->pid_sound = fork();
		if (gameplay->pid_sound == 0)
		{
			execlp("aplay", "aplay", "-q", BACKGROUND_MUSIC_PATH, NULL);
			leave_game(1);
		}
		waitpid(gameplay->pid_sound, NULL, 0);
	}
	return (NULL);
}

void	start_music(void)
{
	t_game		*game;
	t_gameplay	*gameplay;
	pthread_t	*music_thread;

	game = get_game();
	gameplay = &game->gameplay;
	music_thread = &game->music_thread;
	if (gameplay->start_game_sound)
		return ;
	gameplay->start_game_sound = 1;
	if (pthread_create(music_thread, NULL, start_music_thread, NULL) != 0)
	{
		report_error("pthread", "failed to create music thread");
		gameplay->error_music = 1;
	}
}
