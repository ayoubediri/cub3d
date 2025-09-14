/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 11:13:33 by yjazouli          #+#    #+#             */
/*   Updated: 2025/08/20 11:14:15 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*str;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = strlen(s1);
	len2 = strlen(s2);
	str = ft_malloc(len1 + len2 + 1);
	memcpy(str, s1, len1);
	memcpy(str + len1, s2, len2);
	str[len1 + len2] = '\0';
	return (str);
}

char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	char	*str;
	size_t	len1;
	size_t	len2;
	size_t	len3;

	if (!s1 || !s2 || !s3)
		return (NULL);
	len1 = strlen(s1);
	len2 = strlen(s2);
	len3 = strlen(s3);
	str = ft_malloc(len1 + len2 + len3 + 1);
	memcpy(str, s1, len1);
	memcpy(str + len1, s2, len2);
	memcpy(str + len1 + len2, s3, len3);
	str[len1 + len2 + len3] = '\0';
	return (str);
}
