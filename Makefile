NAME         := cub3d
NAME_BONUS    := cub3d_bonus
CC      := cc
CFLAGS  := -g -IIncludes -Iminilibx-linux -Wall -Wextra -Werror

MLX_DIR := minilibx-linux
MLX_LIB := $(MLX_DIR)/libmlx.a
MLX_LINK := -L$(MLX_DIR) -lmlx -lX11 -lXext -lm

SRCS_MANDATORY := $(shell find . \( -path "./minilibx-linux" -o -path "./Mandatory" \) -prune -o -name '*.c' -print)
OBJS_MANDATORY := $(SRCS_MANDATORY:.c=.o)

SRCS_BONUS :=	cub3d_bonus.c \
				Config/door_seg_bonus.c \
				Config/mash_bonus.c \
				Config/minimap_bonus.c \
				Config/seg_bonus.c \
				Config/setup_bonus.c \
				Gameplay/bfs_pathfinding_bonus.c \
				Gameplay/collisions_ent_bonus.c \
				Gameplay/collisions_walls_bonus.c \
				Gameplay/destroy_image_bonus.c \
				Gameplay/game_screen_bonus.c \
				Gameplay/init_textures_bonus.c \
				Gameplay/music_bonus.c \
				Gameplay/load_textures_bonus.c \
				Gameplay/doors_bonus.c \
				Gameplay/engine_bonus.c \
				Gameplay/game_update_bonus.c \
				Gameplay/game_bonus.c \
				Gameplay/ghost_move_bonus.c \
				Gameplay/ghost_update_bonus.c \
				Gameplay/ghosts_bonus.c \
				Gameplay/hp_bonus.c \
				Gameplay/input_bonus.c \
				Gameplay/minimap_update_bonus.c \
				Gameplay/movement_bonus.c \
				Graphics/sprites_bonus.c \
				Graphics/init_sprites_bonus.c \
				Graphics/draw_bonus.c \
				Graphics/dda_algo_bonus.c \
				Graphics/calc_bonus.c \
				Graphics/entities_bonus.c \
				Graphics/fillers_bonus.c \
				Graphics/health_bonus.c \
				Graphics/minimap_bonus.c \
				Graphics/mlx_bonus.c \
				Graphics/pacman_bonus.c \
				Graphics/raycasting_bonus.c \
				Graphics/shapes_bonus.c \
				Graphics/walls_bonus.c \
				Helpers/char_bonus.c \
				Helpers/cleanup_bonus.c \
				Helpers/gameplay_bonus.c \
				Helpers/gnl_bonus.c \
				Helpers/malloc_bonus.c \
				Helpers/map_bonus.c \
				Helpers/maths_bonus.c \
				Helpers/numbers_bonus.c \
				Helpers/parse_bonus.c \
				Helpers/strdup_bonus.c \
				Helpers/strjoin_bonus.c \
				Parse/bfs_plood_fill_bonus.c \
				Parse/build_bonus.c \
				Parse/elements_bonus.c \
				Parse/entities_bonus.c \
				Parse/ghosts_bonus.c \
				Parse/map_bonus.c \
				Parse/parse_bonus.c \
				Parse/pellets_bonus.c \
				Parse/validate_bonus.c \


OBJS_BONUS := $(SRCS_BONUS:.c=.o)

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(OBJS_MANDATORY)
	$(CC) $(CFLAGS) -o $@ $^ $(MLX_LIB) $(MLX_LINK)

$(NAME_BONUS): $(OBJS_BONUS)
	$(CC) $(CFLAGS) -o $@ $^ $(MLX_LIB) $(MLX_LINK)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS_MANDATORY) $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

rebonus: fclean bonus

.PHONY: all clean fclean re rebonus bonus
