/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiri <adiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:38:05 by yjazouli          #+#    #+#             */
/*   Updated: 2025/09/12 05:55:29 by adiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	map_keypress(int key)
{
	if (key == XK_w || key == XK_W || key == XK_Up || key == 'w' || key == 1493)
		return (KEY_W);
	else if (key == XK_a || key == XK_A || key == 'a' || key == 1492)
		return (KEY_A);
	else if (key == XK_s || key == XK_S || key == XK_Down || key == 's'
		|| key == 1491)
		return (KEY_S);
	else if (key == XK_d || key == XK_D || key == 'd' || key == 1514)
		return (KEY_D);
	else if (key == XK_e || key == XK_E || key == 'e' || key == 1483)
		return (KEY_E);
	else if (key == XK_Left)
		return (KEY_LEFT);
	else if (key == XK_Right)
		return (KEY_RIGHT);
	else if (key == XK_Escape)
		return (KEY_ESC);
	return (-1);
}

int	mouse_handler(int x, int y, t_mlx *mlx)
{
	double		dx;
	double		angle;
	t_entity	*player;

	(void)y;
	dx = x - HALF_WIDTH;
	if (fabs(dx) < 2 || mlx->blocked)
		return (0);
	angle = dx * MOUSE_SENSITIVITY;
	player = get_gameplay()->player.ent;
	rotate_player(player, angle);
	mlx_mouse_move(mlx->mlx, mlx->win, HALF_WIDTH, HALF_HEIGHT);
	return (0);
}

void	end_game_screen(void)
{
	t_mlx		*mlx;
	t_texture	texture_escape;

	mlx = get_mlx();
	texture_escape = load_texture(ESCAPE_SCREEN_TEXTURE_PATH);
	stop_background_music();
	mlx_clear_window(mlx->mlx, mlx->win);
	system("aplay -q " ESCAPE_SCREEN_SOUND_PATH " > /dev/null 2>&1 &");
	mlx_put_image_to_window(mlx->mlx, mlx->win, texture_escape.img_ptr, 448, 0);
	mlx_do_sync(mlx->mlx);
	mlx_destroy_image(mlx->mlx, texture_escape.img_ptr);
	sleep(6);
}

int	on_keypress(int key)
{
	int		keycode;
	t_game	*game;

	game = get_game();
	keycode = map_keypress(key);
	if (keycode != -1)
	{
		game->mlx.blocked = 0;
		game->keys[keycode] = true;
	}
	if (keycode == KEY_E)
		toggle_door_in_front();
	if (key == XK_Escape)
		return (end_game_screen(), leave_game(0));
	return (0);
}

int	on_keyrelease(int key)
{
	int		keycode;
	t_game	*game;

	game = get_game();
	keycode = map_keypress(key);
	if (keycode != -1)
		game->keys[keycode] = false;
	return (0);
}
