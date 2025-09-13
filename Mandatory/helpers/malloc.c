/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiri <adiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 12:46:32 by yjazouli          #+#    #+#             */
/*   Updated: 2025/09/13 06:37:28 by adiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*track(void *ptr, size_t size)
{
	t_game		*game;
	t_malloc	*node;

	game = get_game();
	node = malloc(sizeof(t_malloc));
	if (!node)
	{
		free(ptr);
		report_error("malloc", strerror(errno));
		leave_game(1);
	}
	node->ptr = ptr;
	node->size = size;
	node->next = NULL;
	if (!game->tracker)
	{
		game->tracker = node;
		game->tail = node;
	}
	else
	{
		game->tail->next = node;
		game->tail = game->tail->next;
	}
	return (ptr);
}

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		report_error("malloc", strerror(errno));
		leave_game(1);
	}
	return (track(ptr, size));
}

void	*ft_realloc(void *ptr, size_t size)
{
	void		*new;
	t_malloc	*curr;

	curr = get_game()->tracker;
	while (curr && curr->ptr != ptr)
		curr = curr->next;
	new = ft_malloc(size);
	if (!curr)
		return (new);
	if (size > curr->size)
		ft_memcpy(new, ptr, curr->size);
	else
		ft_memcpy(new, ptr, size);
	return (new);
}
