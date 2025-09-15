NAME         := cub3d
NAME_BONUS    := cub3d_bonus
CC      := gcc
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
	   Mandatory/graphics/wall.c \
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

B_CFLAGS  := -g -IBonus/Includes -Iminilibx-linux -Wall -Wextra -Werror
B_MLX_DIR := minilibx-linux
B_MLX_LIB := $(B_MLX_DIR)/libmlx.a
B_MLX_LINK := -L$(B_MLX_DIR) -lmlx -lX11 -lXext -lm

B_SRCS :=	Bonus/cub3d_bonus.c \
			Bonus/Config/door_seg_bonus.c \
			Bonus/Config/mash_bonus.c \
			Bonus/Config/minimap_bonus.c \
			Bonus/Config/seg_bonus.c \
			Bonus/Config/setup_bonus.c \
			Bonus/Gameplay/bfs_pathfinding_bonus.c \
			Bonus/Gameplay/collisions_ent_bonus.c \
			Bonus/Gameplay/collisions_walls_bonus.c \
			Bonus/Gameplay/destroy_image_bonus.c \
			Bonus/Gameplay/game_screen_bonus.c \
			Bonus/Gameplay/init_textures_bonus.c \
			Bonus/Gameplay/music_bonus.c \
			Bonus/Gameplay/load_textures_bonus.c \
			Bonus/Gameplay/doors_bonus.c \
			Bonus/Gameplay/engine_bonus.c \
			Bonus/Gameplay/game_update_bonus.c \
			Bonus/Gameplay/game_bonus.c \
			Bonus/Gameplay/ghost_move_bonus.c \
			Bonus/Gameplay/ghost_update_bonus.c \
			Bonus/Gameplay/ghosts_bonus.c \
			Bonus/Gameplay/hp_bonus.c \
			Bonus/Gameplay/input_bonus.c \
			Bonus/Gameplay/minimap_update_bonus.c \
			Bonus/Gameplay/movement_bonus.c \
			Bonus/Graphics/sprites_bonus.c \
			Bonus/Graphics/init_sprites_bonus.c \
			Bonus/Graphics/draw_bonus.c \
			Bonus/Graphics/dda_algo_bonus.c \
			Bonus/Graphics/calc_bonus.c \
			Bonus/Graphics/entities_bonus.c \
			Bonus/Graphics/fillers_bonus.c \
			Bonus/Graphics/health_bonus.c \
			Bonus/Graphics/minimap_bonus.c \
			Bonus/Graphics/mlx_bonus.c \
			Bonus/Graphics/pacman_bonus.c \
			Bonus/Graphics/raycasting_bonus.c \
			Bonus/Graphics/shapes_bonus.c \
			Bonus/Graphics/walls_bonus.c \
			Bonus/Helpers/char_bonus.c \
			Bonus/Helpers/cleanup_bonus.c \
			Bonus/Helpers/gameplay_bonus.c \
			Bonus/Helpers/gnl_bonus.c \
			Bonus/Helpers/malloc_bonus.c \
			Bonus/Helpers/map_bonus.c \
			Bonus/Helpers/maths_bonus.c \
			Bonus/Helpers/numbers_bonus.c \
			Bonus/Helpers/parse_bonus.c \
			Bonus/Helpers/strdup_bonus.c \
			Bonus/Helpers/strjoin_bonus.c \
			Bonus/Parse/bfs_plood_fill_bonus.c \
			Bonus/Parse/build_bonus.c \
			Bonus/Parse/elements_bonus.c \
			Bonus/Parse/entities_bonus.c \
			Bonus/Parse/ghosts_bonus.c \
			Bonus/Parse/map_bonus.c \
			Bonus/Parse/parse_bonus.c \
			Bonus/Parse/pellets_bonus.c \
			Bonus/Parse/validate_bonus.c 

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
