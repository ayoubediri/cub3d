/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 09:55:36 by yjazouli          #+#    #+#             */
/*   Updated: 2025/08/24 15:50:30 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	count_entities(void)
{
	int		x;
	int		y;
	int		len;
	int		count;
	t_parse	*parse;

	y = 0;
	count = 0;
	parse = get_parse();
	while (y < parse->height)
	{
		x = 0;
		len = strlen(parse->map[y]);
		while (x < len)
		{
			if (parse->map[y][x] == 'X' || parse->map[y][x] == 'N'
				|| parse->map[y][x] == 'S' || parse->map[y][x] == 'E'
				|| parse->map[y][x] == 'W' || parse->map[y][x] == '.')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

static int	create_player_entity(int x, int y, char dir)
{
	int			idx;
	t_gameplay	*gameplay;

	gameplay = get_gameplay();
	idx = add_entity(x, y);
	gameplay->entities[idx].type = ENTITY_PLAYER;
	if (dir == 'N')
		gameplay->entities[idx].dir = (t_vec2){0, -1};
	else if (dir == 'S')
		gameplay->entities[idx].dir = (t_vec2){0, 1};
	else if (dir == 'E')
		gameplay->entities[idx].dir = (t_vec2){1, 0};
	else if (dir == 'W')
		gameplay->entities[idx].dir = (t_vec2){-1, 0};
	gameplay->player.ent = &gameplay->entities[idx];
	gameplay->camera.pos = gameplay->entities[idx].pos;
	gameplay->camera.dir = gameplay->entities[idx].dir;
	gameplay->camera.plane.x = -gameplay->camera.dir.y
		* gameplay->camera.plane_scale;
	gameplay->camera.plane.y = gameplay->camera.dir.x
		* gameplay->camera.plane_scale;
	entity_set_hp(gameplay->player.ent, 100);
	return (idx);
}

int	add_entity(int x, int y)
{
	int			idx;
	t_gameplay	*gameplay;

	gameplay = get_gameplay();
	idx = gameplay->entity_count++;
	gameplay->entities[idx].type = 0;
	gameplay->entities[idx].damage = 25;
	gameplay->entities[idx].radius = 0.2;
	gameplay->entities[idx].pos.x = x + 0.5;
	gameplay->entities[idx].pos.y = y + 0.5;
	gameplay->entities[idx].prev = gameplay->entities[idx].pos;
	bfs_init(&gameplay->entities[idx].pathfinder, get_map()->width,
		get_map()->height);
	gameplay->entities[idx].path_idx = 0;
	gameplay->entities[idx].path_timer = 0.0;
	entity_set_hp(&gameplay->entities[idx], 10);
	return (idx);
}

void	start_entities(void)
{
	t_gameplay	*gameplay;

	gameplay = get_gameplay();
	gameplay->entity_capacity = count_entities();
	if (gameplay->entity_capacity < 1)
		gameplay->entity_capacity = 1;
	gameplay->entities = ft_calloc(gameplay->entity_capacity, sizeof(t_entity));
	gameplay->ghost_capacity = count_ghosts();
	gameplay->ghost_count = 0;
	if (gameplay->ghost_capacity > 0)
		gameplay->ghosts = ft_calloc(gameplay->ghost_capacity, sizeof(t_ghost));
	else
		gameplay->ghosts = NULL;
	gameplay->pellet_capacity = count_pellets();
	gameplay->pellet_count = 0;
	if (gameplay->pellet_capacity > 0)
		gameplay->pellets = ft_calloc(gameplay->pellet_capacity,
				sizeof(t_pellet));
	else
		gameplay->pellets = NULL;
	gameplay->rend_ent_capacity = gameplay->pellet_capacity + gameplay->ghost_capacity;
	gameplay->rend_ents = ft_calloc(gameplay->rend_ent_capacity, sizeof(t_rend_ents));
}

int	mark_entities(char key, int x, int y)
{
	t_map	*map;
	int		idx;

	if (key == '\0')
		return (-1);
	map = get_map();
	if (key == 'N' || key == 'S' || key == 'E' || key == 'W')
	{
		map->player_dir = key;
		map->player_x = x;
		map->player_y = y;
		idx = create_player_entity(x, y, key);
		return (idx);
	}
	if (key == 'X')
	{
		idx = create_ghost_entity(x, y);
		return (idx);
	}
	if (key == '.')
	{
		idx = create_pellet_entity(x, y);
		return (idx);
	}
	return (-1);
}
