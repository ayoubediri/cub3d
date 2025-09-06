CC      = cc
CFLAGS  = -g
INCLUDES = -Iminilibx-linux -I/usr/include/minilibx-linux -I.
LIBS    = -Lminilibx-linux -L/usr/include/minilibx-linux -lmlx -lXext -lX11 -lm

SRCS = cub3d.c \
       config/setup.c \
       gameplay/game.c \
       gameplay/input.c \
       gameplay/movment.c \
       graphics/raycast.c \
       graphics/render.c \
       helpers/char.c \
       helpers/cleanup.c \
       helpers/gnl.c \
       helpers/malloc.c \
       helpers/memory.c \
       helpers/numbers.c \
       helpers/print.c \
       helpers/strdup.c \
       helpers/strings.c \
       helpers/strjoin.c \
       parsing/build_map.c \
       parsing/parse.c \
       parsing/parse_element.c \
       parsing/parse_map.c \
       parsing/validate_map.c

OBJS = $(SRCS:.c=.o)

NAME = cub3d

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean