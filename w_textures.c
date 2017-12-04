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
	e->sabre.img = mlx_xpm_file_to_image(e->mlx, sniper, &e->s_weight,
		&e->s_height);
	e->sabre.data = mlx_get_data_addr(e->sabre.img, &e->sabre.bpp,
		&e->sabre.size_line, &e->sabre.endian);
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
	e->i = -1;
	while (e->i++ < H)
	{
		e->pos = (e->i * e->size_line) + e->x * (e->bpp / 8);
		if (e->i < e->wall_draw_start)
		{
			e->data[e->pos + 2] = e->etoile.data[e->pos + 2];
			e->data[e->pos + 1] = e->etoile.data[e->pos + 1];
			e->data[e->pos] = e->etoile.data[e->pos];
		}
		if (e->i >= e->wall_draw_start && e->i <= e->wall_draw_end)
		{
			e->data[e->pos + 2] = e->color.r;
			e->data[e->pos + 1] = e->color.g;
			e->data[e->pos] = e->color.b;
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
	static int	pos_sabre;

	i = 0;
	while (i < e->s_height)
	{
		j = 0;
		while (j < e->s_weight)
		{
			pos_i = 4 * (W - e->s_weight + j) + e->size_line
			* (H - e->s_height + i);
			pos_sabre = 4 * j + e->sabre.size_line * i;
			if (e->data[pos_sabre] != 0 && e->data[pos_sabre + 1]
				!= 0 && e->data[pos_sabre + 2] != 0)
			{
				if (e->sabre.data[pos_sabre + 2] != 0) {
					e->data[pos_i + 2] = e->sabre.data[pos_sabre + 2];
					e->data[pos_i + 1] = e->sabre.data[pos_sabre + 1];
					e->data[pos_i] = e->sabre.data[pos_sabre];
				}
			}
			j++;
		}
		i++;
	}
}
