/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 12:44:50 by yjazouli          #+#    #+#             */
/*   Updated: 2025/08/01 14:29:58 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// * ======== DEFINES ======= * /
# define BUFFER_SIZE 1024

// * ======== INCLUDES ======= * /
# include <X11/keysym.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

// * ======== STRUCTURES ======= * /
typedef struct s_malloc	t_malloc;
typedef struct s_player	t_player;
typedef struct s_parse	t_parse;
typedef struct s_game	t_game;
typedef struct s_map	t_map;
typedef struct s_mlx	t_mlx;
typedef struct s_ray	t_ray;

typedef enum e_parse_state
{
	MAP,
	ELEMENTS
}						t_parse_state;

typedef enum e_key
{
	KEY_W,
	KEY_A,
	KEY_S,
	KEY_D,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_TOTAL
}						t_key;

struct					s_malloc
{
	void				*ptr;
	size_t				size;
	t_malloc			*next;
};

struct					s_parse
{
	char				dir;
	char				**map;
	int					width;
	int					height;
	int					player_x;
	int					player_y;
	int					floor_col;
	int					ceiling_col;
	char				*no_texture;
	char				*so_texture;
	char				*we_texture;
	char				*ea_texture;
};

struct					s_ray
{
	int					side;
	int					map_x;
	int					map_y;
	double				dir_y;
	double				dir_x;
	int					step_y;
	int					step_x;
	int					draw_end;
	int					draw_start;
	double				side_dist_x;
	int					line_height;
	double				side_dist_y;
	double				delta_dist_x;
	double				delta_dist_y;
	double				perp_wall_dist;
};

struct					s_player
{
	double				pos_x;
	double				pos_y;
	double				dir_x;
	double				dir_y;
	double				plane_x;
	double				plane_y;
	double				rot_speed;
	double				move_speed;
};

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

struct					s_map
{
	int					**grid;
	int					width;
	int					height;
	int					player_x;
	int					player_y;
	char				player_dir;
};

struct					s_game
{
	bool				keys[KEY_TOTAL];
	t_malloc			*tracker;
	t_player			player;
	t_parse				scene;
	t_malloc			*tail;
	t_mlx				mlx;
	t_map				map;
};

// * ======== PROTOTYPES ======= * /
// malloc:
void					*ft_realloc(void *ptr, size_t size);
void					*track(void *ptr, size_t size);
void					*ft_malloc(size_t size);
// cleanup:
int						report_error(char *msg1, char *msg2);
void					parse_error(char *msg1);
void					clean_exit(int status);
void					cleanup(void);
// char;
int						is_empty_line(char *line);
int						is_space(int c);
int						is_alpha(int c);
int						is_alnum(int c);
int						is_digit(int c);
// game:
void					process_movement(void);
void					start_game(void);
// input:
int						on_keyrelease(int key);
int						on_keypress(int key);
// print:
void					ft_putendl(char *str, int fd);
void					ft_putstr(char *str, int fd);
void					ft_putchar(char c, int fd);
void					ft_putnbr(int n, int fd);
int						ft_strlen(char *s);
// memory:
void					*ft_memcpy(void *dst, void *src, size_t n);
void					*ft_memset(void *b, int c, size_t len);
void					ft_bzero(void *s, size_t len);
// string:
char					*ft_strrstr(char *haystack, char *needle);
int						ft_strncmp(char *s1, char *s2, int n);
int						ft_strcmp(char *s1, char *s2);
// parse:
void					parse_map_line(char *line);
void					parse_element(char *line);
void					parse_map(char *path);
void					check_elements(void);
void					validate_map(void);
void					build_map(void);
// strjoin:
char					*ft_strjoin3(char *s1, char *s2, char *s3);
char					*ft_strjoin2(char *s1, char *s2);
t_game					*get_game(void);
// strdup:
char					*ft_strndup(char *str, size_t n);
char					*ft_strsdup(char *str);
char					*ft_strdup(char *str);
// config:
void					setup_config(void);
// render:
void					pixel_put(int x, int y, int color);
void					render_background(void);
void					clear_image(void);
void					raycasting(void);
void					put_image(void);
// numbers:
char					*ft_itoa(int n);
// gnl:
char					*get_next_line(int fd);

#endif