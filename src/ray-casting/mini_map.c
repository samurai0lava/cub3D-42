/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:02:54 by iouhssei          #+#    #+#             */
/*   Updated: 2025/02/20 18:34:14 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

void	draw_minimap_pixel(t_cube *cube, int x, int y, int color)
{
	int		screen_x;
	int		screen_y;
	double	distance_from_center;

	screen_x = MINIMAP_X + x;
	screen_y = MINIMAP_Y + y;
	if (screen_x >= 0 && screen_x < WIDTH && screen_y >= 0 && screen_y < HEIGHT)
	{
		distance_from_center = sqrt(x * x + y * y);
		if (distance_from_center <= MINIMAP_RADIUS)
		{
			my_mlx_pixel_put(cube->data, screen_x, screen_y, color);
		}
	}
}

void	draw_minimap_line(t_cube *cube, double angle, int length, int color)
{
	double	steps;
	double	x_inc;
	double	y_inc;
	double	x;
	double	y;
	int		i;
	int		map_x;
	int		map_y;

	steps = length;
	x_inc = cos(angle);
	y_inc = sin(angle);
	x = 0;
	y = 0;
	i = 0;
	while (i < steps)
	{
		map_x = (int)((cube->p_x + (x / MINIMAP_SCALE)) / S_TEX);
		map_y = (int)((cube->p_y + (y / MINIMAP_SCALE)) / S_TEX);
		if (map_x >= 0 && map_x < 30 && map_y >= 0 && map_y < 30)
		{
			if (cube->map[map_y][map_x] != 0)
				break ;
			draw_minimap_pixel(cube, (int)x, (int)y, color);
		}
		x += x_inc;
		y += y_inc;
		i++;
	}
}

void	draw_walls_mini_map(t_cube *cube)
{
	int	map_x;
	int	map_y;
	int	x;
	int	y;

	y = -MINIMAP_RADIUS;
	while (y <= MINIMAP_RADIUS)
	{
		x = -MINIMAP_RADIUS;
		while (x <= MINIMAP_RADIUS)
		{
			map_x = (int)((cube->p_x + (x * MINIMAP_SCALE)) / S_TEX);
			map_y = (int)((cube->p_y + (y * MINIMAP_SCALE)) / S_TEX);
			if (map_x >= 0 && map_x < 30 && map_y >= 0 && map_y < 30)
			{
				if (cube->map[map_y][map_x] != 0)
					draw_minimap_pixel(cube, x, y, 0x003F3733);
			}
			x++;
		}
		y++;
	}
}

void	draw_circular_minimap(t_cube *cube)
{
	int	x;
	int	y;
	int	sqrt;

	draw_walls_mini_map(cube);
	y = -PLAYER_DOT_SIZE;
	while (y <= PLAYER_DOT_SIZE)
	{
		x = -PLAYER_DOT_SIZE;
		while (x <= PLAYER_DOT_SIZE)
		{
			sqrt = x * x + y * y;
			if (sqrt <= PLAYER_DOT_SIZE * PLAYER_DOT_SIZE)
				draw_minimap_pixel(cube, x, y, 0xFF0000);
			x++;
		}
		y++;
	}
	draw_minimap_line(cube, cube->angle, PLAYER_DOT_SIZE * 3, 0xFF0000);
}
