/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_errors.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanteri <alanteri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 17:03:32 by alanteri          #+#    #+#             */
/*   Updated: 2017/12/04 17:45:38 by alanteri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	clean(t_env *e)
{
	mlx_destroy_image(e->mlx, e->img);
	mlx_clear_window(e->mlx, e->win);
	mlx_destroy_window(e->mlx, e->win);
	ft_putstr("\033[31mGAME OVER\n\033[0m");
	exit(0);
}

void	ft_put_error(void)
{
	ft_putstr("error environement");
	exit(0);
}

int		red_cross(t_env *e)
{
	clean(e);
	return (0);
}
