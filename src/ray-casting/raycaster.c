/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:44:24 by iouhssei          #+#    #+#             */
/*   Updated: 2025/01/21 14:32:51 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

void	draw_vertical_line(t_cube *cube, int x, int wall_height, int color)
{
	int	start_y;
	int	end_y;
	int	y;

	start_y = (S_RES / 2) - (wall_height / 2);
	if (start_y < 0)
		start_y = 0;
	end_y = (S_RES / 2) + (wall_height / 2);
	if (end_y >= S_RES)
		end_y = S_RES - 1;
	y = 0;
	while (y < start_y)
	{
		my_mlx_pixel_put(cube->data, x, y, 0x0087CEEB);
		y++;
	}
	while (y < end_y)
	{
		my_mlx_pixel_put(cube->data, x, y, color);
		y++;
	}
	while (y < S_RES)
	{
		my_mlx_pixel_put(cube->data, x, y, 0x00333333);
		y++;
	}
}

double	get_distance(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	clean_display(t_cube *cube)
{
	int	i;
	int	j;

	i = 0;
	while (i < S_RES)
	{
		j = 0;
		while (j < S_RES)
		{
			my_mlx_pixel_put(cube->data, i, j, 0x00000000);
			j++;
		}
		i++;
	}
}
//shading by colors
int	color_shading(int color, double distance)
{
	int	r, g, b;
	int	shade;

	shade = 0xFF - (int)(0xFF * (distance / 1000));
	if (shade < 0)
		shade = 0;

	// Extract RGB components from the original color
	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;

	// Apply shading to each component
	r = (r * shade) / 0xFF;
	g = (g * shade) / 0xFF;
	b = (b * shade) / 0xFF;

	// Combine components back into a single color
	return ((r << 16) | (g << 8) | b);
}


void	cast_away(t_cube *cube)
{
	int num_rays;
	double ray_angle;
	double start_angle;
	double angle_step;
	int i;
	double distance;
	int wall_height;
	double x, y;
	double dx, dy;
	double ray_step;
	int hit_wall;
	int map_x, map_y;
	double true_distance;
	double angle_diff;
	num_rays = S_RES;
	angle_step = FOV / num_rays;
	start_angle = cube->angle - (FOV / 2);
	clean_display(cube);
	ray_step = 0.1;
	i = 0;
	while (i < num_rays)
	{
		ray_angle = start_angle + (i * angle_step);
		ray_angle = fmod(ray_angle + 2 * PI, 2 * PI);
		dx = cos(ray_angle) * ray_step;
		dy = sin(ray_angle) * ray_step;
		x = cube->p_x;
		y = cube->p_y;
		hit_wall = 0;
		distance = 0.0;
		while (distance < 1000 && !hit_wall)
		{
			x += dx;
			y += dy;
			distance += ray_step;
			map_x = (int)x / 50;
			map_y = (int)y / 50;
			if (map_x >= 0 && map_x < 10 && map_y >= 0 && map_y < 10)
			{
				if (cube->map[map_y][map_x] != 0)
				{
					hit_wall = 1;
					true_distance = get_distance(cube->p_x, cube->p_y, x, y);
					angle_diff = ray_angle - cube->angle;
					if (angle_diff < 0)
						angle_diff += 2 * PI;
					if (angle_diff > 2 * PI)
						angle_diff -= 2 * PI;
					true_distance *= cos(angle_diff);
					wall_height = (int)((S_RES * 50) / true_distance);
					if (cube->map[map_y][map_x] == 2)
						draw_vertical_line(cube, i, wall_height, color_shading(0x0000FFFF, true_distance));
					else if (cube->map[map_y][map_x] == 3)
						draw_vertical_line(cube, i, wall_height, color_shading(0x00FFFF00, true_distance));
					else if (cube->map[map_y][map_x] == 4)
						draw_vertical_line(cube, i, wall_height, color_shading(0x00FF00FF, true_distance));
					else
						draw_vertical_line(cube, i, wall_height, color_shading(0x00E4E6A8, true_distance));
					break ;
				}
			}
		}
		i++;
	}
}
