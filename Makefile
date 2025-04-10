CC = cc
SRCS =  src/main.c src/ray-casting/add_text.c\
        src/ray-casting/mini_map.c\
        src/ray-casting/raycaster.c\
        src/ray-casting/mlx_init.c\
        src/ray-casting/utils.c\
        src/ray-casting/weapon.c\
        src/ray-casting/health_bar.c\
        src/ray-casting/handle_frames.c\
        src/ray-casting/mouse_handling.c\
        src/ray-casting/handle_keypress.c\
        src/ray-casting/draw.c\
        src/ray-casting/door_animation.c\
        src/ray-casting/raycaster_utils1.c\
        src/ray-casting/raycaster_utils.c \
        src/parse/parse_helpers.c \
        src/parse/parse_helpers2.c \
        src/parse/parse_helpers3.c \
        src/parse/parse_map.c \
        src/parse/parse_mapv2.c \
        src/parse/parse_mapv3.c \
        src/parse/parse.c\
        src/parse/parse_outils.c\
        src/ray-casting/draw_walls.c\
# SRCS_BNS = 

LIB = libft/libft.a
NAME = cub3D
OBJ = $(SRCS:.c=.o)

GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
NC = \033[0m
BLACK = \033[0;30m
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m

all : $(NAME) $(LIB)

$(LIB):
	@$(MAKE) -s -C libft/
	@echo "$(GREEN)✅ Libft compiled successfully.$(NC)"

$(NAME): $(OBJ) $(LIB)
	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME) $(LIB)
	@echo "$(GREEN)✅ $(NAME) built successfully! You can now run ./$(NAME) <map_file>.cub$(NC)" 
	@echo "$(GREEN) ________  ___  ___  ________  ________  ________ $(NC)"
	@echo "$(GREEN)|\   ____\|\  \|\  \|\   __  \|\_____  \|\   ___ \ $(NC)"
	@echo "$(GREEN)\ \  \___|\ \  \\\  \ \  \|\ /\|____|\ /\ \  \_|\ \  $(NC)"
	@echo "$(GREEN) \ \  \    \ \  \\\  \ \   __  \    \|\  \ \  \ \\ \ $(NC)"
	@echo "$(GREEN)  \ \  \____\ \  \\\  \ \  \|\  \  __\_\  \ \  \_\\ \  $(NC)"
	@echo "$(GREEN)   \ \_______\ \_______\ \_______\|\_______\ \_______\ $(NC)"
	@echo "$(GREEN)    \|_______|\|_______|\|_______|\|_______|\|_______| $(NC)"
	@echo ""

	@echo "$(CYAN)--- Controls ----------------|$(NC)"
	@echo "$(CYAN) W           : Move Forward  |$(NC)"
	@echo "$(CYAN) S           : Move Backward |$(NC)"
	@echo "$(CYAN) A           : Strafe Left   |$(NC)"
	@echo "$(CYAN) D           : Strafe Right  |$(NC)"
	@echo "$(CYAN) Left Arrow  : Rotate Left   |$(NC)"
	@echo "$(CYAN) Right Arrow : Rotate Right  |$(NC)"
	@echo "$(CYAN) ESC         : Exit Game     |$(NC)"
	@echo "$(CYAN)-----------------------------|$(NC)"
	@echo ""
	@echo "$(YELLOW)~~~~~~ Developed by ~~~~~   $(NC)"
	@echo "$(WHITE)>> <iouhssei>$(NC)" #
	@echo "$(RED)>> <mouadmatadorewinners19372005> $(NC)"
	@echo "$(WHITE)   Ben Guerir, April 2025   $(NC)" #
	@echo "$(YELLOW)~~~~~~~~~~~~~~~~~~~~~~~~~$(NC)" #

%.o: %.c
	@$(CC) -Wall -Wextra -Werror -g -I/usr/include -Imlx_linux -O3 -c $< -o $@

clean :
	@echo "$(RED)Cleaning libft objects...$(NC)"
	@$(MAKE) clean -s -C libft/
	@echo "$(RED)Cleaning project objects...$(NC)"
	@rm -f $(OBJ)

fclean : clean
	@echo "$(RED)Cleaning libft library...$(NC)"
	@$(MAKE) fclean -s -C libft/
	@echo "$(RED)Cleaning project executable $(NAME)...$(NC)"
	@rm -rf $(NAME)
	@echo "$(RED)Full clean complete.$(NC)"

re : fclean all

.PHONY: all clean fclean re

.SECONDARY: $(OBJ)
