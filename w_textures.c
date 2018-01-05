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

void	drawing_wall(t_env *e)
{
	int		pos_wall;

	if (e->worldmap[e->coo_map_x][e->coo_map_y] == 1)
	{
		if (e->ns_ew_side == 0)
			e->wall_x = e->ray_pos_y + e->perp_wall_dist_lenght_of_ray
				* e->ray_of_dir_y;
		else
			e->wall_x = e->ray_pos_x + e->perp_wall_dist_lenght_of_ray
				* e->ray_of_dir_x;
		e->wall_x -= floor((e->wall_x));
		e->tex_x = (int)(e->wall_x * (double)TEXW);
		if (e->ns_ew_side == 0 && e->ray_of_dir_x > 0)
			e->tex_x = TEXW - e->tex_x - 1;
		if (e->ns_ew_side == 1 && e->ray_of_dir_y < 0)
			e->tex_x = TEXW - e->tex_x - 1;
		e->d = e->i * 256 - H * 128 + e->wall_line_height * 128;
		e->tex_y = ((e->d * TEXH) / e->wall_line_height) / 256;
		pos_wall = e->tex_y * e->wall.size_line + (e->wall.bpp / 8)
			* e->tex_x;
		e->data[e->pos + 2] = e->wall.data[pos_wall + 2];
		e->data[e->pos + 1] = e->wall.data[pos_wall + 1];
		e->data[e->pos] = e->wall.data[pos_wall];
	}
}

void	put_textures(t_env *e)
{
	e->i = -1;
	while (e->i++ < H)
	{
		e->pos = (e->i * e->size_line) + e->x * (e->bpp / 8);
		e->pos_sky = (e->i * e->etoile.size_line) + e->x * (e->etoile.bpp / 8);
		if (e->i < e->wall_draw_start)
		{
			e->data[e->pos + 2] = e->etoile.data[e->pos_sky + 2];
			e->data[e->pos + 1] = e->etoile.data[e->pos_sky + 1];
			e->data[e->pos] = e->etoile.data[e->pos_sky];
		}
		if (e->i >= e->wall_draw_start && e->i < e->wall_draw_end)
			drawing_wall(e);
		else if (e->i > e->wall_draw_end && e->i < H)
		{
			set_color(e, 0, 0, 102);
			e->data[e->pos + 2] = e->color.r;
			e->data[e->pos + 1] = e->color.g;
			e->data[e->pos] = e->color.b;
		}
	}
}
