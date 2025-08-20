/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 11:43:00 by yjazouli          #+#    #+#             */
/*   Updated: 2025/08/20 11:43:33 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	fill_itoa(char *str, int n, int len)
{
	int	sign;

	sign = 1;
	if (n < 0)
		sign = -1;
	str[len] = '\0';
	if (n == 0)
		str[0] = '0';
	while (len > 0 && n != 0)
	{
		if (n < 0)
			str[--len] = -(n % 10) + '0';
		else
			str[--len] = (n % 10) + '0';
		n /= 10;
	}
	if (sign == -1)
		str[0] = '-';
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;
	int		original;

	len = 0;
	original = n;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	str = ft_malloc(len + 1);
	fill_itoa(str, original, len);
	return (str);
}
