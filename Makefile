NAME = wolf3d

SRC =	main.c \

CC = gcc

FLAGS = -Wall -Wextra -Werror

LIBFT = libft/libft.a

MLX = minilibx_macos/libmlx.a

MLX_FLAGS = -framework OpenGL -framework AppKit

all : $(LIB_MLX) $(NAME)

$(NAME) :
	$(CC) $(FLAGS) $(MLX_FLAGS) $(MLX) $(SRC) $(LIBFT) -o $(NAME)

$(LIB_MLX) :
	make -C libft/
	make -C minilibx_macos/

clean :
	make -C libft/ clean
	make -C minilibx_macos/ clean

fclean : clean
	make -C libft/ fclean
	rm -rf $(NAME)

re : fclean all