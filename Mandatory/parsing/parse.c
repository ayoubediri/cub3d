/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiri <adiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:13:18 by yjazouli          #+#    #+#             */
/*   Updated: 2025/09/13 06:37:14 by adiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	validate_path(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 4)
		parse_error("File must be at least 4 characters long");
	if (ft_strcmp(".cub", path + len - 4))
		parse_error("File must end with the extension .cub");
}

static int	extract_fd(char *path)
{
	int	fd;

	validate_path(path);
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		report_error("open", strerror(errno));
		leave_game(1);
	}
	return (fd);
}

static int	is_element(char *line)
{
	int	i;

	i = 0;
	while (is_space(line[i]))
		i++;
	if (!ft_strncmp(&line[i], "NO", 2) && is_space(line[i + 2]))
		return (1);
	if (!ft_strncmp(&line[i], "SO", 2) && is_space(line[i + 2]))
		return (1);
	if (!ft_strncmp(&line[i], "WE", 2) && is_space(line[i + 2]))
		return (1);
	if (!ft_strncmp(&line[i], "EA", 2) && is_space(line[i + 2]))
		return (1);
	if (line[i] == 'F' && is_space(line[i + 1]))
		return (1);
	if (line[i] == 'C' && is_space(line[i + 1]))
		return (1);
	return (0);
}

static void	determine_section(char *line, t_parse_state *state)
{
	if (*state == ELEMENTS)
	{
		if (is_element(line))
			parse_element(line);
		else
		{
			*state = MAP;
			check_elements();
			parse_map_line(line);
		}
	}
	else
		parse_map_line(line);
}

void	parse_map(char *path)
{
	int				fd;
	char			*line;
	t_parse_state	state;

	state = ELEMENTS;
	fd = extract_fd(path);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		else if (is_empty_line(line))
		{
			if (state == MAP)
				parse_error("Empty lines inside the map");
			else
				continue ;
		}
		else
			determine_section(line, &state);
	}
	validate_map();
	build_map();
}
