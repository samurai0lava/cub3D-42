/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:44:52 by iouhssei          #+#    #+#             */
/*   Updated: 2025/01/21 14:19:47 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_rectangle(t_data *data, int x, int y, int size, int color)
{
	int i;
	int j;
	
	i = x;
	while (i < x + size)
	{
		j = y;
		while (j < y + size)
		{
			if (i >= 0 && i < S_RES && j >= 0 && j < S_RES)
			{
				my_mlx_pixel_put(data, i, j, color);
			}
			j++;
		}
		i++;
	}
}

void	draw_map(t_data *data, int map[10][10])
{
	int	x;
	int	y;

	x = 0;
	while (x < 10)
	{
		y = 0;
		while (y < 10)
		{
			my_mlx_pixel_put(data, x, y, 0x00000000);
			y++;
		}
		x++;
	}
	y = 0;
	while (y < 10)
	{
		x = 0;
		while (x < 10)
		{
			if (map[y][x] != 0)
				draw_rectangle(data, x * 50, y * 50, 50, 0x00FFFFFF);
			else
				draw_rectangle(data, x * 50, y * 50, 50, 0x00333333);
			x++;
		}
		y++;
	}
}

void	init_mlx(t_cube *cube, t_data *data)
{
	int	example_map[10][10] = 
							{{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 
							 {1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
							 {1, 0, 3, 3, 1, 1, 1, 0, 1, 1},
							 {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
							 {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
							 {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
							 {1, 1, 4, 0, 2, 2, 1, 1, 4, 1},
							 {1, 1, 1, 0, 0, 0, 0, 0, 0, 1},
							 {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
							 {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

	cube->mlx = mlx_init();
	if (cube->mlx == NULL)
	{
		print_error(RED "mlx_init failed\n" RESET);
		free_all(cube->gc);
		return ;
	}
	cube->mlx_window = mlx_new_window(cube->mlx, S_RES, S_RES, "Cub3D");
	if (cube->mlx_window == NULL)
	{
		print_error(RED "mlx_window failed\n" RESET);
		return ;
	}
	data->img = mlx_new_image(cube->mlx, S_RES, S_RES);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	cube->data = data;
	cube->p_x = 250;
	cube->p_y = 250;
	cube->angle = 0;
	ft_memcpy(cube->map, example_map, sizeof(example_map));
	draw_map(data, cube->map);
	cast_away(cube); //the raycster 3D effect
	draw_filled_circle(cube, cube->p_x, cube->p_y, 10, 0x0000FFFF); //the minimap
	mlx_put_image_to_window(cube->mlx, cube->mlx_window, data->img, 0, 0);
	mlx_hook(cube->mlx_window, 2, 1L << 0, handle_keypress, cube);
	mlx_loop(cube->mlx);
}

int	handle_keypress(int keycode, t_cube *cube)
{
	int		movement_speed;
	int		new_x;
	int		new_y;
	int		map_x;
	int		map_y;
	double	rotation_speed;

	movement_speed = 5;
	rotation_speed = 0.1;
	new_x = cube->p_x;
	new_y = cube->p_y;
	if (keycode == ESC)
	{
		if (cube->data && cube->data->img)
			mlx_destroy_image(cube->mlx, cube->data->img);
		mlx_destroy_window(cube->mlx, cube->mlx_window);
		free_all(cube->gc);
		free(cube);
		exit(0);
	}
	else if (keycode == W_KEY)
	{
		new_x += cos(cube->angle) * movement_speed;
		new_y += sin(cube->angle) * movement_speed;
	}
	else if (keycode == S_KEY)
	{
		new_x -= cos(cube->angle) * movement_speed;
		new_y -= sin(cube->angle) * movement_speed;
	}
	else if (keycode == D_KEY)
	{
		new_x += cos(cube->angle + M_PI_2) * movement_speed;
		new_y += sin(cube->angle + M_PI_2) * movement_speed;
	}
	else if (keycode == A_KEY)
	{
		new_x += cos(cube->angle - M_PI_2) * movement_speed;
		new_y += sin(cube->angle - M_PI_2) * movement_speed;
	}
	else if (keycode == LEFT_KEY)
	{
		cube->angle -= rotation_speed;
	}
	else if (keycode == RIGHT_KEY)
	{
		cube->angle += rotation_speed;
	}
	cube->angle = fmod(cube->angle + 2 * PI, 2 * PI);
	map_x = new_x / 50;
	map_y = new_y / 50;
	if (map_x >= 0 && map_x < 10 && map_y >= 0 && map_y < 10
		&& cube->map[map_y][map_x] == 0)
	{
		cube->p_x = new_x;
		cube->p_y = new_y;
	}
	draw_map(cube->data, cube->map);
	cast_away(cube); //the raycster 3D effect
	draw_filled_circle(cube, cube->p_x, cube->p_y, 10, 0x0000FFFF); //the minimap
	mlx_put_image_to_window(cube->mlx, cube->mlx_window, cube->data->img, 0, 0);
	return (1);
}
