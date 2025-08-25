/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 14:49:31 by yjazouli          #+#    #+#             */
/*   Updated: 2025/08/25 18:39:43 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d_bonus.h"

t_door *get_door_at(t_game *game, int x, int y)
{
    t_map *map;
    int index;

    map = &game->map;
    if (x < 0 || x >= map->width || y < 0 || y >= map->height)
        return (NULL);
    index = map->doors_grid[y * map->width + x];
    if (index < 0 || index >= map->door_count)
        return (NULL);
    return (&map->doors[index]);
}

int door_is_open(int x, int y)
{
    t_game *game;
    t_door *door;

    game = get_game();
    if (!game)
        return (0);
    door = get_door_at(game, x, y);
    if (!door)
        return (0);
    return (door->enabled);
}

void open_door(int x, int y)
{
    t_game *game;
    t_door *door;

    game = get_game();
    if (!game)
        return ;
    door = get_door_at(game, x, y);
    if (!door)
        return ;
    door->enabled = 1;
}

void close_door(int x, int y)
{
    t_game *game;
    t_door *door;

    game = get_game();
    if (!game)
        return ;
    door = get_door_at(game, x, y);
    if (!door)
        return ;
    door->enabled = 0;
}

void open_all_doors(void)
{
    t_game *game;
    t_map *map;
    int i;

    i = 0;
    game = get_game();
    map = &game->map;
    while (i < map->door_count)
    {
        map->doors[i].enabled = 1;
        i++;
    }
}
