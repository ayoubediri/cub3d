/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_screen_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiri <adiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 06:55:39 by adiri             #+#    #+#             */
/*   Updated: 2025/09/15 17:21:03 by adiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	show_fps(t_game *game)
{
	static int		frames = 0;
	static long		last_ms = 0;
	static int		current_fps = 0;
	struct timeval	tv;
	long			now_ms;

	gettimeofday(&tv, NULL);
	now_ms = tv.tv_sec * 1000L + tv.tv_usec / 1000L;
	frames++;
	if (last_ms == 0)
		last_ms = now_ms;
	if (now_ms - last_ms >= 250)
	{
		current_fps = frames * 1000 / (now_ms - last_ms);
		frames = 0;
		last_ms = now_ms;
	}
	mlx_string_put(game->mlx.mlx, game->mlx.win, \
		10, 10, 0xFFFFFF, ft_itoa((int)current_fps));
}

void	game_render(double alpha)
{
	(void)alpha;
	raycasting();
	minimap_render();
	render_health_ui();
	put_image();
	show_fps(get_game());
}

int	leave_game(int exit_code)
{
	t_game	*game;
	t_mlx	*mlx;

	game = get_game();
	mlx = get_mlx();
	destroy_wall(mlx, game);
	destroy_enemy_textures(mlx);
	destroy_coin_textures(mlx);
	destroy_other_textures(mlx, game);
	destroy_mlx(mlx);
	stop_background_music();
	pthread_join(game->music_thread, NULL);
	clean_exit(exit_code);
	return (1);
}

void	start_screen(void)
{
	t_mlx		*mlx;
	t_gameplay	*gameplay;
	t_texture	texture_start;

	mlx = get_mlx();
	gameplay = get_gameplay();
	gameplay->start_game_sound = 0;
	texture_start = load_texture(START_SCREEN_TEXTURE_PATH);
	system("aplay -q " START_SCREEN_SOUND_PATH " > /dev/null 2>&1 &");
	mlx_put_image_to_window(mlx->mlx, mlx->win, \
		texture_start.img_ptr, HALF_WIDTH - 256, HALF_HEIGHT - 256);
	sleep(3);
	mlx_destroy_image(mlx->mlx, texture_start.img_ptr);
}

void	lose_screen(void)
{
	t_mlx		*mlx;
	t_texture	lose_texture;

	mlx = get_mlx();
	lose_texture = load_texture(LOSE_TEXTURE_PATH);
	stop_background_music();
	mlx_clear_window(mlx->mlx, mlx->win);
	mlx_put_image_to_window(mlx->mlx, mlx->win, lose_texture.img_ptr, HALF_WIDTH
		- 256, HALF_HEIGHT - 256);
	mlx_do_sync(mlx->mlx);
	system("aplay -q " LOSE_SOUND_PATH " > /dev/null 2>&1 &");
	mlx_destroy_image(mlx->mlx, lose_texture.img_ptr);
	sleep(4);
}
