/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanteri <alanteri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 17:32:57 by alanteri          #+#    #+#             */
/*   Updated: 2017/12/04 18:56:11 by alanteri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include "minilibx_macos/mlx.h"
# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <pthread.h>

# define texW 64
# define texH 64
# define MAPSIZE 24
# define W 800
# define H 600
# define LEFT 123
# define RIGHT 124
# define BACKWARDS 125
# define FORWARD 126
# define WEAPON 6
# define Z 13
# define S 1
# define Q 0
# define D 2

typedef	struct			s_color
{
	int					num;
	int					r;
	int					g;
	int					b;
}						t_color;

typedef	struct			s_gun
{
	void				*img;
	char				*data;
	int					bpp;
	int					size_line;
	int					endian;
}						t_gun;

typedef	struct			s_wall
{
	void				*img;
	char				*data;
	int					bpp;
	int					size_line;
	int					endian;
}						t_wall;

typedef	struct			s_mossy_r
{
	void				*img;
	char				*data;
	int					bpp;
	int					size_line;
	int					endian;
}						t_mossy_r;

typedef	struct			s_mossy_y
{
	void				*img;
	char				*data;
	int					bpp;
	int					size_line;
	int					endian;
}						t_mossy_y;

typedef	struct			s_mossy_g
{
	void				*img;
	char				*data;
	int					bpp;
	int					size_line;
	int					endian;
}						t_mossy_g;

typedef	struct			s_mossy_w
{
	void				*img;
	char				*data;
	int					bpp;
	int					size_line;
	int					endian;
}						t_mossy_w;

typedef	struct			s_etoile
{
	void				*img;
	char				*data;
	int					bpp;
	int					size_line;
	int					endian;
}						t_etoile;

typedef	struct			s_env
{
	void				*win;
	void				*img;
	char				*data;
	void				*mlx;
	int					bpp;
	int					size_line;
	int					endian;
	int					worldmap[MAPSIZE][MAPSIZE];
	int					r;
	int					g;
	int					b;
	int					win_x;
	int					win_y;
	int					i;
	int					pos;
	double				player_posx;
	double				player_posy;
	double				player_dirx;
	double				player_diry;
	double				player_cam_x;
	double				player_cam_y;
	double				camera_x;
	int					x;
	int					max_x;
	int					y;
	int					w;
	int					h;
	double				ray_pos_x;
	double				ray_pos_y;
	double				ray_of_dir_x;
	double				ray_of_dir_y;
	int					coo_map_x;
	int					coo_map_y;
	double				side_dist_ab_x;
	double				side_dist_ab_y;
	double				delta_dist_plus_one_x;
	double				delta_dist_plus_one_y;
	double				perp_wall_dist_lenght_of_ray;
	int					one_step_x;
	int					one_step_y;
	int					hit_wall;
	int					ns_ew_side;
	int					wall_line_height;
	int					wall_draw_start;
	int					wall_draw_end;
	double				move_speed;
	double				rot_speed;
	char				**wall_color;
	// int					mossy;
	t_color				color;

	struct s_gun		gun;
	int					s_weight;
	int					s_height;

	struct s_wall		wall;
	int					s_weigh;
	int					s_heigh;

	struct s_etoile		etoile;
	int					s_wei;
	int					s_hei;

	struct s_mossy_r	mossy_r;
	struct s_mossy_y	mossy_y;
	struct s_mossy_g	mossy_g;
	struct s_mossy_w	mossy_w;


}						t_env;

void					clean(t_env *e);
void					ft_put_error(void);
int						red_cross(t_env *e);

void					init_raycast(t_env *e);
void					direction(t_env *e);
void					dda_start(t_env *e);
void					calcul_wall_dist_and_height(t_env *e);

void					game_with_weapon(t_env *e);
void					gameloop(t_env *e);

void					left_and_right(int key, t_env *e);
void					or_right(int key, t_env *e);
void					backwards_and_forwards(int key, t_env *e);
int						add_weapon(t_env *e);
int						key_hook(int key, t_env *e);

void					init_wall_tab(t_env *e);
void					set_color(t_env *e, int r, int g, int b);
void					put_textures(t_env *e);
void					put_weapon(t_env *e);
void					init_wall(t_env *e);
void					init_weapon(t_env *e);
void					init_sky(t_env *e);
void					init_mossy_r(t_env *e);
void					init_mossy_y(t_env *e);
void					init_mossy_g(t_env *e);
void					init_mossy_w(t_env *e);

void					init_var(t_env *e);
void					map_generator(t_env *e);
void					init_mlx(t_env *e);

#endif
