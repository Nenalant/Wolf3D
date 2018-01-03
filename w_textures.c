/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_textures.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanteri <alanteri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 17:45:19 by alanteri          #+#    #+#             */
/*   Updated: 2017/12/04 19:49:59 by alanteri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	init_weapon(t_env *e)
{
	char	*sniper;

	if (!(sniper = "pics/sniper.xpm"))
		perror("weapon img error");
	e->img = mlx_new_image(e->mlx, W, H);
	e->data = mlx_get_data_addr(e->img, &e->bpp, &e->size_line, &e->endian);
	e->gun.img = mlx_xpm_file_to_image(e->mlx, sniper, &e->s_weight,
		&e->s_height);
	e->gun.data = mlx_get_data_addr(e->gun.img, &e->gun.bpp,
		&e->gun.size_line, &e->gun.endian);
}

void	init_wall(t_env *e)
{
	char	*wall;

	if (!(wall = "pics/wall.xpm"))
		perror("wall img error");
	e->img = mlx_new_image(e->mlx, W, H);
	e->data = mlx_get_data_addr(e->img, &e->bpp, &e->size_line, &e->endian);
	e->wall.img = mlx_xpm_file_to_image(e->mlx, wall, &e->s_weigh,
		&e->s_heigh);
	e->wall.data = mlx_get_data_addr(e->wall.img, &e->wall.bpp,
		&e->wall.size_line, &e->wall.endian);
}

void	init_mossy_r(t_env *e)
{
	char	*mossy_r;

	if (!(mossy_r = "pics/mossy_r.xpm"))
		perror("mossy_r img error");
	e->img = mlx_new_image(e->mlx, W, H);
	e->data = mlx_get_data_addr(e->img, &e->bpp, &e->size_line, &e->endian);
	e->mossy_r.img = mlx_xpm_file_to_image(e->mlx, mossy_r, &e->s_weigh,
		&e->s_heigh);
	e->mossy_r.data = mlx_get_data_addr(e->mossy_r.img, &e->mossy_r.bpp,
		&e->mossy_r.size_line, &e->mossy_r.endian);
}

void	init_mossy_y(t_env *e)
{
	char	*mossy_y;

	if (!(mossy_y = "pics/mossy_y.xpm"))
		perror("mossy_y img error");
	e->img = mlx_new_image(e->mlx, W, H);
	e->data = mlx_get_data_addr(e->img, &e->bpp, &e->size_line, &e->endian);
	e->mossy_y.img = mlx_xpm_file_to_image(e->mlx, mossy_y, &e->s_weigh,
		&e->s_heigh);
	e->mossy_y.data = mlx_get_data_addr(e->mossy_y.img, &e->mossy_y.bpp,
		&e->mossy_y.size_line, &e->mossy_y.endian);
}

void	init_mossy_g(t_env *e)
{
	char	*mossy_g;

	if (!(mossy_g = "pics/mossy_g.xpm"))
		perror("mossy_g img error");
	e->img = mlx_new_image(e->mlx, W, H);
	e->data = mlx_get_data_addr(e->img, &e->bpp, &e->size_line, &e->endian);
	e->mossy_g.img = mlx_xpm_file_to_image(e->mlx, mossy_g, &e->s_weigh,
		&e->s_heigh);
	e->mossy_g.data = mlx_get_data_addr(e->mossy_g.img, &e->mossy_g.bpp,
		&e->mossy_g.size_line, &e->mossy_g.endian);
}

void	init_mossy_w(t_env *e)
{
	char	*mossy_w;

	if (!(mossy_w = "pics/wall.xpm"))
		perror("mossy_w img error");
	e->img = mlx_new_image(e->mlx, W, H);
	e->data = mlx_get_data_addr(e->img, &e->bpp, &e->size_line, &e->endian);
	e->mossy_w.img = mlx_xpm_file_to_image(e->mlx, mossy_w, &e->s_weigh,
		&e->s_heigh);
	e->mossy_w.data = mlx_get_data_addr(e->mossy_w.img, &e->mossy_w.bpp,
		&e->mossy_w.size_line, &e->mossy_w.endian);
}

void	init_sky(t_env *e)
{
	char	*etoile;

	if (!(etoile = "pics/etoile.xpm"))
		perror("sky img error");
	e->img = mlx_new_image(e->mlx, W, H);
	e->data = mlx_get_data_addr(e->img, &e->bpp, &e->size_line, &e->endian);
	e->etoile.img = mlx_xpm_file_to_image(e->mlx, etoile, &e->s_wei, &e->s_hei);
	e->etoile.data = mlx_get_data_addr(e->etoile.img, &e->etoile.bpp,
		&e->etoile.size_line, &e->etoile.endian);
}

void	set_color(t_env *e, int r, int g, int b)
{
	e->color.r = r;
	e->color.g = g;
	e->color.b = b;
}

void	put_textures(t_env *e)
{
	int		pos_wall;
	int		pos_sky;
	int		tex_x;
	int		d;
	int		tex_y;
	double	wall_x;

	e->i = -1;
	if (e->worldmap[e->coo_map_x][e->coo_map_y] == 1)
	{
		if (e->ns_ew_side == 0)
			wall_x = e->ray_pos_y + e->perp_wall_dist_lenght_of_ray * e->ray_of_dir_y;
		else
			wall_x = e->ray_pos_x + e->perp_wall_dist_lenght_of_ray * e->ray_of_dir_x;
		wall_x -= floor((wall_x));
		tex_x = (int)(wall_x * (double)texW);
		if (e->ns_ew_side == 0 && e->ray_of_dir_x > 0)
			tex_x = texW - tex_x - 1;
		if (e->ns_ew_side == 1 && e->ray_of_dir_y < 0)
			tex_x = texW - tex_x - 1;
	}
	while (e->i++ < H)
	{
		e->pos = (e->i * e->size_line) + e->x * (e->bpp / 8);
		pos_sky = (e->i * e->etoile.size_line) + e->x * (e->etoile.bpp / 8);
		if (e->i < e->wall_draw_start)
		{
			e->data[e->pos + 2] = e->etoile.data[pos_sky + 2];
			e->data[e->pos + 1] = e->etoile.data[pos_sky + 1];
			e->data[e->pos] = e->etoile.data[pos_sky];
		}
		if (e->i >= e->wall_draw_start && e->i < e->wall_draw_end)
		{
			d = e->i * 256 - H * 128 + e->wall_line_height * 128;
			tex_y = ((d * texH) / e->wall_line_height) / 256;
			pos_wall = tex_y * e->wall.size_line + (e->wall.bpp / 8) * tex_x;
			e->data[e->pos + 2] = e->wall.data[pos_wall + 2];
			e->data[e->pos + 1] = e->wall.data[pos_wall + 1];
			e->data[e->pos] = e->wall.data[pos_wall];
		}
		else if (e->i > e->wall_draw_end && e->i < H)
		{
			set_color(e, 0, 0, 102);
			e->data[e->pos + 2] = e->color.r;
			e->data[e->pos + 1] = e->color.g;
			e->data[e->pos] = e->color.b;
		}
	}
}

void	put_weapon(t_env *e)
{
	static int	i;
	static int	j;
	static int	pos_i;
	static int	pos_gun;

	i = 0;
	while (i < e->s_height)
	{
		j = 0;
		while (j < e->s_weight)
		{
			pos_i = 4 * (W - e->s_weight + j) + e->size_line
			* (H - e->s_height + i);
			pos_gun = 4 * j + e->gun.size_line * i;
			if (e->data[pos_gun] != 0 && e->data[pos_gun + 1]
				!= 0 && e->data[pos_gun + 2] != 0)
			{
				if (e->gun.data[pos_gun + 2] != 0) {
					e->data[pos_i + 2] = e->gun.data[pos_gun + 2];
					e->data[pos_i + 1] = e->gun.data[pos_gun + 1];
					e->data[pos_i] = e->gun.data[pos_gun];
				}
			}
			j++;
		}
		i++;
	}
}
