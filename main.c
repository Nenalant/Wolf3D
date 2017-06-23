
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

int		key_hook(int keycode, t_cal *c)
{
	printf("key = %d\n", keycode);
	if (keycode == 53)
		exit(0);
	else if (keycode == 126) //forward
	{
		if (!(worldMap[(int)c->pos_of_player_x + (int)c->dir_of_player_x]
			[(int)c->pos_of_player_y]))
			c->pos_of_player_x += c->dir_of_player_x;
		if (!(worldMap[(int)c->pos_of_player_x]
			[(int)c->pos_of_player_y  + (int)c->dir_of_player_y]))
			c->pos_of_player_y += c->dir_of_player_y;
	}
	else if (keycode == 125) //backwards
	{
		if (!(worldMap[(int)c->pos_of_player_x - (int)c->dir_of_player_x]
			[(int)c->pos_of_player_y]))
			c->pos_of_player_x -= c->dir_of_player_x;
		if (!(worldMap[(int)c->pos_of_player_x]
			[(int)c->pos_of_player_y  - (int)c->dir_of_player_y]))
			c->pos_of_player_y -= c->dir_of_player_y;
	}
	else if (keycode == 124) //RIGHT
	{
		double	old_dir_x;
		double	old_plane_x;

		old_dir_x = c->dir_of_player_x;
		c->dir_of_player_x = c->dir_of_player_x * cos(-6.0)
			- c->dir_of_player_y* sin(-6.0);
		old_plane_x = c->cam_plane_of_player_x;
		c->cam_plane_of_player_x = c->cam_plane_of_player_x * cos(-6.0)
			- c->cam_plane_of_player_y * sin(-6.0);
		c->cam_plane_of_player_y = old_plane_x * sin(-6.0)
			+ c->cam_plane_of_player_y * cos(6.0);
	}
	else if (keycode == 123) //LEFT
	{
		double	old_dir_x;
		double	old_plane_x;

		old_dir_x = c->dir_of_player_x;
		c->dir_of_player_x = c->dir_of_player_x * cos(6.0)
			- c->dir_of_player_y * sin(6.0);
		c->dir_of_player_y = old_dir_x * sin(6.0)
			+ c->dir_of_player_y * cos(6.0);
		old_plane_x = c->cam_plane_of_player_x;
		c->cam_plane_of_player_x = c->cam_plane_of_player_x * cos(6.0)
			- c->cam_plane_of_player_y * sin(6.0);
		c->cam_plane_of_player_y = old_plane_x * sin(6.0)
			+ c->cam_plane_of_player_y * cos(6.0);
	}
	return (0);
}

int		put_img_to_win(t_win *e)
{
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	return (0);
}


void	put_image(t_win *e, int x, int y)
{
	if (x <= 0 || x >= e->win_y || y <= 0 || y >= e->win_x)
		return ;
	*(e->data + y * e->size_line + e->bpp / 8 * x) = e->b;
	*(e->data + y * e->size_line + e->bpp / 8 * x + 1) = e->g;
	*(e->data + y * e->size_line + e->bpp / 8 * x + 2) = e->r;
}

void	direction(t_cal *c)
{
	if (c->ray_of_dir_x < 0)
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
	if (c->ray_of_dir_y < 0)
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

void	dda_start(t_cal *c)
{
	while(c->hit_wall == 0)
	{
		if (c->side_dist_ab_x < c->side_dist_ab_y)
		{
			c->side_dist_ab_x += c->delta_dist_plus_one_x;
			c->coo_of_squar_map_x += c->one_step_x;
			c->y_or_x_side_of_wall_hit = 0;
		}
		else
		{
			c->side_dist_ab_y += c->delta_dist_plus_one_y;
			c->coo_of_squar_map_y += c->one_step_y;
			c->y_or_x_side_of_wall_hit = 1;
		}
		if (worldMap[c->x][c->y] > 0)
			c->hit_wall = 1;
	}
}

void	calcul_of_dist_to_wall(t_cal *c)
{
	if (c->y_or_x_side_of_wall_hit == 0)
		c->perp_wall_dist_lenght_of_ray = (c->coo_of_squar_map_x - c->ray_pos_x
			+ (1 - c->one_step_x) / 2) / c->ray_of_dir_x;
	else
		c->perp_wall_dist_lenght_of_ray = (c->coo_of_squar_map_y - c->ray_pos_y
			+ (1 - c->one_step_y) / 2) / c->ray_of_dir_y;
}

void	calcul_of_wall_height(t_cal *c)
{
	c->wall_line_height = (int)(c->h / c->perp_wall_dist_lenght_of_ray);
	c->wall_draw_start = -(c->wall_line_height) / 2 + c->h / 2;
	if (c->wall_draw_start < 0)
		c->wall_draw_start = 0;
	c->wall_draw_end = c->wall_line_height / 2 + c->h / 2;
	if (c->wall_draw_end >= c->h)
		c->wall_draw_end = c->h - 1;
}

void	colors(t_cal *c)
{
	if (c->color.num == 0) //black
	{
		c->color.r = 0x00;
		c->color.g = 0x00;
		c->color.b = 0x00;
	}
	else if (c->color.num == 1) //blue
	{
		c->color.r = 0x00;
		c->color.g = 0x00;
		c->color.b = 0xFF;
	}
	else if (c->color.num == 2) //green
	{
		c->color.r = 0x00;
		c->color.g = 0xFF;
		c->color.b = 0x00;
	}
	else if (c->color.num == 3) //yellow
	{
		c->color.r = 0xFF;
		c->color.g = 0xFF;
		c->color.b = 0x00;
	}
	else if (c->color.num == 4) //cyan
	{
		c->color.r = 0x00;
		c->color.g = 0xFF;
		c->color.b = 0xFF;
	}
	else if (c->color.num == 5) //magenta
	{
		c->color.r = 0xFF;
		c->color.g = 0x00;
		c->color.b = 0xFF;
	}
}

void	set_wall_color(t_cal *c)
{
	colors(c);
	// if (c->y_or_x_side_of_wall_hit == 1)
	// 	c->color. = c->color / 2;
}

void	gameloop(t_cal *c)
{
	while (c->x < c->w)
	{
		c->camera_x = 2 * c->x / (double)(c->w) - 1;
		c->ray_pos_x = c->pos_of_player_x;
		c->ray_pos_y = c->pos_of_player_y;
		c->ray_of_dir_x = c->dir_of_player_x + c->cam_plane_of_player_x * c->camera_x;
		c->ray_of_dir_y = c->dir_of_player_y + c->cam_plane_of_player_y * c->camera_x;

		c->coo_of_squar_map_x = (int)c->ray_pos_x;
		c->coo_of_squar_map_y = (int)c->ray_pos_y;

		c->delta_dist_plus_one_x = sqrt(1 + (c->ray_of_dir_y * c->ray_of_dir_y)
			/ (c->ray_of_dir_x * c->ray_of_dir_x));
		c->delta_dist_plus_one_y = sqrt(1 + (c->ray_of_dir_x * c->ray_of_dir_x)
			/ (c->ray_of_dir_y * c->ray_of_dir_y));
		c->hit_wall = 0;
		direction(c);
		dda_start(c);
		calcul_of_dist_to_wall(c);
		calcul_of_wall_height(c);
		set_wall_color(c);
		c->x++;
	}
}

void	draw(t_win *e, t_cal *c)
{
	e->r = 0xFF;
	e->g = 0x66;
	e->b = 0xFF;
	c->x = 0;
	while (c->x < e->win_x)
	{
		c->y = 0;
		while (c->y < e->win_y)
		{
			c->color.num = worldMap[c->x][c->y];
			gameloop(c);
			put_image(e, c->x, c->y);
			c->y++;
		}
		c->x++;
	}
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
	c.w = e.win_x;
	c.h = e.win_y;

	init_mlx_var(&c);
	if (!(e.mlx = mlx_init()))
		ft_put_error();
	if (!(e.win = mlx_new_window(e.mlx, e.win_x, e.win_y, "WOLF3D")))
		ft_put_error();
	e.img = mlx_new_image(e.mlx, e.win_x, e.win_y);
	e.data = mlx_get_data_addr(e.img, &e.bpp, &e.size_line, &e.endian);
	mlx_hook(e.win, 2, 3, key_hook, &c);
	mlx_hook(e.win, 17, 0, red_cross, &e);
	// gameloop(&c, &e);
	// draw(&e, &c);
	put_img_to_win(&e);
	mlx_expose_hook(e.win, put_img_to_win, &e);
	mlx_loop(e.mlx);
	return (0);
}
