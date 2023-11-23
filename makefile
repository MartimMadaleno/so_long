NAME = so_long
RM = rm -f
CC = gcc  # or cc, whichever you're using
CFLAGS = -Wall -Werror -Wextra
MLXFLAGS = -L./mlx -lmlx -lXext -lX11

SRC = main.c \
	utils/draw_map.c\
	utils/key_press.c\
	utils/read_map.c\
	utils/validate_count.c\
	utils/is_map_closed.c\
	utils/start_flood_fill.c\
	utils/free_data.c\
	utils/h_error.c\
	get_next_line/get_next_line.c \
	get_next_line/get_next_line_utils.c\
	libft/ft_bzero.c\
	libft/ft_calloc.c\
	libft/ft_putchar.c\
	libft/ft_putnbr.c\
	libft/ft_putstr.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(MLXFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
