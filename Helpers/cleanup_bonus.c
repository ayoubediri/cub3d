/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:34:24 by yjazouli          #+#    #+#             */
/*   Updated: 2025/08/22 20:39:38 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	report_error(char *msg1, char *msg2)
{
	fprintf(stderr, "cub3d: %s", msg1);
	if (msg2)
		fprintf(stderr, ": %s", msg2);
	fprintf(stderr, "\n");
	return (1);
}

void	parse_error(char *msg1)
{
	fprintf(stderr, "Error: %s\n", msg1);
	clean_exit(1);
}

void	cleanup(void)
{
	t_game		*game;
	t_malloc	*curr;
	t_malloc	*next;

	game = get_game();
	
	// Free all tracked memory allocations
	curr = game->tracker;
	while (curr)
	{
		next = curr->next;
		if (curr->ptr)
			free(curr->ptr);
		free(curr);
		curr = next;
	}
	
	// Reset tracker pointers
	game->tracker = NULL;
	game->tail = NULL;
}

void	ft_free(void *ptr)
{
    t_game		*game;
    t_malloc	*curr;
    t_malloc	*prev;

    game = get_game();
    prev = NULL;
    curr = game->tracker;
    while (curr && curr->ptr != ptr)
    {
        prev = curr;
        curr = curr->next;
    }
    if (prev)
        prev->next = curr->next;
    else
        game->tracker = curr->next;
    if (game->tail == curr)
        game->tail = prev;
    free(curr->ptr);
    free(curr);
}

void	clean_exit(int status)
{
	cleanup();
	exit(status);
}
