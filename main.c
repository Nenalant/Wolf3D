
#include "wolf.h"

void	ft_put_error(void)
{
	ft_putstr("error environement");
	exit(0);
}

int		red_cross(t_win *e)
{
	(void)e;
	exit(0);
	return (0);
}

int		key_hook(int keycode, t_win *e)
{
	(void)e;
	printf("key = %d\n", keycode);
	if (keycode == 53)
		exit(0);
	return (0);
}

int		put_img_to_win(t_win *e)
{
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	return (0);
}


void	put_image(t_win *e, int x, int y)
{
	if (x <= 0 || x >= e->win_x || y <= 0 || y >= e->win_y)
		return ;
	*(e->data + y * e->size_line + e->bpp / 8 * x) = e->b;
	*(e->data + y * e->size_line + e->bpp / 8 * x + 1) = e->g;
	*(e->data + y * e->size_line + e->bpp / 8 * x + 2) = e->r;
}

void	draw(t_win *e)
{
	int		y;
	int		x;

	e->r = 0xFF;
	e->g = 0x66;
	e->b = 0xFF;
	x = 0;
	while (x < e->win_x)
	{
		y = 0;
		while (y < e->win_y)
		{
			put_image(e, x, y);
			y++;
		}
		x++;
	}
}

int		main(void)
{
	t_win	e;

	e.win_x = 800;
	e.win_y = 600;

	if (!(e.mlx = mlx_init()))
		ft_put_error();
	if (!(e.win = mlx_new_window(e.mlx, e.win_x, e.win_y, "WOLF3D")))
		ft_put_error();
	e.img = mlx_new_image(e.mlx, e.win_x, e.win_y);
	e.data = mlx_get_data_addr(e.img, &e.bpp, &e.size_line, &e.endian);
	mlx_hook(e.win, 2, 3, key_hook, &e);
	mlx_hook(e.win, 17, 0, red_cross, &e);
	draw(&e);
	put_img_to_win(&e);
	mlx_expose_hook(e.win, put_img_to_win, &e);
	mlx_loop(e.mlx);
	return (0);
}

// void	init_mlx_var(t_win *e)
// {
	pos_of_player_x = 0;
	pos_of_player_y = 0;
	dir_of_player_x = -1;
	dir_of_player_y = 0;
	cam_plane_of_player_x = 0;
	cam_plane_of_player_y = 0.66;
// 	time = 0;
// 	oldtime = 0;
// }