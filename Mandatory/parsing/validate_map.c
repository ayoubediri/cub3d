/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:01:44 by yjazouli          #+#    #+#             */
/*   Updated: 2025/06/26 22:54:36 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	playable_char(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static void	report_map_error(int y, int x, int i, char *error_type)
{
	char	*dir_names[4];
	char	*y_str;
	char	*x_str;
	char	*error_msg;

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

static void	check_boundary(t_parse *scene, int y, int x, int i)
{
	int	directions[4][2];
	int	new_y;
	int	new_x;

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
	if (new_y < 0 || new_y >= scene->height)
		report_map_error(y, x, i, "no vertical boundary");
	if (new_x < 0 || new_x >= ft_strlen(scene->map[new_y]))
		report_map_error(y, x, i, "no horizontal boundary");
	if (scene->map[new_y][new_x] == ' ')
		report_map_error(y, x, i, "a space");
}

static void	check_cell_boundary(t_parse *scene, int y, int x)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		check_boundary(scene, y, x, i);
		i++;
	}
}

void	validate_map(void)
{
	t_parse	*scene;
	int		y;
	int		x;

	scene = &get_game()->scene;
	if (scene->dir == '\0')
		parse_error("No player start position in map");
	y = 0;
	while (y < scene->height)
	{
		x = 0;
		while (scene->map[y][x])
		{
			if (playable_char(scene->map[y][x]))
				check_cell_boundary(scene, y, x);
			x++;
		}
		y++;
	}
}
