

NAME = wolf3d
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3
LFLAGS = -framework OpenGL -framework AppKit
MLX = minilibx_macos/libmlx.a
LIBFT = libft/libft.a
OBJ = $(SRC:.c=.o)
SRC =	main.c \
		w_map_generator.c \
		w_gameloop.c \
		w_game_generator.c \
		w_textures.c \
		w_key_hook.c \
		w_errors.c

all : $(NAME)

wolf3d : $(LIBFT) $(MLX) $(OBJ)
	@echo ""
	@$(CC) -o $@ $^ $(LFLAGS)
	@echo "\x1b[32;01mWOLF3D SUCCESSFULLY CREATED !\x1b[32;00m"

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)
	@echo "\x1b[32;01m.\x1b[32;00m\c"

$(LIBFT) :
	@make -C libft/
	@make -C minilibx_macos/
	@echo "\033[32mLibrairies compilated\033[0m"

$(MLX) :
	@make -C minilibx_macos/

.PHONY : all clean fclean re

clean :
	@rm -rf *.o
	@make -C libft/ clean
	@make -C minilibx_macos/ clean
	@echo "\033[32mObjects deleted\nLibraries cleaned\033[0m"

fclean : clean
	@make -C libft/ fclean
	@rm -rf $(NAME)
	@echo "\033[32m$(NAME) deleted\033[0m"

re : fclean all