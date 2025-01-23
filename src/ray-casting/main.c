/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:44:29 by iouhssei          #+#    #+#             */
/*   Updated: 2025/01/23 11:36:20 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

void	init_cube(t_cube *cube, t_data *data)
{
	if (cube->gc)
		return ;
	cube->mlx = NULL;
	cube->mlx_window = NULL;
	data->img = NULL;
	data->addr = NULL;
	data->bits_per_pixel = 0;
	data->endian = 0;
	data->line_length = 0;
	cube->p_x = 250;
	cube->p_y= 250;
	cube->angle = 0;
}
int	main(void)
{
	t_cube	*cube;
	t_data	*data;

	cube = (t_cube *)malloc(sizeof(t_cube));
	if (!cube)
	{
		perror("malloc");
		return (-1);
	}
	cube->gc = init_garbage_collector();
	if (!cube->gc)
	{
		free(cube);
		return (-1);
	}
	data = tracked_malloc(cube->gc, sizeof(t_data));
	if (data == NULL)
	{
		free_all(cube->gc);
		return (1);
	}
	cube->data = data;
	init_cube(cube, data);
	init_mlx(cube, data);
	free_all(cube->gc);
	return (0);
}
