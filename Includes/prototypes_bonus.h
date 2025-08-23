/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 09:57:13 by yjazouli          #+#    #+#             */
/*   Updated: 2025/08/23 14:33:20 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_BONUS_H
# define PROTOTYPES_BONUS_H

// * =========== Gameplay =========== *
// * Entities *
void		entities_update(double dt);
// * Minimap *
void		minimap_update(double dt);
// * Movement *
void		update_movement(void);
int			check_collision(double new_x, double new_y);
// * Input *
int			on_keypress(int key);
int			on_keyrelease(int key);
// * Engine *
double		now_seconds(void);
void		game_tick(t_engine *engine);
// * Pathfinding *
int			bfs_init(t_bfs *bfs, int width, int height);
void		bfs_idx_to_xy(int idx, int w, int *x, int *y);
int			bfs_find_path(t_bfs *bfs, t_map *map, int sx, int sy, int tx,
				int ty);
// * game *
void		start_game(void);
void		game_update(double dt);
void		game_render(double alpha);
// * Hp *
void		entity_kill(t_entity *ent);
int			entity_get_hp(t_entity *ent);
int			entity_heal(t_entity *ent, int amount);
void		entity_set_hp(t_entity *ent, int max_hp);
int			entity_apply_damage(t_entity *ent, int dmg);
void		entity_update_timers(t_entity *ent, double dt);

// * =========== Graphics =========== *
// * Raycasting *
void		raycasting(void);
// * Minimap *
void		minimap_render(void);
// * Pixel Manipulation *
void		put_image(void);
void		clear_image(void);
void		pixel_put(int x, int y, int color);

// * =========== Parsing =========== *
// * Build *
void		build_map(void);
// * Doors *
int			count_doors(void);
// * Parse *
void		parse(char *path);
// * Validate *
void		validate_map(void);
// * Map *
void		parse_map_line(char *line);
// * Pellets *
int			count_pellets(void);
int			create_pellet_entity(int x, int y);
// * Ghosts *
int			count_ghosts(void);
int			create_ghost_entity(int x, int y);
// * Entities *
void		start_entities(void);
int			add_entity(int x, int y);
int			mark_entities(char key, int x, int y);
// * Elements *
void		check_elements(void);
void		parse_elements(char *line);

// * =========== Helpers =========== *
// * Gnl *
char		*get_next_line(int fd);
// * Char *
int			is_empty_string(char *str);
// * Strjoin *
char		*ft_strjoin2(char *s1, char *s2);
char		*ft_strjoin3(char *s1, char *s2, char *s3);
// * Map *
int			get_idx(int x, int y, int width);
int			is_wall(t_map *map, int x, int y);
// * Numbers *
char		*ft_itoa(int n);
int			imin(int a, int b);
int			imax(int a, int b);
// * Strdup *
char		*ft_strdup(char *str);
char		*ft_strsdup(char *str);
char		*ft_strndup(char *str, size_t n);
// * Error Handling *
void		cleanup(void);
void		ft_free(void *ptr);
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
t_camera	*get_camera(void);
t_gameplay	*get_gameplay(void);

// =========== Config =========== //
void		setup_config(void);
void		setup_minimap(void);
void		init_mash(t_mash *mash, t_map *map);
void		minimap_ensure_built(t_minimap *minimap);
void		vert_seg(t_mash *mash, t_map *map, uint32_t color);
void		horirz_seg(t_mash *mash, t_map *map, uint32_t color);

// =========== movement =========== //
void		move_player(int direction);
void		move_sideways(t_entity *ent, int direction);
void		rotate_player(t_entity *ent, double angle);

#endif