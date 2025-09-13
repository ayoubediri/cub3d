/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiri <adiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:20:31 by yjazouli          #+#    #+#             */
/*   Updated: 2025/09/13 10:10:49 by adiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	map_keypress(int key)
{
	if (key == XK_w || key == XK_W || key == XK_Up || key == 1493)
		return (KEY_W);
	else if (key == XK_a || key == XK_A || key == 1492)
		return (KEY_A);
	else if (key == XK_s || key == XK_S || key == XK_Down || key == 1491)
		return (KEY_S);
	else if (key == XK_d || key == XK_D || key == 1514)
		return (KEY_D);
	else if (key == XK_Left)
		return (KEY_LEFT);
	else if (key == XK_Right)
		return (KEY_RIGHT);
	return (-1);
}

int	on_keypress(int key)
{
	int		keycode;
	t_game	*game;

	if (key == XK_Escape)
		leave_game(0);
	game = get_game();
	keycode = map_keypress(key);
	if (keycode != -1)
		game->keys[keycode] = true;
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
