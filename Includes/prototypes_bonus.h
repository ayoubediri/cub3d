/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 09:57:13 by yjazouli          #+#    #+#             */
/*   Updated: 2025/08/20 20:21:14 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_BONUS_H
# define PROTOTYPES_BONUS_H

// * =========== Gameplay =========== *
// * Input *
int			on_keypress(int key);
int			on_keyrelease(int key);
// * Engine *
double		now_seconds(void);
void		game_tick(t_engine *engine);
// * game *
void		start_game(void);
void		game_update(double dt);
void		game_render(double alpha);

// * =========== Graphics =========== *
// * Pixel Manipulation *
void		put_image(void);
void		clear_image(void);
void		pixel_put(int x, int y, int color);

// * =========== Parsing =========== *
// * Build *
void		build_map(void);
// * Parse *
void		parse(char *path);
// * Validate *
void		validate_map(void);
// * Map *
void		parse_map_line(char *line);
// * Doors *
int			count_doors(void);
// * Elements *
void		check_elements(void);
void		parse_elements(char *line);

// * =========== Helpers =========== *
// * Numbers *
char		*ft_itoa(int n);
// * Gnl *
char		*get_next_line(int fd);
// * Char *
int			is_empty_string(char *str);
// * Strjoin *
char		*ft_strjoin2(char *s1, char *s2);
char		*ft_strjoin3(char *s1, char *s2, char *s3);
// * Strdup *
char		*ft_strdup(char *str);
char		*ft_strsdup(char *str);
char		*ft_strndup(char *str, size_t n);
// * Error Handling *
void		cleanup(void);
void		clean_exit(int status);
void		parse_error(char *msg1);
int			report_error(char *msg1, char *msg2);
// * Memory *
void		*ft_malloc(size_t size);
void		*track(void *ptr, size_t size);
void		*ft_realloc(void *ptr, size_t size);
void		*ft_calloc(size_t nmemb, size_t size);
// * Static *
t_map		*get_map(void);
t_mlx		*get_mlx(void);
t_game		*get_game(void);
t_parse		*get_parse(void);
t_engine	*get_engine(void);

// =========== Config =========== //
void		setup_config(void);

#endif