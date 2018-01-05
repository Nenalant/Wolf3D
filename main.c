/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanteri <alanteri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 17:15:41 by alanteri          #+#    #+#             */
/*   Updated: 2017/12/04 18:09:48 by alanteri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	init_var(t_env *e)
{
	e->pos = 0;
	e->i = 0;
	e->player_posx = 22;
	e->player_posy = 20;
	e->player_dirx = -1;
	e->player_diry = 0;
	e->player_cam_x = 0;
	e->player_cam_y = 0.66;
	e->move_speed = 0.4;
	e->rot_speed = 0.08;
}

void	init_mlx(t_env *e)
{
	if (!(e->mlx = mlx_init()))
		ft_put_error();
	if (!(e->win = mlx_new_window(e->mlx, W, H, "WOLF3D")))
		ft_put_error();
	e->img = mlx_new_image(e->mlx, W, H);
	e->data = mlx_get_data_addr(e->img, &e->bpp, &e->size_line, &e->endian);
}

void	init_textures(t_env *e)
{
	init_weapon(e);
	init_sky(e);
	init_wall(e);
	init_mossy_r(e);
	init_mossy_y(e);
	init_mossy_g(e);
	init_mossy_w(e);
}

int		main(int ac, char **av)
{
	t_env	e;

	(void)av;
	if (ac == 1)
	{
		map_generator(&e);
		init_var(&e);
		init_mlx(&e);
		init_textures(&e);
		gameloop(&e);
		mlx_hook(e.win, 2, 3, key_hook, &e);
		mlx_hook(e.win, 17, 0, red_cross, &e);
		mlx_string_put(e.mlx, e.win, W / 3, H / 3, 0x00FF00,
			"PRESS AN ARROW KEY TO START");
		mlx_string_put(e.mlx, e.win, W / 16, H / 20, 0xFF0000, "Welcome !");
		mlx_loop(e.mlx);
	}
	else
		ft_putendl_fd("\033[31mERROR\033[0m\nUsage: ./wolf3d", 2);
	return (0);
}
