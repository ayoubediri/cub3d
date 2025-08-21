/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 11:21:14 by yjazouli          #+#    #+#             */
/*   Updated: 2025/08/21 09:54:56 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	valid_char(char c)
{
	return (c == '0' || c == '1' || c == '.' || c == 'D' || c == ' ' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W' || c == 'X');
}

static void	check_player(char c, int y, int x)
{
	static int	player_found = 0;
	t_parse		*parse;

	parse = get_parse();
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (player_found)
			parse_error("Multiple player positions found in map");
		parse->dir = c;
		player_found = 1;
		parse->player_x = x;
		parse->player_y = y;
	}
}

void	parse_map_line(char *line)
{
	static int	y = 0;
	t_parse		*parse;
	int			x;

	x = 0;
	parse = get_parse();
	if (!parse->map)
	{
		parse->map = ft_malloc(sizeof(char *));
		parse->map[0] = NULL;
	}
	parse->map = ft_realloc(parse->map, sizeof(char *) * (y + 2));
	parse->map[y] = ft_strdup(line);
	parse->map[y + 1] = NULL;
	while (line[x])
	{
		if (!valid_char(line[x]))
			parse_error("Invalid character found in map");
		check_player(line[x], y, x);
		x++;
	}
	if (x > parse->width)
		parse->width = x;
	parse->height = ++y;
}
