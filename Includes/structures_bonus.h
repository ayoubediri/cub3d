/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 09:51:59 by yjazouli          #+#    #+#             */
/*   Updated: 2025/08/21 11:19:19 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_BONUS_H
# define STRUCTURES_BONUS_H

// * =========== Typedefs =========== *

typedef struct s_ray		t_ray;
typedef struct s_gameplay	t_gameplay;
typedef struct s_camera		t_camera;
typedef struct s_entity		t_entity;
typedef struct s_player		t_player;
typedef struct s_engine		t_engine;
typedef struct s_malloc		t_malloc;
typedef struct s_parse		t_parse;
typedef struct s_door		t_door;
typedef struct s_game		t_game;
typedef struct s_vec2		t_vec2;
typedef struct s_map		t_map;
typedef struct s_mlx		t_mlx;

// * =========== Structures =========== *

struct						s_vec2
{
	double					x;
	double					y;
};

// * Raycasting *
struct						s_ray
{
	double					camera_x;
	t_vec2					dir;
	t_vec2					side_dist;
	t_vec2					delta_dist;
	t_vec2					step;
	double					height;
	int						start;
	int						end;
	int						hit;
	int						side;
	int						map_x;
	int						map_y;
	int						hit_side;
	double					perp_wall_dist;
	double					wall_x;
};

// * Rendering *

struct						s_camera
{
	t_vec2					pos;
	t_vec2					dir;
	t_vec2					plane;
	t_ray					ray;
	double					fov;
	double					plane_scale;
};

struct						s_mlx
{
	int						bpp;
	int						line;
	void					*mlx;
	void					*win;
	void					*img;
	char					*addr;
	int						width;
	int						endian;
	int						height;
};

struct						s_engine
{
	double					dt;
	double					acc;
	double					last;

	int						target_fps;

	void					(*update)(double);
	void					(*render)(double);
};



// * Gameplay *

struct						s_entity
{
	t_vec2					pos;
	t_vec2					vel;
	t_vec2					dir;
	t_vec2					prev;

	double					radius;
};

struct						s_player
{
	t_entity				*ent;
};

struct						s_gameplay
{
	t_camera				camera;
	t_player				player;

	t_entity				*entities;
	int						entity_count;
	int						entity_capacity;
};

// * Parsing *

struct						s_door
{
	int						x;
	int						y;
	int						enabled;
	int						linked_index;
};

struct						s_parse
{
	int						fd;
	char					*line;
	t_parse_state			state;

	int						floor_col;
	int						ceiling_col;
	char					*ea_texture;
	char					*we_texture;
	char					*no_texture;
	char					*so_texture;

	char					dir;
	char					**map;
	int						width;
	int						height;
	int						player_x;
	int						player_y;
};

struct						s_map
{
	int						*grid;
	int						*doors_grid;

	int						width;
	int						height;

	int						player_x;
	int						player_y;
	char					player_dir;

	t_door					*doors;
	int						door_count;
};

// * General *

struct						s_malloc
{
	void					*ptr;
	size_t					size;
	t_malloc				*next;
};

struct						s_game
{
	bool					keys[KEY_TOTAL];
	t_gameplay				gameplay;
	t_malloc				*tracker;
	t_engine				engine;
	t_malloc				*tail;
	t_parse					parse;
	t_map					map;
	t_mlx					mlx;
};

#endif