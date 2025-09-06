/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 13:21:00 by yjazouli          #+#    #+#             */
/*   Updated: 2025/06/14 13:21:20 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strlen(char *s)
{
	int	len;

	len = 0;
	while (s && s[len])
		len++;
	return (len);
}

void	ft_putchar(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
}

void	ft_putnbr(int n, int fd)
{
	long	ln;

	ln = n;
	if (ln < 0)
	{
		write(fd, "-", 1);
		ln = -ln;
	}
	if (ln >= 10)
		ft_putnbr(ln / 10, fd);
	ft_putchar((ln % 10) + '0', fd);
}

void	ft_putendl(char *str, int fd)
{
	ft_putstr(str, fd);
	write(fd, "\n", 1);
}
