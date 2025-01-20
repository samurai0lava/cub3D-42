/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samurai0lava <samurai0lava@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:02:54 by iouhssei          #+#    #+#             */
/*   Updated: 2025/01/20 19:59:18 by samurai0lav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

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
			if (cube->map[map_y][map_x] != 0)
				break ;
			if (x >= 0 && x < S_RES && y >= 0 && y < S_RES)
				my_mlx_pixel_put(cube->data, (int)x, (int)y, color);
		}
		x += x_inc;
		y += y_inc;
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

	num_rays = 100;
	angle_step = FOV / num_rays;
	start_angle = cube->angle - (FOV / 2);
	i = 0;
	while (i < num_rays)
	{
		ray_angle = start_angle + (i * angle_step);
		ray_angle = fmod(ray_angle + 2 * PI, 2 * PI);
		draw_line(cube, cube->p_x, cube->p_y, ray_angle, 500, 0x00FF0000);
		i++;
	}
}

void	draw_filled_circle(t_cube *cube, int center_x, int center_y, int radius,
		int color)
{
	double	radius_squared;
	int x, y;

	radius_squared = 10;
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
				if (x >= 0 && x < 10 && y >= 0 && y < 10)
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