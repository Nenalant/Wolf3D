
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

void	put_calc_in(t_cal *c, t_win *e)
{
	int		i;
	int		j;

	i = 0;
	j = 255;
	e->i = 0;
	while (e->i < H)
	{
	printf("enter aff\n");
		e->pos = (e->i * e->size_line) + c->x * (e->bpp / 8);
		if (e->i >= c->wall_draw_start && e->i <= c->wall_draw_end)
		{
			printf("1\n");
			e->data[e->pos + 2] = (c->color.r + i > 255) ? (char)255 : c->color.r + i;
			e->data[e->pos + 1] = (c->color.g + i > 255) ? (char)255 : c->color.g + i;
			e->data[e->pos] = (c->color.b + i > 255) ? (char)255 : c->color.b + i;
			i++;
		}
		else
		{
			printf("2\n");
			e->data[e->pos + 2] = 0;
			printf("2-1\n");
			e->data[e->pos + 1] = 0;
			e->data[e->pos] = 99;
		}
		printf("3\n");
		e->i++;
	}
}

// void	put_image(t_win *e, int x, int y)
// {
// 	if (x <= 0 || x >= H || y <= 0 || y >= W)
// 		return ;
// 	*(e->data + y * e->size_line + e->bpp / 8 * x) = e->b;
// 	*(e->data + y * e->size_line + e->bpp / 8 * x + 1) = e->g;
// 	*(e->data + y * e->size_line + e->bpp / 8 * x + 2) = e->r;
// }

void	init_raycast(t_cal *c)
{
	c->camera_x = 2 * c->x / (double)(W) - 1;
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
	while (c->hit_wall == 0)
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
		if (worldMap[c->coo_of_squar_map_x][c->coo_of_squar_map_y] > 0)
			c->hit_wall = 1;
	}
}

void	set_wall_color(t_cal *c, int r, int g, int b)
{
	c->color.r = r;
	c->color.g = g;
	c->color.b = b;
}

void	calcul_of_dist_to_wall_and_wall_height(t_cal *c)
{
	if (c->y_or_x_side_of_wall_hit == 0)
		c->perp_wall_dist_lenght_of_ray = (c->coo_of_squar_map_x - c->ray_pos_x
			+ (1 - c->one_step_x) / 2) / c->ray_of_dir_x;
	else
		c->perp_wall_dist_lenght_of_ray = (c->coo_of_squar_map_y - c->ray_pos_y
			+ (1 - c->one_step_y) / 2) / c->ray_of_dir_y;

	c->wall_line_height = (int)(H / c->perp_wall_dist_lenght_of_ray);
	c->wall_draw_start = -(c->wall_line_height) / 2 + H / 2;
	if (c->wall_draw_start < 0)
		c->wall_draw_start = 0;
	c->wall_draw_end = c->wall_line_height / 2 + H / 2;
	if (c->wall_draw_end >= H)
		c->wall_draw_end = H - 1;

	if (c->y_or_x_side_of_wall_hit == 0 && c->ray_of_dir_x > 0)
		set_wall_color(c, 255, 255, 102); //razer green
	else if (c->y_or_x_side_of_wall_hit == 0 && c->ray_of_dir_x < 0)
		set_wall_color(c, 153, 0, 255); //purple
	else if (c->y_or_x_side_of_wall_hit == 1 && c->ray_of_dir_x > 0)
		set_wall_color(c, 102, 255, 255); //baby yellow
	else
		set_wall_color(c, 0, 255, 0); //baby blue
}

void	gameloop(t_cal *c, t_win *e)
{	
	c->x = -1;
	mlx_clear_window(e->mlx, e->window);

	while (c->x++ < W)
	{
		init_raycast(c);
		direction(c);
		dda_start(c);
		calcul_of_dist_to_wall_and_wall_height(c);
		put_calc_in(c, e);
	}
	mlx_put_image_to_window(e->mlx, e->window, e->img, 0, 0);
}

int		key_hook(int key, t_cal *c, t_win *e)
{
	printf("key = %d\n", key);
	if (key == 53)
		exit(0);
	if (key >= 123 && key <= 126)
	{
		if (key == LEFT)
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
		else if (key == RIGHT)
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
		else if (key == BACKWARDS)
		{
			if (!(worldMap[(int)c->pos_of_player_x - (int)c->dir_of_player_x]
				[(int)c->pos_of_player_y]))
				c->pos_of_player_x -= c->dir_of_player_x;
			if (!(worldMap[(int)c->pos_of_player_x]
				[(int)c->pos_of_player_y  - (int)c->dir_of_player_y]))
				c->pos_of_player_y -= c->dir_of_player_y;
		}
		else if (key == FORWARD)
		{
			if (!(worldMap[(int)c->pos_of_player_x + (int)c->dir_of_player_x]
				[(int)c->pos_of_player_y]))
				c->pos_of_player_x += c->dir_of_player_x;
			if (!(worldMap[(int)c->pos_of_player_x]
				[(int)c->pos_of_player_y  + (int)c->dir_of_player_y]))
				c->pos_of_player_y += c->dir_of_player_y;
		}
		gameloop(c, e);
	}
	return (0);
}

void	init_var(t_cal *c, t_win *e)
{
	e->pos = 0;
	e->i = 0;
	c->pos_of_player_x = 22.0;
	c->pos_of_player_y = 11.5;
	c->dir_of_player_x = -1.0;
	c->dir_of_player_y = 0.0;
	c->cam_plane_of_player_x = 0.0;
	c->cam_plane_of_player_y = 0.66;
}

void	init_mlx(t_win *e)
{
	if (!(e->mlx = mlx_init()))
		ft_put_error();
	if (!(e->window = mlx_new_window(e->mlx, W, H, "WOLF3D")))
		ft_put_error();
	e->img = mlx_new_image(e->mlx, W, H);
	e->data = mlx_get_data_addr(e->img, &e->bpp, &e->size_line, &e->endian);
	mlx_hook(e->window, 17, 0, red_cross, &e);
}

int			expose_hook(t_win *e)
{
	mlx_put_image_to_window(e->mlx, e->window, e->img, 0, 0);
	return (0);
}

int		main(void)
{
	t_win	e;
	t_cal	c;

	init_var(&c, &e);
	init_mlx(&e);
	gameloop(&c, &e);
	mlx_expose_hook(e.window, expose_hook, &e);
	mlx_hook(e.window, 2, 3, key_hook, &c);
	mlx_loop(e.mlx);
	return (0);
}
