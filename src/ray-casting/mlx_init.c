/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:44:52 by iouhssei          #+#    #+#             */
/*   Updated: 2025/01/11 16:21:32 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x
			* (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	init_mlx(t_cube *cube)
{
	t_data *data;
	cube->mlx = mlx_init();
	
	data = tracked_malloc(cube->gc,sizeof(t_data));
	if(data = NULL)
		return ;
	if (cube->mlx == NULL)
	{
		print_error(RED "mlx_init failed\n" RESET);
		return ;
	}
	cube->mlx_window = mlx_new_window(cube->mlx, 500, 500, "Cub3D");
	if (cube->mlx_window == NULL)
	{
		print_error(RED "mlx_window failed\n" RESET);
		return ;
	}
	data->img = mlx_new_image(cube->mlx, 500, 500);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
	my_mlx_pixel_put(data, 250, 250, 0x00FF0000);
	mlx_put_image_to_window(cube->mlx, cube->mlx_window, data->img, 0,0);
    printf("allo\n");
	mlx_loop(cube->mlx);

}
