#ifndef WOLF3D_H
# define WOLF3D_H

# include <mlx.h>
# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# define HEIGHT 800
# define WIDTH 600
// # define PUT_STRING(fd, s) (write(fd, s, sizeof(s) - 1))

typedef	struct		s_win
{
	void	*win;
	void	*img;
	char	*data;
	void	*mlx;
	int		bpp;
	int		size_line;
	int		endian;
	int		r;
	int		g;
	int		b;
	// int		win_x;
	// int		win_y;
}					t_win;

// typedef	struct		s_cal
// {
// 	double posX;
// 	double posY;
// 	double dirX;
// 	double dirY;
// 	double camX;
// 	double camY;

// 	double time;
// 	double oldtime;
// }

// void	init_mlx_var(t_win *e);
// void	init_mlx(t_win *e);
// int		put_img_to_win(t_win *e);

#endif