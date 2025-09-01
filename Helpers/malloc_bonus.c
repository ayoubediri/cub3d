/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli@student.1337.ma <yjazouli>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:24:10 by yjazouli          #+#    #+#             */
/*   Updated: 2025/08/23 11:21:29 by yjazouli@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
		clean_exit(1);
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
		clean_exit(1);
	}
	return (track(ptr, size));
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total;
	void	*ptr;

	if (nmemb && size > SIZE_MAX / nmemb)
	{
		report_error("calloc", "size overflow");
		clean_exit(1);
	}
	total = nmemb * size;
	ptr = ft_malloc(total);
	memset(ptr, 0, total);
	return (ptr);
}

void	*ft_realloc(void *ptr, size_t size)
{
	t_malloc	*curr;
	void		*newptr;

	if (!ptr)
		return (ft_malloc(size));
	curr = get_game()->tracker;
	while (curr && curr->ptr != ptr)
		curr = curr->next;
	if (!curr)
		return (ft_malloc(size));
	newptr = realloc(curr->ptr, size);
	if (!newptr)
	{
		report_error("realloc", strerror(errno));
		clean_exit(1);
	}
	curr->ptr = newptr;
	curr->size = size;
	return (newptr);
}
