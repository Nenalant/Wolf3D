/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_map_generator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanteri <alanteri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 17:13:36 by alanteri          #+#    #+#             */
/*   Updated: 2017/12/04 18:55:34 by alanteri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		map_generator(t_env *e)
{
	int		i;
	int		j;

	j = 0;
	while (j < MAPSIZE)
	{
		i = 0;
		while (i < 25)
		{
			if (i == 0 || i == MAPSIZE - 1 || j == 0 || j == MAPSIZE - 1)
				e->worldmap[j][i] = 1;
			else if (rand() % 12 == 1 && e->player_posx != i &&
					e->player_posy != j)
				e->worldmap[j][i] = 1;
			else
				e->worldmap[j][i] = 0;
			i++;
		}
		j++;
	}
	i = 0;
	j = 0;
}
