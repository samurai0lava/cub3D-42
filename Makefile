CC = cc
SRCS = 	main.c\
		src/ray-casting/raycaster.c\
        src/ray-casting/mlx_init.c\
        src/ray-casting/utils.c\
        src/ray-casting/weapon.c\
        src/ray-casting/handle_frames.c\
		src/ray-casting/draw_weapon2.c\
		src/ray-casting/draw_weapon.c\
        src/ray-casting/handle_keypress.c\
        src/ray-casting/draw.c\
        src/ray-casting/raycaster_utils1.c\
        src/ray-casting/raycaster_utils.c \
		src/parse/parse_helper_2_complete.c\
        src/parse/parse_helpers.c \
        src/parse/parse_helpers2.c \
        src/parse/parse_helpers3.c \
        src/parse/parse_map.c \
        src/parse/parse_mapv2.c \
        src/parse/parse_mapv3.c \
        src/parse/parse.c\
        src/parse/parse_outils.c\
		src/parse/check_double_texture.c\
        src/ray-casting/draw_walls.c\
		src/ray-casting/utils2.c\
		src/ray-casting/raycaster_utils2.c\
		src/parse/parse_map_complete.c\
		src/parse/parse_helper_3_complete.c\
		src/parse/parse_helpers4.c\
		src/parse/helpers.c
		


BONS =  src/parse/parse_helpers.c \
        src/parse/parse_helpers2.c \
        src/parse/parse_helpers3.c \
        src/parse/parse_map.c \
        src/parse/parse_mapv2.c \
        src/parse/parse_mapv3.c \
        src/parse/parse.c\
        src/parse/parse_outils.c\
		src/parse/check_double_texture.c\
		src/parse/parse_helpers4.c\
		src/parse/parse_helper_3_complete.c\
		src/parse/parse_helper_2_complete.c\
		src/parse/parse_map_complete.c\
        src_bonus/ray-casting-bonus/mini_map.c\
        src_bonus/ray-casting-bonus/raycaster.c\
        src_bonus/ray-casting-bonus/mlx_init.c\
        src_bonus/ray-casting-bonus/utils.c\
        src_bonus/ray-casting-bonus/weapon.c\
        src_bonus/ray-casting-bonus/handle_frames.c\
        src_bonus/ray-casting-bonus/mouse_handling.c\
        src_bonus/ray-casting-bonus/handle_keypress.c\
        src_bonus/ray-casting-bonus/draw.c\
        src_bonus/ray-casting-bonus/raycaster_utils1.c\
        src_bonus/ray-casting-bonus/draw_walls.c\
        src_bonus/ray-casting-bonus/raycaster_utils.c \
		main.c\
		src_bonus/ray-casting-bonus/draw_weapon2.c\
		src_bonus/ray-casting-bonus/draw_weapon.c\
		src_bonus/ray-casting-bonus/utils2.c\
		src_bonus/ray-casting-bonus/raycaster_utils2.c\
		src_bonus/ray-casting-bonus/mini_map_helper.c\

LIB = libft/libft.a
NAME = cub3D
NAME_BONUS = cub3d_bonus
OBJ = $(SRCS:.c=.o)
OBJ_BONUS = $(BONS:.c=.o)

GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
NC = \033[0m
BLACK = \033[0;30m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m

all : $(NAME)

$(LIB):
	@$(MAKE) -s -C libft/
	@echo "$(GREEN)✅ Libft compiled successfully.$(NC)"

$(NAME): $(OBJ) $(LIB)
	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME) $(LIB) -fsanitize=address
	@echo "$(GREEN)✅ $(NAME) built successfully! You can now run ./$(NAME) <map_file>.cub$(NC)"
	@echo "$(GREEN) ________  ___  ___  ________  ________  ________ $(NC)"
	@echo "$(GREEN)|\   ____\|\  \|\  \|\   __  \|\_____  \|\   ___ \ $(NC)"
	@echo "$(GREEN)\ \  \___|\ \  \\\  \ \  \|\ /\|____|\ /\ \  \_|\ \  $(NC)"
	@echo "$(GREEN) \ \  \    \ \  \\\  \ \   __  \    \|\  \ \  \ \\ \ $(NC)"
	@echo "$(GREEN)  \ \  \____\ \  \\\  \ \  \|\  \  __\_\  \ \  \_\\ \  $(NC)"
	@echo "$(GREEN)   \ \_______\ \_______\ \_______\|\_______\ \_______\ $(NC)"
	@echo "$(GREEN)    \|_______|\|_______|\|_______|\|_______|\|_______| $(NC)"
	@echo ""

	@echo "$(CYAN)--- Mandatory Controls ------|$(NC)"
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

bonus: $(OBJ_BONUS) $(LIB)
	$(CC) $(OBJ_BONUS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME_BONUS) $(LIB)
	@echo "$(GREEN)✅ $(NAME_BONUS) built successfully! You can now run ./$(NAME_BONUS) <map_file>.cub$(NC)"

%.o: %.c
	@$(CC) -Wall -Wextra -Werror -g -I/usr/include -Imlx_linux -O3 -c $< -o $@
	@echo "$(YELLOW)Compiling: $< $(NC)" # Added echo for compilation step

clean :
	@echo "$(WHITE)✔️ --Cleaning libft objects$(NC)"
	@$(MAKE) clean -s -C libft/
	@echo "$(WHITE)✔️ --Cleaning project objects$(NC)"
	@rm -f $(OBJ) $(OBJ_BONUS) # Remove both sets of object files

fclean : clean
	@echo "$(WHITE)✔️ --Cleaning libft library$(NC)"
	@$(MAKE) fclean -s -C libft/
	@echo "$(WHITE)✔️ --Cleaning project executables $(NAME) & $(NAME_BONUS)$(NC)"
	@rm -f $(NAME) $(NAME_BONUS) # Remove both executables
	@echo "$(RED)✔️ --Full clean complete$(NC)"

re : fclean all

re_bonus : fclean bonus

.PHONY: all clean fclean re bonus re_bonus

.SECONDARY: $(OBJ) $(OBJ_BONUS)