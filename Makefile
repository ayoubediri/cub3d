NAME    := cub3d_bonus
CC      := gcc
CFLAGS  := -Wall -Wextra -Werror -g -IIncludes

SRCS := $(shell find . -name '*.c')
OBJS := $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
