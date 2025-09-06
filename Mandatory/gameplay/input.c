/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:20:31 by yjazouli          #+#    #+#             */
/*   Updated: 2025/07/15 23:09:18 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	map_keypress(int key)
{
	if (key == XK_w || key == XK_W)
		return (KEY_W);
	else if (key == XK_a || key == XK_A)
		return (KEY_A);
	else if (key == XK_s || key == XK_S)
		return (KEY_S);
	else if (key == XK_d || key == XK_D)
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
		clean_exit(0);
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
