/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:48:27 by yjazouli          #+#    #+#             */
/*   Updated: 2025/09/01 17:19:16 by yjazouli         ###   ########.fr       */
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
# define HALF_HEIGHT 505
# define MOUSE_SENSITIVITY 0.002
# define PELLET_U_DIV 3
# define PELLET_V_DIV 3
# define GHOST_U_DIV 1.0
# define GHOST_V_DIV 1.0

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

// * ======== Textures ========== *

# define FLOOR_TEXTURE_PATH "textures/wall_1.xpm"
# define CEILING_TEXTURE_PATH "textures/wall_1.xpm"
# define SKY_TEXTURE_PATH "textures/sky1.xpm"
# define GHOST_TEXTURE_PATH "textures/ghost_packman_red_128.xpm"
# define PELLET_TEXTURE_PATH "textures/frame_8.xpm"

# define START_SCREEN_TEXTURE_PATH "assets/start_game/17.xpm"

// enemy textures number 1
# define ENEMY1_TEXTURE_MED "assets/enemy1/1.xpm"
# define ENEMY1_TEXTURE_DOWN "assets/enemy1/2.xpm"
# define ENEMY1_TEXTURE_UP "assets/enemy1/3.xpm"

// enemy textures number 2
# define ENEMY2_TEXTURE_MED "assets/enemy2/1.xpm"
# define ENEMY2_TEXTURE_DOWN "assets/enemy2/2.xpm"
# define ENEMY2_TEXTURE_UP "assets/enemy2/3.xpm"

// enemy textures number 3
# define ENEMY3_TEXTURE_MED "assets/enemy3/1.xpm"
# define ENEMY3_TEXTURE_DOWN "assets/enemy3/2.xpm"
# define ENEMY3_TEXTURE_UP "assets/enemy3/3.xpm"

// enemy textures number 4
# define ENEMY4_TEXTURE_MED "assets/enemy4/1.xpm"
# define ENEMY4_TEXTURE_DOWN "assets/enemy4/2.xpm"
# define ENEMY4_TEXTURE_UP "assets/enemy4/3.xpm"

// win texture
# define WIN_TEXTURE_PATH "assets/WIN_GAME.xpm"

// win sound
# define WIN_SOUND_PATH "assets/win_game_sound.wav"

// lose texture
# define LOSE_TEXTURE_PATH "assets/15.xpm"

// lose sound
# define LOSE_SOUND_PATH "assets/lose_sound.wav"

// coin sound
# define COIN_SOUND_PATH "assets/coin-sound.wav"

// back ground music
# define BACKGROUND_MUSIC_PATH "assets/sounds/back_music_pac_man.wav"

// sky textures
# define SKY_TEXTURE_1 "assets/sky/1.xpm"
# define SKY_TEXTURE_2 "assets/sky/2.xpm"
# define SKY_TEXTURE_3 "assets/sky/3.xpm"

// * ======== Enums ========== *

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
	GHOST_STATE_FLEEING,
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