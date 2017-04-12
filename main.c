#include "wolf.h"

void	init_mlx_var(t_win *e)
{
	e->win_x = WIDTH;
	e->win_y = HEIGHT;
}

void	init_mlx(t_win *e)
{
	if ((e->mlx = mlx_init()) == NULL)
	{
		PUT_STRING(2, "error environement");
		exit(0);
	}
	e->win = mlx_new_window(e->mlx, e->win_x, e->win_y, "WOLF3D")
	// e->img = mlx_new_image(e->mlx, e->win_x, e->win_y);
	// e->data = mlx_get_data_addr(e->img.img, &e->img.bpp, &e->img.size_line, &e->img.endian);
}

// int		put_img_to_win(t_win *e)
// {
// 	mlx_put_image_to_window(e->mlx, e->img.win, e->img.img, 0, 0);
// 	return (0);
// }

int		main(int ac, char **av)
{
	t_win	e;

	(void)ac;
	(void)av;
	// double posX;
	// double posY;
	// double dirX;
	// double dirY;
	// double camX;
	// double camY;

	// double time;
	// double oldtime;

	// posX = 0;
	// posY = 0;
	// dirX = -1;
	// dirY = 0;
	// camX = 0;
	// camY = 0.66;
	// time = 0;
	// oldtime = 0;
	init_mlx_var(&e);
	init_mlx(&e);
	// put_img_to_win(&e);
	return (0);
}