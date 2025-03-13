/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:02:54 by iouhssei          #+#    #+#             */
/*   Updated: 2025/03/13 23:53:44 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

void	init_minimap_params(t_cube *cube)
{
	double	min_dim;

	if (WIDTH < HEIGHT)
		min_dim = WIDTH;
	else
		min_dim = HEIGHT;
	cube->minimap_radius = (int)(min_dim * 0.15);
	cube->minimap_center_x = cube->minimap_radius + 20;
	cube->minimap_center_y = HEIGHT - cube->minimap_radius - 20;
	cube->minimap_scale = 0.3;
	cube->player_dot_size = (int)(cube->minimap_radius * 0.04);
	if (cube->player_dot_size < 2)
		cube->player_dot_size = 2;
}

void	draw_minimap_pixel(t_cube *cube, int local_x, int local_y, int color)
{
	int		screen_x;
	int		screen_y;
	double	dist_from_center;

	screen_x = cube->minimap_center_x + local_x;
	screen_y = cube->minimap_center_y + local_y;
	dist_from_center = sqrt((double)local_x * local_x + (double)local_y
			* local_y);
	if (screen_x >= 0 && screen_x < WIDTH && screen_y >= 0 && screen_y < HEIGHT)
	{
		if (dist_from_center <= cube->minimap_radius)
			my_mlx_pixel_put(cube->data, screen_x, screen_y, color);
	}
}

void	draw_minimap_line(t_cube *cube, double angle, int length, int color)
{
	double	x;
	double	y;
	double	x_inc;
	double	y_inc;
	int		map_x;
	int		map_y;

	x = 0.0;
	y = 0.0;
	x_inc = cos(angle);
	y_inc = sin(angle);
	for (int i = 0; i < length; i++)
	{
		map_x = (int)((cube->p_x + (x / cube->minimap_scale)) / S_TEX);
		map_y = (int)((cube->p_y + (y / cube->minimap_scale)) / S_TEX);
		if (map_x < 0 || map_x >= 30 || map_y < 0 || map_y >= 30)
			break ;
		if (cube->map[map_y][map_x] != 0)
			break ;
		draw_minimap_pixel(cube, (int)x, (int)y, color);
		x += x_inc;
		y += y_inc;
	}
}

void	draw_walls_mini_map(t_cube *cube)
{
	int	map_x;
	int	map_y;

	int local_x, local_y;
	for (local_y =
		-cube->minimap_radius; local_y <= cube->minimap_radius; local_y++)
	{
		for (local_x =
			-cube->minimap_radius; local_x <= cube->minimap_radius; local_x++)
		{
			map_x = (int)((cube->p_x + local_x / cube->minimap_scale) / S_TEX);
			map_y = (int)((cube->p_y + local_y / cube->minimap_scale) / S_TEX);
			if (map_x >= 0 && map_x < 30 && map_y >= 0 && map_y < 30)
			{
				if (cube->map[map_y][map_x] != 0)
					draw_minimap_pixel(cube, local_x, local_y, 0x003F3733);
			}
		}
	}
}

void	draw_circular_minimap(t_cube *cube)
{
	int	distSq;
	int	y;
	int	x;

	draw_walls_mini_map(cube);
	y = -cube->player_dot_size;
	while (y <= cube->player_dot_size)
	{
		x = -cube->player_dot_size;
		while (x <= cube->player_dot_size)
		{
			distSq = x * x + y * y;
			if (distSq <= (cube->player_dot_size * cube->player_dot_size))
				draw_minimap_pixel(cube, x, y, 0xFF0000);
            x++;
		}
		y++;
	}
	draw_minimap_line(cube, cube->angle, cube->player_dot_size * 4, 0xFF0000);
}
