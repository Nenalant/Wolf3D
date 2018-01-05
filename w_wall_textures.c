/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanteri <alanteri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 18:10:11 by alanteri          #+#    #+#             */
/*   Updated: 2018/01/04 18:10:15 by alanteri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

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
