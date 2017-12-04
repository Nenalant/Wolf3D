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

void	left_and_right(int key, t_env *e)
{
	double	old_dir_x;
	double	old_plane_x;

	if (key == LEFT || key == Q)
	{
		old_dir_x = e->player_dirx;
		e->player_dirx = e->player_dirx * cos(e->rot_speed)
		- e->player_diry * sin(e->rot_speed);
		e->player_diry = old_dir_x * sin(e->rot_speed)
		+ e->player_diry * cos(e->rot_speed);
		old_plane_x = e->player_cam_x;
		e->player_cam_x = e->player_cam_x * cos(e->rot_speed)
		- e->player_cam_y * sin(e->rot_speed);
		e->player_cam_y = old_plane_x * sin(e->rot_speed)
		+ e->player_cam_y * cos(e->rot_speed);
	}
	or_right(key, e);
}

void	or_right(int key, t_env *e)
{
	double	old_dir_x;
	double	old_plane_x;

	if (key == RIGHT || key == D)
	{
		old_dir_x = e->player_dirx;
		e->player_dirx = e->player_dirx * cos(-e->rot_speed)
		- e->player_diry * sin(-e->rot_speed);
		e->player_diry = old_dir_x * sin(-e->rot_speed)
		+ e->player_diry * cos(-e->rot_speed);
		old_plane_x = e->player_cam_x;
		e->player_cam_x = e->player_cam_x * cos(-e->rot_speed)
		- e->player_cam_y * sin(-e->rot_speed);
		e->player_cam_y = old_plane_x * sin(-e->rot_speed)
		+ e->player_cam_y * cos(e->rot_speed);
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
	{
		if (e->worldmap[(int)(e->player_posx + e->player_dirx
			* (e->move_speed))][(int)e->player_posy] == 0)
			e->player_posx += e->player_dirx * e->move_speed;
		if (e->worldmap[(int)e->player_posx]
			[(int)(e->player_posy + e->player_diry * (e->move_speed))] == 0)
			e->player_posy += e->player_diry * e->move_speed;
	}
}

int		key_hook(int key, t_env *e)
{
	if (key == 53)
		clean(e);
	if ((key >= 123 && key <= 126) || (key >= 0 && key <= 2)
		|| (key == 13) || (key == 6))
	{
		if (key == LEFT || key == RIGHT || key == Q || key == D)
			left_and_right(key, e);
		if (key == BACKWARDS || key == FORWARD || key == S || key == Z)
			backwards_and_forwards(key, e);
		gameloop(e);
	}
	if (key == WEAPON)
		game_with_weapon(e);
	if (key == 7)
		mlx_string_put(e->mlx, e->win, W / 2, H / 2, 0xFF0000, "PIOU !");
	return (0);
}
