/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samurai0lava <samurai0lava@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:44:52 by iouhssei          #+#    #+#             */
/*   Updated: 2025/01/20 15:17:45 by samurai0lav      ###   ########.fr       */
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
	while (x < S_RES)
	{
		y = 0;
		while (y < S_RES)
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
			if (map[y][x] == 1)
				draw_rectangle(data, x * 50, y * 50, 50, 0x00FFFFFF);
			else
				draw_rectangle(data, x * 50, y * 50, 50, 0x00333333);
			x++;
		}
		y++;
	}
}

void	draw_line(t_cube *cube, int x1, int y1, double angle, int length,
		int color)
{
	double	steps;
	int		i;
	int		x2;
	int		y2;

	double dx, dy;
	double x, y;
	double x_inc, y_inc;
	i = 0;
	int map_x, map_y;
	x2 = x1 + cos(angle) * length;
	y2 = y1 + sin(angle) * length;
	dx = x2 - x1;
	dy = y2 - y1;
	steps = fmax(fabs(dx), fabs(dy));
	x_inc = dx / steps;
	y_inc = dy / steps;
	x = x1;
	y = y1;
	while (i <= steps)
	{
		map_x = (int)x / 50;
		map_y = (int)y / 50;
		if (map_x >= 0 && map_x < 10 && map_y >= 0 && map_y < 10)
		{
			if (cube->map[map_y][map_x] == 1)
				break ;
			if (x >= 0 && x < S_RES && y >= 0 && y < S_RES)
				my_mlx_pixel_put(cube->data, (int)x, (int)y, color);
		}
		x += x_inc;
		y += y_inc;
		i++;
	}
}
void	draw_filled_circle(t_cube *cube, int center_x, int center_y, int radius,
		int color)
{
	double	radius_squared;
	int x, y;

	radius_squared = 80;
	draw_map(cube->data, cube->map);
	y = center_y - radius;
	while (y <= center_y + radius)
	{
		x = center_x - radius;
		while (x <= center_x + radius)
		{
			if (((x - center_x) * (x - center_x) + (y - center_y) * (y
						- center_y)) <= radius_squared)
			{
				if (x >= 0 && x < S_RES && y >= 0 && y < S_RES)
				{
					my_mlx_pixel_put(cube->data, x, y, color);
				}
			}
			x++;
		}
		y++;
	}
	cast_away_minirays(cube);
}

void	init_mlx(t_cube *cube, t_data *data)
{
	int	example_map[10][10] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0,
			0, 0, 0, 0, 1}, {1, 0, 1, 1, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0,
			0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0,
			0, 0, 1}, {1, 0, 0, 0, 1, 1, 1, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0,
			0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1,
			1}};

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
	// draw_filled_circle(cube, cube->p_x, cube->p_y, 60, 0x0000FFFF); //the minimap
	cast_away(cube); //the raycster 3D effect
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
		&& cube->map[map_y][map_x] != 1)
	{
		cube->p_x = new_x;
		cube->p_y = new_y;
	}
	draw_map(cube->data, cube->map);
	// draw_filled_circle(cube, cube->p_x, cube->p_y, 60, 0x0000FFFF); //the minimap
	cast_away(cube); //the raycster 3D effect
	mlx_put_image_to_window(cube->mlx, cube->mlx_window, cube->data->img, 0, 0);
	return (1);
}
