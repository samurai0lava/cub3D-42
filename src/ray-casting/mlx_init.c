#include "../../inc/cube3d.h"

void	init_mlx(t_cube *cube)
{
	cube->mlx = mlx_init();
	if (cube->mlx == NULL)
	{
		print_error(RED "mlx_init failed\n" RESET);
		return ;		
	}
	cube->mlx_window = mlx_new_window(cube->mlx, 1000, 1000, "Cub3D");
	if (cube->mlx_window == NULL)
	{
		print_error(RED "mlx_window failed\n" RESET);
		return ;
	}
	mlx_loop(cube->mlx);
}
