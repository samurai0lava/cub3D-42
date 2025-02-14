/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:44:24 by iouhssei          #+#    #+#             */
/*   Updated: 2025/02/14 17:24:23 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

void	draw_vertical_line(t_cube *cube, int x, int wall_height, int color)
{
	int	y;

	cube->start_y = (HEIGHT / 2) - (wall_height / 2);
	if (cube->start_y < 0)
		cube->start_y = 0;
	cube->end_y = (HEIGHT / 2) + (wall_height / 2);
	if (cube->end_y >= HEIGHT)
		cube->end_y = HEIGHT - 1;
	y = 0;
	while (y < cube->start_y)
	{
		my_mlx_pixel_put(cube->data, x, y, 0x0087CEEB);
		y++;
	}
	while (y < cube->end_y)
	{
		my_mlx_pixel_put(cube->data, x, y, color);
		y++;
	}
	while (y < HEIGHT)
	{
		my_mlx_pixel_put(cube->data, x, y, 0x00333333);
		y++;
	}
}

void	draw_floor(t_cube *cube, int y, int x)
{
	while (y < HEIGHT)
	{
		my_mlx_pixel_put(cube->data, x, y, 0x003E2723);
		y++;
	}
}
int	draw_sky(t_cube *cube, int x, int start_y)
{
	int	y;

	y = 0;
	while (y < start_y)
	{
		my_mlx_pixel_put(cube->data, x, y, 0x003E2723);
		y++;
	}
	return (y);
}

void	draw_vertical_line_with_texture(t_cube *cube, int x, int wall_height,
		int tex_x, double distance, t_data *selected_tex)
{
	double	tex_step;
	double	tex_pos;
	int		tex_y;
	int		y;
	int		color;

	if (wall_height <= 0 || !selected_tex || tex_x < 0
		|| tex_x >= selected_tex->width)
		return ;
	tex_step = (double)selected_tex->height / wall_height;
	cube->start_y = (HEIGHT / 2) - (wall_height / 2);
	if (cube->start_y < 0)
		cube->start_y = 0;
	cube->end_y = (HEIGHT / 2) + (wall_height / 2);
	if (cube->end_y > HEIGHT)
		cube->end_y = HEIGHT;
	y = draw_sky(cube, x, cube->start_y);
	tex_pos = (y - ((HEIGHT / 2) - (wall_height / 2))) * tex_step;
	while (y < cube->end_y)
	{
		tex_y = (int)tex_pos & (selected_tex->height - 1);
		color = get_texture_pixel(selected_tex, tex_x, tex_y);
		my_mlx_pixel_put(cube->data, x, y, color_shading(color, distance));
		tex_pos += tex_step;
		y++;
	}
	draw_floor(cube, y, x);
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
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
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

double	eye_fish_correction(double ray_angle, t_cube *cube)
{
	double	angle_diff;

	angle_diff = ray_angle - cube->angle;
	if (angle_diff > PI)
		angle_diff -= 2 * PI;
	if (angle_diff < -PI)
		angle_diff += 2 * PI;
	return (angle_diff);
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
	int		tex_x;
	t_data	*selected_tex;
	int		color;

	num_rays = WIDTH;
	angle_step = FOV / num_rays; // FOV = 60 / num_rays = 1000
	start_angle = cube->angle - (FOV / 2);
	// parse from the map where the player start
	ray_step = 0.1;
	clean_display(cube);

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
			selected_tex = NULL;
			if (map_x >= 0 && map_x < 10 && map_y >= 0 && map_y < 10
				&& cube->map[map_y][map_x] != 0)
			{
				hit_wall = 1;
				true_distance = get_distance(cube->p_x, cube->p_y, x, y);
				angle_diff = eye_fish_correction(ray_angle, cube);
				true_distance *= cos(angle_diff);
				if (true_distance < 0.5)
					true_distance = 0.5;
				wall_height = (int)((HEIGHT * S_TEX) / true_distance);
				if (cube->map[map_y][map_x] == 4)
					selected_tex = &cube->texture[0];
				else if (cube->map[map_y][map_x] == 2)
					selected_tex = &cube->texture[1];
				else if (cube->map[map_y][map_x] == 3)
					selected_tex = &cube->texture[3];
				else
					selected_tex = &cube->texture[1];
				if (fabs(x - map_x * S_TEX) < 0.1 || fabs(x - (map_x + 1)
						* S_TEX) < 0.1)
					wall_x = fmod(y, S_TEX) / S_TEX;
				else
					wall_x = fmod(x, S_TEX) / S_TEX;
				wall_x = wall_x - floor(wall_x);
				if (selected_tex && selected_tex->img)
				{
					tex_x = (int)(wall_x * selected_tex->width);
					draw_vertical_line_with_texture(cube, i, wall_height, tex_x,
						true_distance, selected_tex);
				}
				else
				{
					color = 0x00FFFFFF;
					if (cube->map[map_y][map_x] == 2)
						color = 0x0000FFFF;
					else if (cube->map[map_y][map_x] == 3)
						color = 0x00FFFF00;
					else if (cube->map[map_y][map_x] == 4)
						color = 0x00FF00FF;
					draw_vertical_line(cube, i, wall_height,
						color_shading(color, true_distance));
				}
				break ;
			}
		}
		if (!hit_wall)
			draw_vertical_line(cube, i, HEIGHT, 0x00000000);
		i++;
	}
}
