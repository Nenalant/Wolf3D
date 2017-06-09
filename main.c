
#include "wolf.h"

void	ft_put_error(void)
{
	ft_putstr("error environement");
	exit(0) ;
}

int		red_cross(t_win *e)
{
	(void)e;
	exit(0) ;
	return (0);
}

int		key_hook(int keycode, t_win *e)
{
	(void)e;
	printf("key = %d\n", keycode);
	if (keycode == 53)
		exit(0) ;
	return (0);
}

int		put_img_to_win(t_win *e)
{
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	return (0);
}

int		main(void)
{
	t_win	e;

	if (!(e.mlx = mlx_init()))
		ft_put_error();
	if (!(e.win = mlx_new_window(e.mlx, 800, 800, "WOLF3D")))
		ft_put_error();
	e.img = mlx_new_image(e.mlx, 800, 800);
	e.data = mlx_get_data_addr(e.img, &e.bpp, &e.size_line, &e.endian);
	mlx_hook(e.win, 2, 3, key_hook, &e);
	mlx_hook(e.win, 17, 0, red_cross, &e);
	put_img_to_win(&e);
	mlx_expose_hook(e.win, put_img_to_win, &e);
	mlx_loop(e.mlx);
	return (0);
}

// #include "wolf.h"

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

// int		put_img_to_win(t_win *e)
// {
// 	mlx_put_image_to_window(e->mlx_ptr, e->win_ptr, e->img_ptr, 0, 0);
// 	return (0);
// }

// void	init_mlx(t_win *e)
// {
// 	e->win_ptr_x = WIDTH;
// 	e->win_ptr_y = HEIGHT;
// 	if ((e->mlx_ptr = mlx_init()) == NULL)
// 	{
// 		PUT_STRING(2, "error environement");
// 		exit(0);
// 	}
// 	e->win_ptr = mlx_new_window(e->mlx_ptr, e->win_ptr_x, e->win_ptr_y, "WOLF3D");
// 	e->img_ptr = mlx_new_image(e->mlx_ptr, e->win_ptr_x, e->win_ptr_y);
// 	e->data = mlx_get_data_addr(e->img_ptr, &e->bpp, &e->size_line, &e->endian);
// }

// int		main(int ac, char **av)
// {
// 	t_win	e;

// 	(void)ac;
// 	(void)av;
// 	init_mlx_var(&e);
// 	init_mlx(&e);
// 	// put_img_to_win(&e);
// 	return (0);
// }