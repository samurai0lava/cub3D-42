CC = cc
FLAGS = -Wall -Wextra -Werror -Imlx -c -g
SRCS =	src/main.c src/ray-casting/add_text.c src/ray-casting/mini_map.c src/ray-casting/raycaster.c \
		src/ray-casting/mlx_init.c src/ray-casting/utils.c \
		src/ray-casting/weapon.c src/ray-casting/health_bar.c\
		src/ray-casting/handle_frames.c
SRCS_PARCE = src/parce/parce_helper.c src/parce/parce_map.c src/parce/parce_mapv2.c src/parce/parce.c
LIB = libft/libft.a
NAME = cub3D
OBJ = $(SRCS:.c=.o)

GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
NC = \033[0m

all : $(NAME) $(LIB)

$(LIB):
	$(MAKE) -C libft/

$(NAME): $(OBJ) $(LIB)
	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME) $(LIB)

%.o: %.c
	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O4 -c $< -o $@

clean :
	$(MAKE) clean -C libft/
	@rm -f $(OBJ)

fclean : clean
	$(MAKE) fclean -C libft/
	@rm -rf $(NAME)

re : fclean all 

.PHONY: all clean fclean re

.SECONDARY: $(OBJ)
