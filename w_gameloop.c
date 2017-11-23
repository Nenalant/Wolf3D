#include "wolf.h"

void	gameloop(t_env *e)
{	
	mlx_clear_window(e->mlx, e->win);
	e->x = 0;

	while (e->x < W)
	{
		init_raycast(e);
		direction(e);
		dda_start(e);
		calcul_wall_dist_and_height(e);
		put_textures(e);
		e->x++;
	}
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
}

void	game_with_weapon(t_env *e)
{	
	mlx_clear_window(e->mlx, e->win);
	e->x = 0;

	while (e->x < W)
	{
		put_weapon(e);
		init_raycast(e);
		direction(e);
		dda_start(e);
		calcul_wall_dist_and_height(e);
		put_textures(e);
		e->x++;
	}
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
}