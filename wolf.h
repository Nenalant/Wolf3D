#ifndef WOLF3D_H
# define WOLF3D_H

# include "minilibx_macos/mlx.h"
# include <unistd.h>
# include <stdlib.h>

# define WIDTH 800
# define HEIGHT 800
# define PUT_STRING(fd, s) (write(fd, s, sizeof(s) - 1))

typedef	struct		s_win
{
	void	*win;
	void	*img;
	void	*data;
	void	*mlx;
	int		bpp;
	int		size_line;
	int		endian;
	int		win_x;
	int		win_y;
}					t_win;

void	init_mlx_var(t_win *e);
void	init_mlx(t_win *e);
int		put_img_to_win(t_win *e);

#endif