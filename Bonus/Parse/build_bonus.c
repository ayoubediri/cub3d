/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 13:00:56 by yjazouli          #+#    #+#             */
/*   Updated: 2025/09/03 10:17:01 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	tile_converter(char c)
{
	if (c == '1')
		return (CELL_WALL);
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == 'X')
		return (CELL_EMPTY);
	if (c == '.')
		return (CELL_PELLET);
	if (c == 'D')
		return (CELL_DOOR);
	return (-1);
}

static void	create_map(void)
{
	t_map	*map;
	t_parse	*parse;

	map = get_map();
	parse = get_parse();
	map->width = parse->width;
	map->height = parse->height;
	map->player_x = parse->player_x;
	map->player_y = parse->player_y;
	map->grid = ft_malloc(sizeof(int) * (map->width * map->height));
	memset(map->grid, -1, sizeof(int) * (map->width * map->height));
	start_entities();
}

static void	fill_line(int y, int width, int len)
{
	int		x;
	char	key;
	int		tile;
	t_map	*map;

	x = 0;
	map = get_map();
	while (x < width)
	{
		key = ' ';
		if (x < len && get_parse()->map[y])
			key = get_parse()->map[y][x];
		tile = tile_converter(key);
		mark_entities(key, x, y);
		map->grid[y * width + x] = tile;
		x++;
	}
}

void	fill_rend_ents(void)
{
	t_gameplay	*gameplay;
	t_rend_ents	*curr;
	int			i;

	gameplay = get_gameplay();
	i = 0;
	while (i < gameplay->entity_count)
	{
		if (gameplay->entities[i].type != ENTITY_PLAYER)
		{
			curr = &gameplay->rend_ents[gameplay->rend_ent_count];
			curr->ent = &gameplay->entities[i];
			curr->type = gameplay->entities[i].type;
			gameplay->rend_ent_count++;
		}
		i++;
	}
}

void	build_map(void)
{
	int		y;
	int		len;
	t_game	*game;

	y = 0;
	create_map();
	game = get_game();
	while (y < game->map.height)
	{
		len = strlen(game->parse.map[y]);
		fill_line(y, game->map.width, len);
		y++;
	}
	fill_rend_ents();
}
