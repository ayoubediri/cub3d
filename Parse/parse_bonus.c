/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:37:44 by yjazouli          #+#    #+#             */
/*   Updated: 2025/08/20 15:52:16 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	validate_path(char *path)
{
	int	len;

	len = strlen(path);
	if (len < 4)
		parse_error("Filename too short");
	if (strcmp(path + len - 4, ".cub"))
		parse_error("File must end with .cub extension");
}

static int	extract_fd(char *path)
{
	int	fd;

	validate_path(path);
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		report_error("open", strerror(errno));
		clean_exit(1);
	}
	return (fd);
}

static int	is_element(char *line)
{
	int	i;

	i = 0;
	while (line[i] && isspace(line[i]))
		i++;
	if (!strncmp(&line[i], "NO", 2) && isspace(line[i + 2]))
		return (1);
	if (!strncmp(&line[i], "SO", 2) && isspace(line[i + 2]))
		return (1);
	if (!strncmp(&line[i], "WE", 2) && isspace(line[i + 2]))
		return (1);
	if (!strncmp(&line[i], "EA", 2) && isspace(line[i + 2]))
		return (1);
	if (line[i] == 'F' && isspace(line[i + 1]))
		return (1);
	if (line[i] == 'C' && isspace(line[i + 1]))
		return (1);
	return (0);
}

static void	determine_section(void)
{
	t_parse	*parse;

	parse = get_parse();
	if (parse->state == PARSE_ELEMENTS)
	{
		if (is_element(parse->line))
			parse_elements(parse->line);
		else
		{
			check_elements();
			parse->state = PARSE_MAP_LINES;
			parse_map_line(parse->line);
		}
	}
	else
		parse_map_line(parse->line);
}

void	parse(char *path)
{
	t_parse	*parse;

	parse = get_parse();
	parse->fd = extract_fd(path);
	while (1)
	{
		parse->line = get_next_line(parse->fd);
		if (!parse->line)
			break ;
		else if (is_empty_string(parse->line))
		{
			if (parse->state == PARSE_MAP_LINES)
				parse_error("Empty lines inside the map");
			else
				continue ;
		}
		else
			determine_section();
	}
	validate_map();
	build_map();
}
