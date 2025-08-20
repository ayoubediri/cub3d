/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 11:15:56 by yjazouli          #+#    #+#             */
/*   Updated: 2025/08/20 11:16:43 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

char	*ft_strdup(char *str)
{
	char	*new;
	size_t	len;

	if (!str)
		return (NULL);
	len = strlen(str);
	new = ft_malloc(len + 1);
	memcpy(new, str, len);
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
	while (str[len] && !isspace(str[len]))
		len++;
	new = ft_malloc(len + 1);
	memcpy(new, str, len);
	new[len] = 0;
	return (new);
}

char	*ft_strndup(char *str, size_t n)
{
	char	*new;
	size_t	len;

	if (!str)
		return (NULL);
	len = strlen(str);
	if (n < len)
		len = n;
	new = ft_malloc(len + 1);
	memcpy(new, str, len);
	new[len] = 0;
	return (new);
}
