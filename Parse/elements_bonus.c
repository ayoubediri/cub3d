/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 11:07:56 by yjazouli          #+#    #+#             */
/*   Updated: 2025/08/20 11:33:18 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	parse_rgb(char **num)
{
	char	*str;
	int		value;

	value = 0;
	str = *num;
	while (isspace(*str))
		str++;
	if (!isdigit(*str))
		parse_error("RGB component must be a number");
	while (isdigit(*str))
	{
		value = value * 10 + (*str - '0');
		str++;
		if (value > 255)
			parse_error("RGB component must be between 0 and 255");
	}
	*num = str;
	return (value);
}

static int	parse_xor(char *str)
{
	int	r;
	int	g;
	int	b;

	r = parse_rgb(&str);
	if (*str != ',')
		parse_error("RGB components must be separated by commas");
	str++;
	g = parse_rgb(&str);
	if (*str != ',')
		parse_error("RGB components must be separated by commas");
	str++;
	b = parse_rgb(&str);
	while (isspace(*str))
		str++;
	if (*str)
		parse_error("Unexpected characters after RGB xor");
	return ((r << 16) | (g << 8) | b);
}

static char	*parse_texture(char **line, char *name)
{
	char	*path;
	char	*str;

	str = *line;
	str += 2;
	while (isspace(*str))
		str++;
	path = ft_strsdup(str);
	if (!*path)
		parse_error(ft_strjoin2(name, " texture path missing"));
	str += strlen(path);
	while (isspace(*str))
		str++;
	if (*str)
		parse_error(ft_strjoin2("Unexpected characters after ", name));
	*line = str;
	return (path);
}

void	check_elements(void)
{
	t_parse	*parse;

	parse = get_parse();
	if (!parse->no_texture)
		parse_error("Missing NO texture");
	if (!parse->so_texture)
		parse_error("Missing SO texture");
	if (!parse->we_texture)
		parse_error("Missing WE texture");
	if (!parse->ea_texture)
		parse_error("Missing EA texture");
	if (parse->floor_col == -1)
		parse_error("Missing floor color");
	if (parse->ceiling_col == -1)
		parse_error("Missing ceiling color");
}

void	parse_elements(char *line)
{
	t_parse	*parse;

	parse = get_parse();
	while (*line && isspace(*line))
		line++;
	if (!strncmp(line, "NO", 2) && isspace(line[2]))
		parse->no_texture = parse_texture(&line, "NO");
	else if (!strncmp(line, "SO", 2) && isspace(line[2]))
		parse->so_texture = parse_texture(&line, "SO");
	else if (!strncmp(line, "WE", 2) && isspace(line[2]))
		parse->we_texture = parse_texture(&line, "WE");
	else if (!strncmp(line, "EA", 2) && isspace(line[2]))
		parse->ea_texture = parse_texture(&line, "EA");
	else if (*line == 'F')
		parse->floor_col = parse_xor(line + 1);
	else if (*line == 'C')
		parse->ceiling_col = parse_xor(line + 1);
	else
		parse_error("Unknown element");
}
