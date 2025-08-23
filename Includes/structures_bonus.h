/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 09:51:59 by yjazouli          #+#    #+#             */
/*   Updated: 2025/08/23 14:28:29 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_BONUS_H
# define STRUCTURES_BONUS_H

// * =========== Typedefs =========== *

// * Minimap *
typedef struct s_minimap	t_minimap;
typedef struct s_pacman		t_pacman;
typedef struct s_mash		t_mash;
typedef struct s_seg		t_seg;

// * Entities *
typedef struct s_entity		t_entity;
typedef struct s_player		t_player;
typedef struct s_pellet		t_pellet;
typedef struct s_ghost		t_ghost;

typedef struct s_gameplay	t_gameplay;
typedef struct s_camera		t_camera;
typedef struct s_engine		t_engine;
typedef struct s_malloc		t_malloc;
typedef struct s_parse		t_parse;
typedef struct s_door		t_door;
typedef struct s_game		t_game;
typedef struct s_vec2		t_vec2;
typedef struct s_map		t_map;
typedef struct s_mlx		t_mlx;
typedef struct s_ray		t_ray;
typedef struct s_bfs		t_bfs;
typedef struct s_texture	t_texture;
typedef struct s_floor		t_floor;
typedef struct s_sky		t_sky;



// * =========== Structures =========== *

struct						s_vec2
{
	double					x;
	double					y;
};

struct						s_bfs
{
	int						n;
	int						width;
	int						height;

	int						*came;
	int						*queue;
	int						*visited;

	int						queue_end;
	int						queue_start;
	int						queue_capacity;

	int						start;
	int						goal;

	int						*path;
	int						path_length;
	int						path_capacity;

	int						visit_stamp;
};

// * Minimap *

struct						s_seg
{
	int						x;
	int						y;
	int						len;
	uint8_t					dir;
	uint32_t				color;
};

struct						s_mash
{
	int						dirty;
	int						min_x;
	int						min_y;
	int						max_x;
	int						max_y;
	t_seg					*segs;
	int						seg_count;
	int						seg_capacity;
	uint8_t					*nbr_mask;
};

struct						s_pacman
{
	t_entity				*ent;

	double					anim_time;
	double					mouth_open;
	double					mouth_speed;

	double					scale;
};

struct						s_minimap
{
	double					padding;

	int						ox;
	int						oy;
	int						size_px;

	int						cell_px;
	int						content_w;
	int						content_h;
	int						content_x;
	int						content_y;

	double					world_to_px;
	double					world_offset_x;
	double					world_offset_y;

	unsigned int			col_bg;
	unsigned int			col_wall;
	unsigned int			col_door;
	unsigned int			col_pacman;
	unsigned int			col_pellet;
	unsigned int			col_border;

	t_pacman				pacman;
	t_mash					mash;

	t_map					*src_map;
	unsigned int			build_stamp;
};

// * Entities *
struct						s_entity
{
	t_vec2					pos;
	t_vec2					vel;
	t_vec2					dir;
	t_vec2					prev;

	double					radius;
	int						path_idx;
	t_bfs					pathfinder;
	double					path_timer;

	int						hp;
	int						max_hp;
	double					invuln_time;
	double					invuln_duration;

	t_entity_type			type;
};

struct						s_ghost
{
	t_entity				*ent;

	uint32_t				color;
	t_vec2					spawn_point;
};

struct						s_pellet
{
	t_entity				*ent;
};

struct						s_player
{
	t_entity				*ent;
};

// * Raycasting *
struct						s_ray
{
	double					camera_x;
	t_vec2					dir;
	t_vec2					side_dist;
	t_vec2					delta_dist;
	t_vec2					step;
	t_texture				*texture;
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
	int						tex_x;
};

// * Rendering *



struct						s_floor
{
	double					player_z;
	double					row_distance;
	double					floor_step_x;
	double					floor_step_y;
	double					floor_x;
	double					floor_y;
	double					dir_x0;
	double					dir_y0;
	double					dir_x1;
	double					dir_y1;
	int						tex_x;
	int						tex_y;
	unsigned int			color;
};

struct						s_sky
{
	t_texture				*texture;
	double					camera_x;
	double					dir_x;
	double					dir_y;
	double					angle;
	int						tex_x;
	int						tex_y;
	unsigned int			color;
};

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

struct						s_gameplay
{
	t_camera				camera;
	t_player				player;
	t_minimap				minimap;

	t_entity				*entities;
	int						entity_count;
	int						entity_capacity;

	t_ghost					*ghosts;
	int						ghost_count;
	int						ghost_capacity;

	t_pellet				*pellets;
	int						pellet_count;
	int						pellet_capacity;
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

struct						s_texture
{
	int						width;
	int						height;
	int						bpp;
	int						line_length;
	int						endian;
	void					*img_ptr;
	char					*addr;
	char					*path;
};

struct						s_game
{
	bool					keys[KEY_TOTAL];
	t_gameplay				gameplay;
	t_texture				wall_textures[WALL_TOTAL];
	t_texture				floor_texture;
	t_texture				ceiling_texture;
	t_texture				sky_texture;
	t_malloc				*tracker;
	t_engine				engine;
	t_malloc				*tail;
	t_parse					parse;
	t_map					map;
	t_mlx					mlx;
};

#endif