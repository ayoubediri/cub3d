/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:48:22 by yjazouli          #+#    #+#             */
/*   Updated: 2025/06/14 18:06:56 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strdup(char *str)
{
	char	*new;
	size_t	len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	new = ft_malloc(len + 1);
	ft_memcpy(new, str, len);
	new[len] = 0;
	return (new);
}

char	*ft_strndup(char *str, size_t n)
{
	char	*new;
	size_t	len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (n < len)
		len = n;
	new = ft_malloc(len + 1);
	ft_memcpy(new, str, len);
	new[len] = 0;
	return (new);
}

char	*ft_strsdup(char *str)
{
	char	*new;
	size_t	len;

	len = 0;
	if (!str)
		return (NULL);
	while (str[len] && !is_space(str[len]))
		len++;
	new = ft_malloc(len + 1);
	ft_memcpy(new, str, len);
	new[len] = 0;
	return (new);
}
