NAME = cub3D
CC = gcc
CFLAGS =-g -Wall -Wextra -Werror
SRCS = ./src/main.c\
		./src/get_next_line.c\
		./src/read_cubfile.c\
		./src/error.c\
		./src/key.c\
		./src/move.c\
		./src/create_bmp.c\
		./src/load_img.c\
		./src/load_color.c\
		./src/load_window.c\
		./src/load_map.c\
		./src/check_map_closed.c\
		./src/check_map.c\
		./src/check_map_form.c\
		./src/wall_casting.c\
		./src/free.c\
		./src/hash.c\
		./src/draw.c\
		./src/sprite_casting.c\
		./src/wall_param.c\

OBJS = $(SRCS:%.c=%.o)

INCLUDES = -I ./includes/cub3d.h\
		./includes/mlx.h\

FRAMEWORK = -L ./minilibx-linux -lmlx -I ./minilibx-linux -lXext -lX11 -lm

$(NAME): $(OBJS)
	$(MAKE) -C libft
	$(MAKE) -C minilibx-linux
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) libft/libft.a $(FRAMEWORK)

all: $(NAME)

clean:
	rm -f $(OBJS)
	make clean -C ./libft
	make clean -C ./minilibx-linux

fclean: clean
	rm -f $(NAME)
	make fclean -C ./libft

re: fclean all
.PHONY: all clean fclean re
