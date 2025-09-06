/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 13:05:53 by yjazouli          #+#    #+#             */
/*   Updated: 2025/06/14 16:36:45 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	report_error(char *msg1, char *msg2)
{
	ft_putstr("cub3d: ", 2);
	ft_putstr(msg1, 2);
	if (msg2)
	{
		ft_putstr(": ", 2);
		ft_putstr(msg2, 2);
	}
	ft_putchar('\n', 2);
	return (1);
}

void	parse_error(char *msg1)
{
	ft_putendl("Error", 2);
	ft_putendl(msg1, 2);
	clean_exit(1);
}

void	cleanup(void)
{
	t_game		*game;
	t_malloc	*curr;
	t_malloc	*next;

	game = get_game();
	curr = game->tracker;
	while (curr)
	{
		next = curr->next;
		free(curr->ptr);
		free(curr);
		curr = next;
	}
}

void	clean_exit(int status)
{
	cleanup();
	exit(status);
}
