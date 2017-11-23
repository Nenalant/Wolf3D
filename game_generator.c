#include "wolf.h"

void	init_raycast(t_env *e)
{
	e->camera_x = 2 * e->x / (double)(W) - 1;
	e->ray_pos_x = e->player_posx;
	e->ray_pos_y = e->player_posy;
	e->ray_of_dir_x = e->player_dirx + e->player_cam_x * e->camera_x;
	e->ray_of_dir_y = e->player_diry + e->player_cam_y * e->camera_x;
	e->coo_map_x = (int)e->ray_pos_x;
	e->coo_map_y = (int)e->ray_pos_y;
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
		e->side_dist_ab_x = (e->ray_pos_x - e->coo_map_x)
		* e->delta_dist_plus_one_x;
	}
	else
	{
		e->one_step_x = 1;
		e->side_dist_ab_x = (e->coo_map_x + 1.0 - e->ray_pos_x)
		* e->delta_dist_plus_one_x;
	}
	if (e->ray_of_dir_y < 0)
	{
		e->one_step_y = -1;
		e->side_dist_ab_y = (e->ray_pos_y - e->coo_map_y)
		* e->delta_dist_plus_one_y;
	}
	else
	{
		e->one_step_y = 1;
		e->side_dist_ab_y = (e->coo_map_y + 1.0 - e->ray_pos_y)
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
			e->coo_map_x += e->one_step_x;
			e->ns_ew_side = 0;
		}
		else
		{
			e->side_dist_ab_y += e->delta_dist_plus_one_y;
			e->coo_map_y += e->one_step_y;
			e->ns_ew_side = 1;
		}
		if (e->worldMap[e->coo_map_x][e->coo_map_y] > 0)
			e->hit_wall = 1;
	}
}

void	calcul_wall_dist_and_height(t_env *e)
{
	if (e->ns_ew_side == 0)
		e->perp_wall_dist_lenght_of_ray = fabs((e->coo_map_x - e->ray_pos_x
			+ (1 - e->one_step_x) / 2) / e->ray_of_dir_x);
	else
		e->perp_wall_dist_lenght_of_ray = fabs((e->coo_map_y - e->ray_pos_y
			+ (1 - e->one_step_y) / 2) / e->ray_of_dir_y);

	e->wall_line_height = abs((int)(H / e->perp_wall_dist_lenght_of_ray));
	e->wall_draw_start = -(e->wall_line_height) / 2 + H / 2;
	if (e->wall_draw_start < 0)
		e->wall_draw_start = 0;
	e->wall_draw_end = e->wall_line_height / 2 + H / 2;
	if (e->wall_draw_end >= H)
		e->wall_draw_end = H - 1;

	if (e->ns_ew_side == 0 && e->ray_of_dir_x > 0)
		set_color(e, 51, 255, 51); //menth green
	else if (e->ns_ew_side == 0 && e->ray_of_dir_x < 0)
		set_color(e, 225, 102, 225); //clear pink
	else if (e->ns_ew_side == 1 && e->ray_of_dir_y > 0)
		set_color(e, 0, 204, 255); //clear blue
	else if (e->ns_ew_side == 1 && e->ray_of_dir_y < 0)
		set_color(e, 153, 0, 204); //lila
}
