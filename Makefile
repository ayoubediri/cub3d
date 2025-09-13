NAME         := cub3d
NAME_BONUS    := cub3d_bonus
CC      := cc
M_CFLAGS  = -g -Wall -Wextra -Werror
M_INCLUDES = -Iminilibx-linux -I/usr/include/minilibx-linux -I. -IMandatory
M_LIBS    = -Lminilibx-linux -L/usr/include/minilibx-linux -lmlx -lXext -lX11 -lm

M_SRCS = Mandatory/cub3d.c \
       Mandatory/config/setup.c \
       Mandatory/gameplay/game.c \
       Mandatory/gameplay/input.c \
       Mandatory/gameplay/movment.c \
       Mandatory/graphics/raycast.c \
       Mandatory/graphics/render.c \
       Mandatory/graphics/textures.c \
       Mandatory/helpers/char.c \
       Mandatory/helpers/cleanup.c \
       Mandatory/helpers/gnl.c \
       Mandatory/helpers/malloc.c \
       Mandatory/helpers/memory.c \
       Mandatory/helpers/numbers.c \
       Mandatory/helpers/print.c \
       Mandatory/helpers/strdup.c \
       Mandatory/helpers/strings.c \
       Mandatory/helpers/strjoin.c \
       Mandatory/parsing/build_map.c \
       Mandatory/parsing/parse.c \
       Mandatory/parsing/parse_element.c \
       Mandatory/parsing/parse_map.c \
       Mandatory/parsing/validate_map.c

M_OBJS = $(M_SRCS:.c=.o)

B_CFLAGS  := -g -I./Includes -Iminilibx-linux -Wall -Wextra -Werror
B_MLX_DIR := minilibx-linux
B_MLX_LIB := $(B_MLX_DIR)/libmlx.a
B_MLX_LINK := -L$(B_MLX_DIR) -lmlx -lX11 -lXext -lm

B_SRCS :=	cub3d_bonus.c \
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
			Parse/validate_bonus.c 

B_OBJS:= $(B_SRCS:.c=.o)

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(M_OBJS)
	$(CC) $(M_CFLAGS) -o $@ $^ $(M_LIBS)

$(NAME_BONUS): $(B_OBJS)
	$(CC) $(B_CFLAGS) -o $@ $^ $(B_MLX_LIB) $(B_MLX_LINK)

Mandatory/%.o: Mandatory/%.c
	$(CC) $(M_CFLAGS) $(M_INCLUDES) -c $< -o $@

./%.o: ./%.c
	$(CC) $(B_CFLAGS) -c $< -o $@

clean:
	rm -f $(M_OBJS) $(B_OBJS)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

rebonus: fclean bonus

.PHONY: all clean fclean re rebonus bonus
