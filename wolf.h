#ifndef WOLF3D_H
# define WOLF3D_H

# include "minilibx_macos/mlx.h"
# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

// # define PUT_STRING(fd, s) (write(fd, s, sizeof(s) - 1))

# define LEFT 123
# define RIGHT 124
# define BACKWARDS 125
# define FORWARD 126

typedef	struct		s_color
{
	int		num;
	int		r;
	int		g;
	int		b;
}					t_color;

typedef	struct		s_env
{
	void	*window;
	void	*img;
	char	*data;
	void	*mlx;
	int		bpp;
	int		size_line;
	int		endian;
	int		r;
	int		g;
	int		b;
	int		win_x;
	int		win_y;
	int		i;
	int		pos;
	double	pos_of_player_x;
	double	pos_of_player_y;
	double	dir_of_player_x;
	double	dir_of_player_y;
	double	cam_plane_of_player_x;
	double	cam_plane_of_player_y;
	double	camera_x;
	int		x;
	int		y;
	int		w;
	int		h;
	double	ray_pos_x;
	double	ray_pos_y;
	double	ray_of_dir_x;
	double	ray_of_dir_y;
	int		coo_of_squar_map_x;
	int		coo_of_squar_map_y;
	double	side_dist_ab_x;
	double	side_dist_ab_y;
	double	delta_dist_plus_one_x;
	double	delta_dist_plus_one_y;
	double	perp_wall_dist_lenght_of_ray;
	int		one_step_x;
	int		one_step_y;
	int		hit_wall;
	int		y_or_x_side_of_wall_hit;
	int		wall_line_height;
	int		wall_draw_start;
	int		wall_draw_end;
	double		move_speed;
	double		rot_speed;
	t_color	color;
}					t_env;


// typedef	struct		s_cal
// {

// }					t_cal;

# define W 640
# define H 480
# define mapWidth 24
# define mapHeight 24

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

#endif