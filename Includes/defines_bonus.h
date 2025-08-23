/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli@student.1337.ma <yjazouli>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:48:27 by yjazouli          #+#    #+#             */
/*   Updated: 2025/08/23 10:53:27 by yjazouli@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_BONUS_H
# define DEFINES_BONUS_H

// * ========= Defines ========== *

# define BUFFER_SIZE 1024
# define WIDTH 1920
# define HEIGHT 1080
# define FPS 60
# define FOV 60.0
# define ROT_SPEED 0.05
# define MOVE_SPEED 0.05
# define HALF_WIDTH 960
# define HALF_HEIGHT 540

# ifndef M_PI
#  define M_PI		3.14159265358979323846
# endif

// * ======== Textures ========== *

# define FLOOR_TEXTURE_PATH "textures/wall_1.xpm"
# define CEILING_TEXTURE_PATH "textures/wall_1.xpm"
# define SKY_TEXTURE_PATH "textures/sky1.xpm"

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
    SEG_OUTER_ARC,
    SEG_INNER_ARC,
    SEG_TOTAL
}	t_segtype;

typedef enum e_key
{
	KEY_W,
	KEY_A,
	KEY_S,
	KEY_D,
	KEY_LEFT,
	KEY_RIGHT,
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