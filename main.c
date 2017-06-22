
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

void	direction(t_cal *e)
{
	if (ray_of_dir_x < 0)
	{
		c->one_step_x = -1;
		c->side_dist_ab_x = (c->ray_pos_x - c->coo_of_squar_map_x)
		* c->delta_dist_plus_one_x;
	}
	else
	{
		c->one_step_x = 1;
		c->side_dist_ab_x = (c->coo_of_squar_map_x + 1.0 - c->ray_pos_x)
		* c->delta_dist_plus_one_x;
	}
	if (ray_of_dir_y < 0)
	{
		c->one_step_y = -1;
		c->side_dist_ab_y = (c->ray_pos_y - c->coo_of_squar_map_y)
		* c->delta_dist_plus_one_y;
	}
	else
	{
		c->one_step_y = 1;
		c->side_dist_ab_y = (c->coo_of_squar_map_y + 1.0 - c->ray_pos_y)
		* c->delta_dist_plus_one_y;
	}
}

void	dda_start(t_cal *e)
{
	while(c->hit == 0)
	{
		if (c->side_dist_ab_x < c->side_dist_ab_y)
		{
			c->side_dist_ab_x += c->delta_dist_plus_one_x;
			c->coo_of_squar_map_x += c->one_step_x;
			c->side = 0;
		}
		else
		{
			c->side_dist_ab_y += c->delta_dist_plus_one_y;
			c->coo_of_squar_map_y +=one_step_y;
			c->side = 1;
		}
		if (worldMap[mapWidth][mapHeight] > 0)
			c->hit = 1;
	}
}

void	gameloop(t_cal *c, t_win *e)
{
	c->x = 0;
	
	while (c->x < c->w)
	{
		c->camera_x = 2 * c->x / double(c->w) - 1;
		c->ray_pos_x = pos_of_player_x;
		c->ray_pos_y = pos_of_player_y;
		c->ray_of_dir_x = dir_of_player_x + cam_plane_of_player_x * camera_x;
		c->ray_of_dir_y = dir_of_player_y + cam_plane_of_player_y * camera_x;

		coo_of_squar_map_x = int(ray_pos_x);
		coo_of_squar_map_y = int(ray_pos_y);

		c->delta_dist_plus_one_x = sqrt(1 + (ray_of_dir_y * ray_of_dir_y)
			/ (ray_of_dir_x * ray_of_dir_x));
		c->delta_dist_plus_one_y = sqrt(1 + (ray_of_dir_x * ray_of_dir_x)
			/ (ray_of_dir_y * ray_of_dir_y));
		c->hit = 0;
		direction(&e);
		dda_start(&e);
		c->x++;
	}
	draw(&e);
}

void	init_mlx_var(t_cal *c)
{
	c->pos_of_player_x = 0;
	c->pos_of_player_y = 0;
	c->dir_of_player_x = -1;
	c->dir_of_player_y = 0;
	c->cam_plane_of_player_x = 0;
	c->cam_plane_of_player_y = 0.66;
}

int		main(void)
{
	t_win	e;
	t_cal	c;

	e.win_x = 800;
	e.win_y = 600;
	c.w = e->win_x;

	init_mlx_var(&c);
	if (!(e.mlx = mlx_init()))
		ft_put_error();
	if (!(e.win = mlx_new_window(e.mlx, e.win_x, e.win_y, "WOLF3D")))
		ft_put_error();
	e.img = mlx_new_image(e.mlx, e.win_x, e.win_y);
	e.data = mlx_get_data_addr(e.img, &e.bpp, &e.size_line, &e.endian);
	mlx_hook(e.win, 2, 3, key_hook, &e);
	mlx_hook(e.win, 17, 0, red_cross, &e);
	gameloop(&c &e);
	put_img_to_win(&e);
	mlx_expose_hook(e.win, put_img_to_win, &e);
	mlx_loop(e.mlx);
	return (0);
}
