/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:44:24 by iouhssei          #+#    #+#             */
/*   Updated: 2025/01/19 15:34:26 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../inc/cube3d.h"

// void	cast_away(t_cube *cube)
// {
// 	int		num_rays;
// 	double	ray_angle;
// 	double	start_angle;
// 	double	angle_step;
// 	int		i;

// 	num_rays = 60;
// 	angle_step = FOV / num_rays;
// 	start_angle = cube->angle - (FOV / 2);
// 	i = 0;
// 	while (i < num_rays)
// 	{
// 		ray_angle = start_angle + (i * angle_step);
// 		ray_angle = fmod(ray_angle + 2 * PI, 2 * PI);
// 		draw_line(cube, cube->p_x, cube->p_y, ray_angle, 300, 0x00FF0000);
// 		i++;
// 	}
// }

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
		my_mlx_pixel_put(cube->data, x, y, 0x00333333);
		y++;
	}
	while (y < end_y)
	{
		my_mlx_pixel_put(cube->data, x, y, color);
		y++;
	}
	while (y < S_RES)
	{
		my_mlx_pixel_put(cube->data, x, y, 0x00666666);
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
	double steps;
	int hit_wall;
	int map_x, map_y;

	num_rays = S_RES;
	angle_step = FOV / num_rays;
	start_angle = cube->angle - (FOV / 2);
	clean_display(cube);

	i = 0;
	while (i < num_rays)
	{
		ray_angle = start_angle + (i * angle_step);
		ray_angle = fmod(ray_angle + 2 * PI, 2 * PI);
		x = cube->p_x;
		y = cube->p_y;
		steps = 0;
		hit_wall = 0;
		while (steps < 1000 && !hit_wall)
		{
			x += cos(ray_angle);
			y += sin(ray_angle);
			map_x = (int)x / 50;
			map_y = (int)y / 50;
			if (map_x >= 0 && map_x < 10 && map_y >= 0 && map_y < 10)
			{
				if (cube->map[map_y][map_x] == 1)
				{
					hit_wall = 1;
					break ;
				}
			}
			steps++;
		}

		if (hit_wall)
		{
			distance = get_distance(cube->p_x, cube->p_y, x, y) * cos(ray_angle
					- cube->angle);
			wall_height = (int)((S_RES * 50) / distance);
			draw_vertical_line(cube, i, wall_height, 0x00FFFFFF);
		}
		i++;
	}
}