
#include "wolf.h"

void	ft_put_error(void)
{
	ft_putstr("error environement");
	exit(0);
}

int		red_cross(t_env *e)
{
	(void)e;
	exit(0);
	return (0);
}

void	put_calc_in(t_env *e)
{
	e->i = 0;
	while (e->i < H)
	{
		e->pos = (e->i * e->size_line) + e->x * (e->bpp / 8);
		if (e->i >= e->wall_draw_start && e->i <= e->wall_draw_end)
		{
			e->data[e->pos + 2] = e->color.r;//(e->color.r + i > 255) ? (char)255 : e->color.r + i;
			e->data[e->pos + 1] = e->color.g;//(e->color.g + i > 255) ? (char)255 : e->color.g + i;
			e->data[e->pos] = e->color.b;//(e->color.b + i > 255) ? (char)255 : e->color.b + i;
			// i++;
		}
		else
		{
			e->data[e->pos + 2] = 0;
			e->data[e->pos + 1] = 0;
			e->data[e->pos] = 99;
		}
		e->i++;
	}
}

void	init_raycast(t_env *e)
{
	e->camera_x = 2 * e->x / (double)(W) - 1;
	e->ray_pos_x = e->pos_of_player_x;
	e->ray_pos_y = e->pos_of_player_y;
	e->ray_of_dir_x = e->dir_of_player_x + e->cam_plane_of_player_x * e->camera_x;
	e->ray_of_dir_y = e->dir_of_player_y + e->cam_plane_of_player_y * e->camera_x;
	e->coo_of_squar_map_x = (int)e->ray_pos_x;
	e->coo_of_squar_map_y = (int)e->ray_pos_y;
	e->delta_dist_plus_one_x = sqrt(1 + (e->ray_of_dir_y * e->ray_of_dir_y)
		/ (e->ray_of_dir_x * e->ray_of_dir_x));
	e->delta_dist_plus_one_y = sqrt(1 + (e->ray_of_dir_x * e->ray_of_dir_x)
		/ (e->ray_of_dir_y * e->ray_of_dir_y));
	e->hit_wall = 0;
}

void	direction(t_env *e)
{
	if (e->ray_of_dir_x < 0)
	{
		e->one_step_x = -1;
		e->side_dist_ab_x = (e->ray_pos_x - e->coo_of_squar_map_x)
		* e->delta_dist_plus_one_x;
	}
	else
	{
		e->one_step_x = 1;
		e->side_dist_ab_x = (e->coo_of_squar_map_x + 1.0 - e->ray_pos_x)
		* e->delta_dist_plus_one_x;
	}
	if (e->ray_of_dir_y < 0)
	{
		e->one_step_y = -1;
		e->side_dist_ab_y = (e->ray_pos_y - e->coo_of_squar_map_y)
		* e->delta_dist_plus_one_y;
	}
	else
	{
		e->one_step_y = 1;
		e->side_dist_ab_y = (e->coo_of_squar_map_y + 1.0 - e->ray_pos_y)
		* e->delta_dist_plus_one_y;
	}
}

void	dda_start(t_env *e)
{
	while (e->hit_wall == 0)
	{
		if (e->side_dist_ab_x < e->side_dist_ab_y)
		{
			e->side_dist_ab_x += e->delta_dist_plus_one_x;
			e->coo_of_squar_map_x += e->one_step_x;
			e->y_or_x_side_of_wall_hit = 0;
		}
		else
		{
			e->side_dist_ab_y += e->delta_dist_plus_one_y;
			e->coo_of_squar_map_y += e->one_step_y;
			e->y_or_x_side_of_wall_hit = 1;
		}
		if (worldMap[e->coo_of_squar_map_x][e->coo_of_squar_map_y] > 0)
			e->hit_wall = 1;
	}
}

void	set_wall_color(t_env *e, int r, int g, int b)
{
	e->color.r = r;
	e->color.g = g;
	e->color.b = b;
}

void	calcul_of_dist_to_wall_and_wall_height(t_env *e)
{
	if (e->y_or_x_side_of_wall_hit == 0)
		e->perp_wall_dist_lenght_of_ray = (e->coo_of_squar_map_x - e->ray_pos_x
			+ (1 - e->one_step_x) / 2) / e->ray_of_dir_x;
	else
		e->perp_wall_dist_lenght_of_ray = (e->coo_of_squar_map_y - e->ray_pos_y
			+ (1 - e->one_step_y) / 2) / e->ray_of_dir_y;

	e->wall_line_height = (int)(H / e->perp_wall_dist_lenght_of_ray);
	e->wall_draw_start = -(e->wall_line_height) / 2 + H / 2;
	if (e->wall_draw_start < 0)
		e->wall_draw_start = 0;
	e->wall_draw_end = e->wall_line_height / 2 + H / 2;
	if (e->wall_draw_end >= H)
		e->wall_draw_end = H - 1;

	if (e->y_or_x_side_of_wall_hit == 0 && e->ray_of_dir_x > 0)
		set_wall_color(e, 255, 255, 102); //razer green
	else if (e->y_or_x_side_of_wall_hit == 0 && e->ray_of_dir_x < 0)
		set_wall_color(e, 153, 0, 255); //purple
	else if (e->y_or_x_side_of_wall_hit == 1 && e->ray_of_dir_x > 0)
		set_wall_color(e, 102, 255, 255); //baby yellow
	else
		set_wall_color(e, 0, 255, 0); //baby blue
}

void	gameloop(t_env *e)
{	
	mlx_clear_window(e->mlx, e->window);
	e->x = 0;
	while (e->x < W)
	{
		init_raycast(e);
		direction(e);
		dda_start(e);
		calcul_of_dist_to_wall_and_wall_height(e);
		put_calc_in(e);
		e->x++;
	}
	mlx_put_image_to_window(e->mlx, e->window, e->img, 0, 0);
}

int		key_hook(int key, t_env *e)
{
	// printf("key = %d\n", key);
	if (key == 53)
		exit(0);
	if (key >= 123 && key <= 126)
	{
		if (key == LEFT)
		{
			double	old_dir_x;
			double	old_plane_x;

			old_dir_x = e->dir_of_player_x;

			e->dir_of_player_x = e->dir_of_player_x * cos(e->rot_speed) - e->dir_of_player_y * sin(e->rot_speed);
			e->dir_of_player_y = old_dir_x * sin(e->rot_speed) + e->dir_of_player_y * cos(e->rot_speed);
			old_plane_x = e->cam_plane_of_player_x;
			e->cam_plane_of_player_x = e->cam_plane_of_player_x * cos(e->rot_speed) - e->cam_plane_of_player_y * sin(e->rot_speed);
			e->cam_plane_of_player_y = old_plane_x * sin(e->rot_speed) + e->cam_plane_of_player_y * cos(e->rot_speed);
		}
		else if (key == RIGHT)
		{
			double	old_dir_x;
			double	old_plane_x;

			old_dir_x = e->dir_of_player_x;

			e->dir_of_player_x = e->dir_of_player_x * cos(-e->rot_speed) - e->dir_of_player_y* sin(-e->rot_speed);
			e->dir_of_player_y = old_dir_x * sin(-e->rot_speed) + e->dir_of_player_y * cos(-e->rot_speed);
			old_plane_x = e->cam_plane_of_player_x;
			e->cam_plane_of_player_x = e->cam_plane_of_player_x * cos(-e->rot_speed) - e->cam_plane_of_player_y * sin(-e->rot_speed);
			e->cam_plane_of_player_y = old_plane_x * sin(-e->rot_speed) + e->cam_plane_of_player_y * cos(e->rot_speed);
		}
		else if (key == BACKWARDS)
		{
			if (worldMap[(int)e->pos_of_player_x - (int)e->dir_of_player_x]
				[(int)e->pos_of_player_y] == 0)
				e->pos_of_player_x -= e->dir_of_player_x * e->move_speed;
			if (worldMap[(int)e->pos_of_player_x]
				[(int)e->pos_of_player_y  - (int)e->dir_of_player_y] == 0)
				e->pos_of_player_y -= e->dir_of_player_y * e->move_speed;
		}
		else if (key == FORWARD)
		{
			if (worldMap[(int)e->pos_of_player_x + (int)e->dir_of_player_x]
				[(int)e->pos_of_player_y] == 0)
				e->pos_of_player_x += e->dir_of_player_x * e->move_speed;
			if (worldMap[(int)e->pos_of_player_x]
				[(int)e->pos_of_player_y  + (int)e->dir_of_player_y] == 0)
				e->pos_of_player_y += e->dir_of_player_y * e->move_speed;
		}
		gameloop(e);
	}
	return (0);
}

void	init_var(t_env *e)
{
	e->pos = 0;
	e->i = 0;
	e->pos_of_player_x = 22;
	e->pos_of_player_y = 12;
	e->dir_of_player_x = -1;
	e->dir_of_player_y = 0;
	e->cam_plane_of_player_x = 0;
	e->cam_plane_of_player_y = 0.66;
	e->move_speed = 0.3;
	e->rot_speed = 0.06;
}

void	init_mlx(t_env *e)
{
	if (!(e->mlx = mlx_init()))
		ft_put_error();
	if (!(e->window = mlx_new_window(e->mlx, W, H, "WOLF3D")))
		ft_put_error();
	e->img = mlx_new_image(e->mlx, W, H);
	e->data = mlx_get_data_addr(e->img, &e->bpp, &e->size_line, &e->endian);
}

int			expose_hook(t_env *e)
{
	mlx_put_image_to_window(e->mlx, e->window, e->img, 0, 0);
	return (0);
}

int		main(void)
{
	t_env	e;

	init_var(&e);
	init_mlx(&e);
	gameloop(&e);
	mlx_expose_hook(e.window, expose_hook, &e);
	mlx_hook(e.window, 2, 3, key_hook, &e);
	// mlx_hook(e.window, 17, 0, red_cross, &e);
	// mlx_string_put(e.mlx, e.window, W/2, H/2, 255, "START");
	mlx_loop(e.mlx);
	return (0);
}
