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
