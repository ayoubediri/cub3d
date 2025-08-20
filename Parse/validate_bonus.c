/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 11:38:01 by yjazouli          #+#    #+#             */
/*   Updated: 2025/08/20 13:01:11 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	playable_char(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == '.');
}

static void	report_map_error(int y, int x, int i, char *error_type)
{
	char	*y_str;
	char	*x_str;
	char	*error_msg;
	char	*dir_names[4];

	dir_names[0] = "north";
	dir_names[1] = "east";
	dir_names[2] = "south";
	dir_names[3] = "west";
	y_str = ft_itoa(y);
	x_str = ft_itoa(x);
	error_msg = ft_strjoin3("Map not enclosed: position (", y_str, ",");
	error_msg = ft_strjoin3(error_msg, x_str, ") has ");
	error_msg = ft_strjoin3(error_msg, error_type, " in ");
	error_msg = ft_strjoin3(error_msg, dir_names[i], " direction");
	parse_error(error_msg);
}

static void	check_boundary(t_parse *parse, int y, int x, int i)
{
	int		directions[4][2];
	int		new_y;
	int		new_x;
	size_t	row_len;

	directions[0][0] = -1;
	directions[0][1] = 0;
	directions[1][0] = 0;
	directions[1][1] = 1;
	directions[2][0] = 1;
	directions[2][1] = 0;
	directions[3][0] = 0;
	directions[3][1] = -1;
	new_y = y + directions[i][0];
	new_x = x + directions[i][1];
	if (new_y < 0 || new_y >= parse->height)
		report_map_error(y, x, i, "no vertical boundary");
	row_len = strlen(parse->map[new_y]);
	if (new_x < 0 || (size_t)new_x >= row_len)
		report_map_error(y, x, i, "no horizontal boundary");
	if (parse->map[new_y][new_x] == ' ')
		report_map_error(y, x, i, "a space");
}

static void	check_cell_boundary(t_parse *parse, int y, int x)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		check_boundary(parse, y, x, i);
		i++;
	}
}

void	validate_map(void)
{
	t_parse	*parse;
	int		x;
	int		y;

	x = 0;
	y = 0;
	parse = get_parse();
	if (parse->dir == 0)
		parse_error("No player spawn point set");
	while (y < parse->height)
	{
		x = 0;
		while (parse->map[y][x])
		{
			if (playable_char(parse->map[y][x]))
				check_cell_boundary(parse, y, x);
			x++;
		}
		y++;
	}
}
