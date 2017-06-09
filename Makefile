NAME = wolf3d

SRC = main.c

CC = gcc

CFLAGS = -Wall -Wextra -Werror

LFLAGS = -framework OpenGL -framework AppKit

MLX = minilibx_macos/libmlx.a

LIBFT = libft/libft.a

OBJ = $(SRC:.c=.o)

all : $(NAME)

wolf3d : $(LIBFT) $(MLX) $(OBJ) 
	$(CC) -o $@ $^ $(LFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

$(LIBFT) :
	@make -C libft/

$(MLX) :
	@make -C minilibx_macos/

.PHONY : clean fclean

clean :
	@rm -rf *.o
	@make -C libft/ clean
	@make -C minilibx_macos/ clean

fclean : clean
	@make -C libft/ fclean
	@rm -rf $(NAME)

re : fclean all