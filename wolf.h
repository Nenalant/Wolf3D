#ifndef WOLF3D_H
# define WOLF3D_H

# include <mlx.h>
# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

// # define PUT_STRING(fd, s) (write(fd, s, sizeof(s) - 1))
# define w 800
# define h 600
# define UP 126
# define DOWN 125
# define RIGHT 124
# define LEFT 123

typedef	struct		s_win
{
	void	*win;
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
}					t_win;

// typedef	struct		s_color
// {
	
// }					t_color;

typedef	struct		s_cal
{
	double	pos_of_player_x;
	double	pos_of_player_y;
	double	dir_of_player_x;
	double	dir_of_player_y;
	double	cam_plane_of_player_x;
	double	cam_plane_of_player_y;
	double	camera_x;
	int		x;
	int		y;
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
	// t_color	*color;
	int		color_num;
	int		r;
	int		g;
	int		b;
}					t_cal;

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