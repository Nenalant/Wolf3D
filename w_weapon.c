/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_weapon.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanteri <alanteri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 18:25:07 by alanteri          #+#    #+#             */
/*   Updated: 2018/01/04 18:25:17 by alanteri         ###   ########.fr       */
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

void	put_weapon(t_env *e)
{
	static int	j;
	static int	pos_i;
	static int	pos_gun;

	e->w_i = -1;
	while (e->w_i++ < e->s_height)
	{
		j = -1;
		while (j++ < e->s_weight)
		{
			pos_i = 4 * (W - e->s_weight + j) + e->size_line
			* (H - e->s_height + e->w_i);
			pos_gun = 4 * j + e->gun.size_line * e->w_i;
			if (e->data[pos_gun] != 0 && e->data[pos_gun + 1]
				!= 0 && e->data[pos_gun + 2] != 0)
			{
				if (e->gun.data[pos_gun + 2] != 0)
				{
					e->data[pos_i + 2] = e->gun.data[pos_gun + 2];
					e->data[pos_i + 1] = e->gun.data[pos_gun + 1];
					e->data[pos_i] = e->gun.data[pos_gun];
				}
			}
		}
	}
}
