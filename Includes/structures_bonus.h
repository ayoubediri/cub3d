/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 09:51:59 by yjazouli          #+#    #+#             */
/*   Updated: 2025/08/20 18:36:10 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_BONUS_H
# define STRUCTURES_BONUS_H

// * =========== Typedefs =========== *

typedef struct s_malloc	t_malloc;
typedef struct s_parse	t_parse;
typedef struct s_door	t_door;
typedef struct s_game	t_game;
typedef struct s_map	t_map;
typedef struct s_mlx	t_mlx;

// * =========== Structures =========== *
// * Rendering *

struct					s_mlx
{
	int					bpp;
	int					line;
	void				*mlx;
	void				*win;
	void				*img;
	char				*addr;
	int					width;
	int					endian;
	int					height;
};

// * Parsing *

struct					s_door
{
	int					x;
	int					y;
	int					enabled;
	int					linked_index;
};

struct					s_parse
{
	int					fd;
	char				*line;
	t_parse_state		state;

	int					floor_col;
	int					ceiling_col;
	char				*ea_texture;
	char				*we_texture;
	char				*no_texture;
	char				*so_texture;

	char				dir;
	char				**map;
	int					width;
	int					height;
	int					player_x;
	int					player_y;
};

struct					s_map
{
	int					*grid;
	int					*doors_grid;

	int					width;
	int					height;

	int					player_x;
	int					player_y;
	char				player_dir;

	t_door				*doors;
	int					door_count;
};

// * General *

struct					s_malloc
{
	void				*ptr;
	size_t				size;
	t_malloc			*next;
};

struct					s_game
{
	bool				keys[KEY_TOTAL];
	t_malloc			*tracker;
	t_parse				parse;
	t_malloc			*tail;
	t_map				map;
	t_mlx				mlx;
};

#endif