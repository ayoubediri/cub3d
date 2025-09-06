/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:57:28 by yjazouli          #+#    #+#             */
/*   Updated: 2025/06/27 11:40:44 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parse_rgb(char **num)
{
	char	*str;
	int		value;

	value = 0;
	str = *num;
	while (is_space(*str))
		str++;
	if (!is_digit(*str))
		parse_error("RGB component must be a number");
	while (is_digit(*str))
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
	while (is_space(*str))
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
	while (is_space(*str))
		str++;
	path = ft_strsdup(str);
	if (!*path)
		parse_error(ft_strjoin2(name, " texture path missing"));
	str += ft_strlen(path);
	while (is_space(*str))
		str++;
	if (*str)
		parse_error(ft_strjoin2("Unexpected characters after ", name));
	*line = str;
	return (path);
}

void	check_elements(void)
{
	t_parse	scene;

	scene = get_game()->scene;
	if (!scene.no_texture)
		parse_error("Missing NO texture");
	if (!scene.so_texture)
		parse_error("Missing SO texture");
	if (!scene.we_texture)
		parse_error("Missing WE texture");
	if (!scene.ea_texture)
		parse_error("Missing EA texture");
	if (scene.floor_col == -1)
		parse_error("Missing Floor col");
	if (scene.ceiling_col == -1)
		parse_error("Missing Ceiling col");
}

void	parse_element(char *line)
{
	t_parse	*scene;

	scene = &get_game()->scene;
	while (is_space(*line))
		line++;
	if (!ft_strncmp(line, "NO", 2))
		scene->no_texture = parse_texture(&line, "NO");
	else if (!ft_strncmp(line, "SO", 2))
		scene->so_texture = parse_texture(&line, "SO");
	else if (!ft_strncmp(line, "WE", 2))
		scene->we_texture = parse_texture(&line, "WE");
	else if (!ft_strncmp(line, "EA", 2))
		scene->ea_texture = parse_texture(&line, "EA");
	else if (*line == 'F')
		scene->floor_col = parse_xor(line + 1);
	else if (*line == 'C')
		scene->ceiling_col = parse_xor(line + 1);
	else
		parse_error("Invalid element line");
}
