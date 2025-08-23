/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pellets_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 14:32:12 by yjazouli          #+#    #+#             */
/*   Updated: 2025/08/23 14:47:42 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d_bonus.h"

int	count_pellets(void)
{
    int		x;
    int		y;
    int		len;
    int		count;
    t_parse	*parse;

    parse = get_parse();
    if (!parse)
        return (0);
    y = 0;
    count = 0;
    while (y < parse->height)
    {
        x = 0;
        len = strlen(parse->map[y]);
        while (x < len)
        {
            if (parse->map[y][x] == '.')
                count++;
            x++;
        }
        y++;
    }
    return (count);
}

int	create_pellet_entity(int x, int y)
{
    int			idx;
    t_gameplay	*gameplay;

    gameplay = get_gameplay();
    idx = add_entity(x, y);
    gameplay->entities[idx].type = ENTITY_PELLET;
    if (gameplay->pellets && gameplay->pellet_count < gameplay->pellet_capacity)
    {
        gameplay->pellets[gameplay->pellet_count].ent = &gameplay->entities[idx];
        gameplay->pellet_count++;
    }
    return (idx);
}

