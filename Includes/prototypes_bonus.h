/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 09:57:13 by yjazouli          #+#    #+#             */
/*   Updated: 2025/09/12 11:09:28 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_BONUS_H
# define PROTOTYPES_BONUS_H

// * =========== Gameplay =========== *
// * Entities *
void			ghosts_update(double dt);
void			update_enemy_texture(t_ghost *ghost);
void			timers_update(double dt);
int				entity_try_move_by(t_entity *ent, double dx, double dy);
// * Minimap *
void			minimap_update(double dt);
// * Movement *
void			update_movement(void);
int				entity_in_cell(int x, int y);
int				resolve_overlap(t_entity *ent, double *nx, double *ny);
int				check_collision(double new_x, double new_y, double radius);
// * Input *
int				on_keypress(int key);
int				on_keyrelease(int key);
// * Engine *
double			now_seconds(void);
void			game_tick(t_engine *engine);
// * Doors *
void			open_door(int x, int y);
void			close_door(int x, int y);
int				door_exists(int x, int y);
int				door_is_open(int x, int y);
void			toggle_door_in_front(void);
// * game *
void			start_game(void);
void			game_update(double dt);
void			game_render(double alpha);
// * Hp *
void			entity_kill(t_entity *ent);
void			player_take_dmg(int dmg);
void			entity_set_hp(t_entity *ent, int max_hp);
int				entity_apply_damage(t_entity *ent, int dmg);
void			entity_update_timers(t_entity *ent, double dt);

// * =========== Graphics =========== *
// * Raycasting *
void			raycasting(void);
// * Health-Bar*
void			render_health_ui(void);
// * Pixel Manipulation *
void			put_image(void);
void			clear_image(void);
void			pixel_put(int x, int y, int color);
// * Minimap *
void			minimap_render(void);
void			draw_walls(t_minimap *mm);
void			draw_pacman(t_pacman *pac);
void			draw_entities(t_entity *ents);
void			world_to_minimap(double wx, double wy, int *px, int *py);
// * Shapes *
void			draw_arc(t_shape s);
void			draw_rect(t_shape s);
void			draw_line(t_shape s);
void			rect_filler(t_shape s);
void			draw_circle(t_shape s);
void			line_filler(t_shape s);
void			circle_filler(t_shape s);
void			arc_filler(t_shape s, double facing, double span);

// * =========== Parsing =========== *
// * Build *
void			build_map(void);
// * Parse *
void			parse(char *path);
// * Validate *
void			validate_map(void);
// * Map *
void			parse_map_line(char *line);
// * Pellets *
int				count_pellets(void);
void			check_all_pellets(void);
int				create_pellet_entity(int x, int y);
// * Ghosts *
int				count_ghosts(void);
int				create_ghost_entity(int x, int y);
// * Entities *
void			start_entities(void);
int				add_entity(int x, int y);
int				mark_entities(char key, int x, int y);
// * Elements *
void			check_elements(void);
void			parse_elements(char *line);

// * =========== Helpers =========== *
// * Gnl *
char			*get_next_line(int fd);
// * Char *
int				is_empty_string(char *str);
// * Strjoin *
char			*ft_strjoin2(char *s1, char *s2);
char			*ft_strjoin3(char *s1, char *s2, char *s3);
// * Map *
int				get_idx(int x, int y, int width);
int				is_wall(t_map *map, int x, int y);
int				is_blocked(t_map *map, int x, int y);

// * Numbers *
char			*ft_itoa(int n);
int				imin(int a, int b);
int				imax(int a, int b);
// * Strdup *
char			*ft_strdup(char *str);
char			*ft_strsdup(char *str);
char			*ft_strndup(char *str, size_t n);
// * Maths *
double			vec2_dist(t_vec2 a, t_vec2 b);
double			vec2_dist_sq(t_vec2 a, t_vec2 b);
double			vec2_dir_and_dist(t_vec2 from, t_vec2 to, t_vec2 *out_dir);
// * Error Handling *
void			cleanup(void);
int				leave_game(int exit_code);
void			ft_free(void *ptr);
void			clean_exit(int status);
void			parse_error(char *msg1);
int				report_error(char *msg1, char *msg2);
// * Memory *
void			*ft_malloc(size_t size);
void			*track(void *ptr, size_t size);
void			*ft_realloc(void *ptr, size_t size);
void			*ft_calloc(size_t nmemb, size_t size);
// * Static *
t_map			*get_map(void);
t_mlx			*get_mlx(void);
t_game			*get_game(void);
t_parse			*get_parse(void);
t_engine		*get_engine(void);
t_camera		*get_camera(void);
t_gameplay		*get_gameplay(void);
t_texture		**enemy_texture(void);

// * bfs *
t_bfs			*get_bfs(void);
int				bfs_find_path(t_bfs *bfs, t_map *map, t_vec2 *start_pos, \
	t_vec2 *end_pos);
int				**get_neighbors(void);	
void			bfs_init(t_bfs *bfs, int width, int height);

// =========== Config =========== //
void			setup_config(void);
void			setup_minimap(void);
void			init_mash(t_mash *mash, t_map *map);
void			minimap_ensure_built(t_minimap *minimap);
void			add_seg(t_mash *mash, t_seg *seg, uint32_t color);
void			build_door_segs(t_mash *mash, t_map *map, uint32_t color);
void			build_border_segs(t_mash *mash, t_map *map, uint32_t color);

// =========== movement =========== //
void			move_player(int direction);
void			move_sideways(t_entity *ent, int direction);
void			rotate_player(t_entity *ent, double angle);
void			move_entity(t_entity *ent, t_map *map, double dt);

// music
void			stop_background_music(void);
t_texture		load_texture(char *path);
void			end_game_screen(void);
t_texture		*get_coin_texture(void);

void			update_ghost_movement(t_ghost *ghost, t_entity \
	*player, t_map *map, double dt);
void			ghost_move_to_attack_player(t_ghost *ghost, \
	t_entity *player, double dt);
int				mouse_handler(int x, int y, t_mlx *mlx);
void			destroy_wall(t_mlx *mlx, t_game *game);
void			destroy_enemy_textures(t_mlx *mlx);
void			destroy_other_textures(t_mlx *mlx, t_game *game);
void			destroy_coin_textures(t_mlx *mlx);
void			destroy_mlx(t_mlx *mlx);
void			start_screen(void);
void			lose_screen(void);
void			load_enemy(t_texture	**enemy_textures);
void			load_wall_textures(t_game *game);
void			load_coins_textures(void);
void			init_ghosts_textures(void);
void			config_textures(void);
void			load_other_textures(t_game *game);
char			*get_coin_texture_path(int index);
void			start_music(void);
void			sort_sprites_by_distance(t_entity *player, t_rend_ents *ents);
void			calculate_sprite_transform(t_entity *player, \
	t_entity *sprite, t_sprite_info *s);
void			draw_the_sprite_transform(t_gameplay *gameplay, int ent_index, \
				t_sprite_info *s_info, double *z_buffer);
void			init_div(t_sprite_info *s_info);
void			render_sprites(double *z_buffer);
void			draw_sprites(double *z_buffer);
int				get_wall_color(t_ray *ray, double step, double *tex_pos);
void			draw_ceiling_and_floor(int x);
void			calc_tex_x(void);
void			calc_wall_tex_idx(void);
void			calc_door_texture(t_ray *ray);
unsigned int	get_texture_color(t_texture *texture, int x, int y);
void			init_steps(void);
void			perform_dda(void);
void			calc_texture(void);
void			draw_wall_x(int x);
void			draw_floor(int x, int y);
void			draw_sky(int x);
void			draw_sprite_type(t_sprite_info *s, int stripe, t_texture *text, \
	double *z_buffer);
void			init_the_sprite_transform(t_entity *player, t_entity *sprite, \
	t_sprite_info *s);
void			sort_sprites_by_distance(t_entity *player, t_rend_ents *ents);
void			init_the_sprite_transform(t_entity *player, t_entity *sprite, \
	t_sprite_info *s);
void			draw_sprite_stripe(t_sprite_info *s, int stripe, \
	double *z_buffer, t_texture *texture);
void			calc_floor(t_floor *info, t_camera *camera, \
	t_texture *floor_txt);
#endif