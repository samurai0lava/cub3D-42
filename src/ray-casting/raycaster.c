/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:44:24 by iouhssei          #+#    #+#             */
/*   Updated: 2025/01/23 11:06:14 by iouhssei         ###   ########.fr       */
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
void	draw_vertical_line_with_texture(t_cube *cube, int x, int wall_height,
		t_data *texture, int tex_x, double distance)
{
	int	start_y;
	int	end_y;
	int	y;
	int	tex_y;
	int	color;

	start_y = (S_RES / 2) - (wall_height / 2);
	if (start_y < 0)
		start_y = 0;
	end_y = (S_RES / 2) + (wall_height / 2);
	if (end_y >= S_RES)
		end_y = S_RES - 1;
	y = start_y;
	while (y < end_y)
	{
		tex_y = (int)((y - start_y) * (double)texture->height / wall_height);
		color = get_texture_pixel(texture, tex_x, tex_y);
		color = color_shading(color, distance); // Optional shading
		my_mlx_pixel_put(cube->data, x, y, color);
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
// shading by colors
int	color_shading(int color, double distance)
{
	int	shade;

	int r, g, b;
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
	int		num_rays;
	double	ray_angle;
	double	start_angle;
	double	angle_step;
	int		i;
	double	distance;
	int		wall_height;
	double	ray_step;
	int		hit_wall;
	double	true_distance;
	double	angle_diff;
	double	wall_x;
	double	x;
	double	y;
	double	dx;
	double	dy;
	int		map_x;
	int		map_y;
	t_data *selected_tex;
	int tex_x;

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
			map_x = (int)x / S_TEX;
			map_y = (int)y / S_TEX;
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
					wall_height = (int)((S_RES * S_TEX) / true_distance);
					if (cube->map[map_y][map_x] == 2)
					{
						// draw_vertical_line(cube, i, wall_height,
						// 	color_shading(0x0000FFFF, true_distance));
						selected_tex = &cube->texture[0];
						wall_x = cube->p_y + distance * sin(ray_angle);
					}
					else if (cube->map[map_y][map_x] == 3)
					{
						// draw_vertical_line(cube, i, wall_height,
							// color_shading(0x00FFFF00, true_distance));
						selected_tex = &cube->texture[1];

						wall_x = cube->p_y + distance * sin(ray_angle);
					}
					else if (cube->map[map_y][map_x] == 4)
					{
						selected_tex = &cube->texture[2];
						// draw_vertical_line(cube, i, wall_height,
						// 	color_shading(0x00FF00FF, true_distance));
						wall_x = cube->p_x + distance * cos(ray_angle);
					}
					else
					{
						selected_tex = &cube->texture[4];
						// draw_vertical_line(cube, i, wall_height,
						// 	color_shading(0x00E4E6A8, true_distance));
						wall_x = cube->p_x + distance * cos(ray_angle);
					}
					wall_x -= floor(wall_x);
					tex_x =  (int)(wall_x * selected_tex->width);
					draw_vertical_line_with_texture(cube, i, wall_height, selected_tex, tex_x, true_distance);	
					break ;
				}
			}
		}
		i++;
	}
}
