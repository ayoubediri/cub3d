NAME    := cub3d_bonus
CC      := gcc
CFLAGS  := -g -IIncludes -Iminilibx-linux

MLX_DIR := minilibx-linux
MLX_LIB := $(MLX_DIR)/libmlx.a
MLX_LINK := -L$(MLX_DIR) -lmlx -lX11 -lXext -lm

SRCS := $(shell find . -name '*.c' -not -path "./minilibx-linux/*")
OBJS := $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(MLX_LINK)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
