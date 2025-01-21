/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:02:54 by iouhssei          #+#    #+#             */
/*   Updated: 2025/01/21 16:05:05 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

void	draw_line(t_cube *cube, double angle, int length, int color)
{
	double	steps;
	int		i;
	double	x2;
	double	y2;
	double dx, dy;
	double x, y;
	double x_inc, y_inc;
	int map_x, map_y;

	i = 0;
	x2 = cube->p_x + cos(angle) * length;
	y2 = cube->p_y + sin(angle) * length;
	dx = x2 - cube->p_x;
	dy = y2 - cube->p_y;
	steps = fmax(fabs(dx), fabs(dy));
	x_inc = dx / steps;
	y_inc = dy / steps;
	x = cube->p_x * MAP_SCALE;
	y = cube->p_y * MAP_SCALE;
	while (i <= steps)
	{
		map_x = (int)(x / TILE_SIZE);
		map_y = (int)(y / TILE_SIZE);
		if (map_x >= 0 && map_x < 10 && map_y >= 0 && map_y < 10)
		{
			if (cube->map[map_y][map_x] != 0)
				break ;
			if (x >= 0 && x < (S_RES * MAP_SCALE) && y >= 0 && y < (S_RES
					* MAP_SCALE))
				my_mlx_pixel_put(cube->data, (int)x, (int)y, color);
		}
		x += x_inc * MAP_SCALE;
		y += y_inc * MAP_SCALE;
		i++;
	}
}

void	cast_away_minirays(t_cube *cube)
{
	int		num_rays;
	double	ray_angle;
	double	start_angle;
	double	angle_step;
	int		i;

	num_rays = 60;
	angle_step = FOV / num_rays;
	start_angle = cube->angle - (FOV / 2);
	i = 0;
	while (i < num_rays)
	{
		ray_angle = start_angle + (i * angle_step);
		ray_angle = fmod(ray_angle + 2 * PI, 2 * PI);
		draw_line(cube, ray_angle, 1000 * MAP_SCALE, 0x0000FFEE);
		i++;
	}
}

void	draw_filled_circle(t_cube *cube, int radius, int color)
{
	double	radius_squared;
	int		x;
	int		y;

	radius_squared = radius * radius * MAP_SCALE;
	draw_map(cube->data, cube->map);
	y = cube->p_y - (radius * MAP_SCALE);
	while (y <= cube->p_y + (radius * MAP_SCALE))
	{
		x = cube->p_x - (radius * MAP_SCALE);
		while (x <= cube->p_x + (radius * MAP_SCALE))
		{
			if (((x - cube->p_x) * (x - cube->p_x) + (y - cube->p_y) * (y
						- cube->p_y)) <= radius_squared)
			{
				if (x >= 0 && x < (10 * MAP_SCALE) && y >= 0 && y < (10
						* MAP_SCALE))
					my_mlx_pixel_put(cube->data, x, y, color);
			}
			x++;
		}
		y++;
	}
	cast_away_minirays(cube);
}
