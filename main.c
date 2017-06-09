
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
	if (x <= 0 || x >= HEIGHT || y <= 0 || y >= WIDTH)
		return ;
	*(e->data + x * e->size_line + e->bpp / 8 * y) = e->b;
	*(e->data + x * e->size_line + e->bpp / 8 * y + 1) = e->g;
	*(e->data + x * e->size_line + e->bpp / 8 * y + 2) = e->r;
}

void	draw(t_win *e)
{
	int		y;
	int		x;

	e->r = 0xFF;
	e->g = 0x66;
	e->b = 0xFF;
	x = 0;
	while (x < HEIGHT)
	{
		y = 0;
		while (y < WIDTH)
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

	if (!(e.mlx = mlx_init()))
		ft_put_error();
	if (!(e.win = mlx_new_window(e.mlx, HEIGHT, WIDTH, "WOLF3D")))
		ft_put_error();
	e.img = mlx_new_image(e.mlx, HEIGHT, WIDTH);
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
// 	posX = 0;
// 	posY = 0;
// 	dirX = -1;
// 	dirY = 0;
// 	camX = 0;
// 	camY = 0.66;
// 	time = 0;
// 	oldtime = 0;
// }