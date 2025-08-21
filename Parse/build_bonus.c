/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 13:00:56 by yjazouli          #+#    #+#             */
/*   Updated: 2025/08/21 11:14:58 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	print_entities(void)
{
    t_gameplay	*game;
    int		i;

    game = get_gameplay();
    if (!game)
    {
        printf("print_entities: no game\n");
        return ;
    }
    if (!game->entities || game->entity_count <= 0)
    {
        printf("no entities\n");
        return ;
    }
    printf("entities (%d):\n", game->entity_count);
    i = 0;
    while (i < game->entity_count)
    {
        t_entity *e = &game->entities[i];
        printf("  [%2d] pos=(%.2f,%.2f) prev=(%.2f,%.2f) vel=(%.2f,%.2f) radius=%.2f\n",
            i,
            e->pos.x, e->pos.y,
            e->prev.x, e->prev.y,
            e->vel.x, e->vel.y,
            e->radius);
        i++;
    }
}

static void	print_camera(void)
{
    t_gameplay *gp = get_gameplay();

    if (!gp)
    {
        printf("print_camera: no gameplay\n");
        return ;
    }
    printf("camera:\n");
    printf("  pos   = (%.4f, %.4f)\n", gp->camera.pos.x, gp->camera.pos.y);
    printf("  dir   = (%.4f, %.4f)\n", gp->camera.dir.x, gp->camera.dir.y);
    printf("  plane = (%.4f, %.4f)\n", gp->camera.plane.x, gp->camera.plane.y);
    printf("  fov   = %.6f rad (%.2f deg)\n",
        gp->camera.fov,
        (gp->camera.fov * 180.0 / M_PI));
}

static int	tile_converter(char c)
{
	if (c == '1')
		return (1);
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == 'X')
		return (0);
	if (c == '.')
		return (2);
	if (c == 'D')
		return (3);
	return (-1);
}

static void	create_map(void)
{
	int		i;
	t_map	*map;
	t_parse	*parse;

	i = 0;
	map = get_map();
	parse = get_parse();
	map->width = parse->width;
	map->height = parse->height;
	map->player_x = parse->player_x;
	map->player_y = parse->player_y;
	map->grid = ft_malloc(sizeof(int) * (map->width * map->height));
	map->doors_grid = ft_malloc(sizeof(int) * (map->width * map->height));
	memset(map->grid, -1, sizeof(int) * (map->width * map->height));
	memset(map->doors_grid, -1, sizeof(int) * (map->width * map->height));
	map->door_count = count_doors();
	map->doors = ft_malloc(sizeof(t_door) * map->door_count);
	while (i < map->door_count)
	{
		map->doors[i].x = -1;
		map->doors[i].y = -1;
		map->doors[i].enabled = 1;
		map->doors[i].linked_index = -1;
		i++;
	}
	start_entities();
}

static void	fill_line(int y, int width, int len, int *door_idx)
{
	int		x;
	char	key;
	int		idx;
	int		cell;
	int		tile;
	t_map	*map;
	t_parse	*parse;

	x = 0;
	cell = 0;
	map = get_map();
	parse = get_parse();
	while (x < width)
	{
		key = ' ';
		cell = y * width + x;
		if (x < len && parse->map[y])
			key = parse->map[y][x];
		tile = tile_converter(key);
		if (mark_entities(key, x, y) >= 0)
			tile = 0;
		if (tile == 3 && map->doors && *door_idx < map->door_count)
		{
			idx = (*door_idx)++;
			map->doors[idx].x = x;
			map->doors[idx].y = y;
			map->doors[idx].enabled = 1;
			map->doors[idx].linked_index = -1;
			map->doors_grid[cell] = idx;
		}
		map->grid[cell] = tile;
		x++;
	}
}

void	build_map(void)
{
	int		y;
	int		len;
	t_game	*game;
	int		door_idx;

	y = 0;
	create_map();
	door_idx = 0;
	game = get_game();
	while (y < game->map.height)
	{
		len = strlen(game->parse.map[y]);
		fill_line(y, game->map.width, len, &door_idx);
		y++;
	}
	print_entities();
	print_camera();
}
