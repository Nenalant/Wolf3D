/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_key_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanteri <alanteri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 17:44:06 by alanteri          #+#    #+#             */
/*   Updated: 2017/12/04 18:55:53 by alanteri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	turn(t_env *e, double var, double var2)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = e->player_dirx;
	e->player_dirx = e->player_dirx * cos(var)
	- e->player_diry * sin(var);
	e->player_diry = old_dir_x * sin(var)
	+ e->player_diry * cos(var);
	old_plane_x = e->player_cam_x;
	e->player_cam_x = e->player_cam_x * cos(var)
	- e->player_cam_y * sin(var);
	e->player_cam_y = old_plane_x * sin(var)
	+ e->player_cam_y * cos(var2);
}

void	walk_forward(t_env *e)
{
	if (e->worldmap[(int)(e->player_posx + e->player_dirx
		* (e->move_speed))][(int)e->player_posy] == 0)
		e->player_posx += e->player_dirx * e->move_speed;
	if (e->worldmap[(int)e->player_posx]
		[(int)(e->player_posy + e->player_diry * (e->move_speed))] == 0)
		e->player_posy += e->player_diry * e->move_speed;
}

void	left_and_right(int key, t_env *e)
{
	if (key == LEFT)
	{
		turn(e, e->rot_speed, e->rot_speed);
		e->etoile.data += 20;
	}
	else if (key == Q)
	{
		turn(e, 1.5, 1.5);
		walk_forward(e);
		turn(e, -1.5, 1.5);
		e->etoile.data += 20;
	}
	else if (key == RIGHT)
	{
		turn(e, -e->rot_speed, e->rot_speed);
		e->etoile.data -= 20;
	}
	else if (key == D)
	{
		turn(e, -1.5, 1.5);
		walk_forward(e);
		turn(e, 1.5, 1.5);
		e->etoile.data -= 20;
	}
}

void	backwards_and_forwards(int key, t_env *e)
{
	if (key == BACKWARDS || key == S)
	{
		if (e->worldmap[(int)(e->player_posx - e->player_dirx
			* (e->move_speed))][(int)e->player_posy] == 0)
			e->player_posx -= e->player_dirx * e->move_speed;
		if (e->worldmap[(int)e->player_posx]
			[(int)(e->player_posy - e->player_diry * (e->move_speed))] == 0)
			e->player_posy -= e->player_diry * e->move_speed;
	}
	else if (key == FORWARD || key == Z)
		walk_forward(e);
}

int		key_hook(int key, t_env *e)
{
	if (key == 53)
		clean(e);
	if ((key >= 123 && key <= 126) || (key >= 0 && key <= 2)
		|| (key == 13) || (key == 6) || (key == 46))
	{
		if (key == LEFT || key == RIGHT || key == Q || key == D)
			left_and_right(key, e);
		if (key == BACKWARDS || key == FORWARD || key == S || key == Z)
			backwards_and_forwards(key, e);
		if (key == CHANGE_MAP)
			map_generator(e);
		gameloop(e);
	}
	if (key == WEAPON)
		game_with_weapon(e);
	if (key == 7)
		mlx_string_put(e->mlx, e->win, W / 2, H / 2, 0xFF0000, "PIOU !");
	return (0);
}
