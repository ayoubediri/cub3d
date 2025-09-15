/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiri <adiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:48:27 by yjazouli          #+#    #+#             */
/*   Updated: 2025/09/15 16:57:02 by adiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_BONUS_H
# define DEFINES_BONUS_H

// * ========= Defines ========== *

# define BUFFER_SIZE 1024
# define WIDTH 1920
# define HEIGHT 1010
# define FPS 60
# define FOV 60.0
# define ROT_SPEED 0.05
# define MOVE_SPEED 0.05
# define HALF_WIDTH 960
# define INV_DET -1.732051
# define HALF_HEIGHT 505
# define MOUSE_SENSITIVITY 0.002
# define PELLET_U_DIV 3
# define PELLET_V_DIV 3
# define GHOST_U_DIV 1.0
# define GHOST_V_DIV 1.0
# define MAX_GHOST_MOVES 10
# define NUM_COINS_FRAMES 34
# define FLIB_COINS_ANIM_TIME 0.11764705882
# define TOTAL_FRAMES_SECONDS 4.0
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

// * ======== Textures ========== *

# define GROUND_TEXTURE_PATH "Bonus/assets/ground/ground.xpm"
# define SKY_TEXTURE_PATH "Bonus/assets/sky/panoramic-sea.xpm"
# define DOOR_TEXTURE_CLOSE_PATH "Bonus/assets/door/door.xpm"

// enemy textures number 1
# define ENEMY1_TEXTURE_MED "Bonus/assets/enemy1/1.xpm"
# define ENEMY1_TEXTURE_DOWN "Bonus/assets/enemy1/2.xpm"
# define ENEMY1_TEXTURE_UP "Bonus/assets/enemy1/3.xpm"

// enemy textures number 2
# define ENEMY2_TEXTURE_MED "Bonus/assets/enemy2/1.xpm"
# define ENEMY2_TEXTURE_DOWN "Bonus/assets/enemy2/2.xpm"
# define ENEMY2_TEXTURE_UP "Bonus/assets/enemy2/3.xpm"

// enemy textures number 3
# define ENEMY3_TEXTURE_MED "Bonus/assets/enemy3/1.xpm"
# define ENEMY3_TEXTURE_DOWN "Bonus/assets/enemy3/2.xpm"
# define ENEMY3_TEXTURE_UP "Bonus/assets/enemy3/3.xpm"

// enemy textures number 4
# define ENEMY4_TEXTURE_MED "Bonus/assets/enemy4/1.xpm"
# define ENEMY4_TEXTURE_DOWN "Bonus/assets/enemy4/2.xpm"
# define ENEMY4_TEXTURE_UP "Bonus/assets/enemy4/3.xpm"

// coin
# define COIN_TEXTURE_PATH "Bonus/assets/coin/coin_"
# define COIN_SOUND_PATH "Bonus/assets/coin/coin-sound.wav"

// win
# define WIN_TEXTURE_PATH "Bonus/assets/win_game/WIN_GAME.xpm"
# define WIN_SOUND_PATH "Bonus/assets/win_game/win_game_sound.wav"

// lose
# define LOSE_TEXTURE_PATH "Bonus/assets/game_over/end.xpm"
# define LOSE_SOUND_PATH "Bonus/assets/game_over/lose_sound.wav"

//background
# define BACKGROUND_MUSIC_PATH "Bonus/assets/start_game/background.wav"

// start
# define START_SCREEN_SOUND_PATH "Bonus/assets/start_game/start_music.wav"
# define START_SCREEN_TEXTURE_PATH "Bonus/assets/start_game/start.xpm"

// escape
# define ESCAPE_SCREEN_SOUND_PATH "Bonus/assets/esc/sad_music.wav"
# define ESCAPE_SCREEN_TEXTURE_PATH "Bonus/assets/esc/esc.xpm"

// hurt
# define PLAYER_HIT_SOUND_PATH "Bonus/assets/damage_sound/hurt_sound.wav"

// * ======== Enums ========== *

typedef enum e_map_cell
{
	CELL_EMPTY = 0,
	CELL_WALL = 1,
	CELL_PELLET = 2,
	CELL_DOOR = 3,
	CELL_TOTAL
}	t_map_cell;

typedef enum e_parse_state
{
	PARSE_ELEMENTS,
	PARSE_MAP_LINES
}	t_parse_state;

typedef enum e_segtype
{
	SEG_DIR_HORIZ,
	SEG_DIR_VERT,
	SEG_TOTAL
}	t_segtype;

typedef enum e_entity_type
{
	ENTITY_PLAYER,
	ENTITY_PELLET,
	ENTITY_GHOST,
	ENTITY_TOTAL
}	t_entity_type;

typedef enum e_ghost_state
{
	GHOST_STATE_IDLE,
	GHOST_STATE_CHASING,
	GHOST_STATE_ATTACKING,
	GHOST_STATE_TOTAL
}	t_ghost_state;

typedef enum e_shape_type
{
	SHAPE_SEG,
	SHAPE_LINE,
	SHAPE_CIRCLE,
	SHAPE_RECTANGLE,
	SHAPE_TOTAL
}	t_shape_type;

typedef enum e_key
{
	KEY_W,
	KEY_A,
	KEY_S,
	KEY_D,
	KEY_E,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_ESC,
	KEY_TOTAL
}	t_key;

typedef enum e_wall
{
	WALL_NORTH,
	WALL_SOUTH,
	WALL_EAST,
	WALL_WEST,
	WALL_TOTAL
}	t_wall;

#endif