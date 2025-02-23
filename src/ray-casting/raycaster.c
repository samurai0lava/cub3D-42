/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:44:24 by iouhssei          #+#    #+#             */
/*   Updated: 2025/02/23 17:41:24 by iouhssei         ###   ########.fr       */
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
		tex_y = (int)tex_pos;
		if (tex_y >= selected_tex->height)
			tex_y = selected_tex->height - 1;
		color = get_texture_pixel(selected_tex, tex_x, tex_y);
		my_mlx_pixel_put(cube->data, x, y, color_shading(color, distance));
		tex_pos += tex_step;
		y++;
	}
	draw_floor(cube, y, x);
}




void clean_display(t_cube *cube)
{
    int x, y;

    if (!cube->data || !cube->data->addr)
        return;

    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            my_mlx_pixel_put(cube->data, x, y, 0x000000);
            x++;
        }
        y++;
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
	if (shade < 54)
		shade = 54;
	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	r = (r * shade) / 0xFF;
	g = (g * shade) / 0xFF;
	b = (b * shade) / 0xFF;
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
	double ray_angle;
	int i;
	double true_distance;
	double angle_diff;
	int wall_height;
	int tex_x;
	t_data *selected_tex;
	double wall_x;
	double ray_dir_x;
	double ray_dir_y;

	int map_x, map_y;
	int step_x, step_y;
	double side_dist_x, side_dist_y;
	double delta_dist_x, delta_dist_y;
	int hit_wall, side;

	cube->num_rays = WIDTH;
	cube->angle_step = FOV / cube->num_rays;
	cube->angle = fmod(cube->angle, 2 * PI);
	if (cube->angle < 0)
		cube->angle += 2 * PI;
	cube->start_angle = cube->angle - (FOV / 2);
	cube->start_angle = fmod(cube->start_angle + 2 * PI, 2 * PI);
	clean_display(cube);
	i = 0;
	while (i < cube->num_rays)
	{
		ray_angle = cube->start_angle + (i * cube->angle_step);
		ray_angle = fmod(ray_angle, 2 * PI);
		if (ray_angle < 0)
			ray_angle += 2 * PI;
		ray_dir_x = cos(ray_angle);
		ray_dir_y = sin(ray_angle);
		map_x = (int)(cube->p_x / S_TEX);
		map_y = (int)(cube->p_y / S_TEX);
		if (ray_dir_x == 0)
			delta_dist_x = 1e30;
		else
			delta_dist_x = fabs(1.0 / ray_dir_x);
		if (ray_dir_y == 0)
			delta_dist_y = 1e30;
		else
			delta_dist_y = fabs(1.0 / ray_dir_y);
		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (cube->p_x / S_TEX - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - cube->p_x / S_TEX) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (cube->p_y / S_TEX - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - cube->p_y / S_TEX) * delta_dist_y;
		}

		
		hit_wall = 0;
		while (!hit_wall)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (map_y < 0 || map_x < 0 || cube->map[map_y][map_x] > 0)
				hit_wall = 1;
		}
		if (side == 0)
			true_distance = side_dist_x - delta_dist_x;
		else
			true_distance = side_dist_y - delta_dist_y;
		angle_diff = eye_fish_correction(ray_angle, cube);
		true_distance *= cos(angle_diff);
		wall_height = (int)((HEIGHT) / (true_distance + 0.0001));
		if (cube->map[map_y][map_x] == 4)
			selected_tex = &cube->texture[0];
		else if (cube->map[map_y][map_x] == 2)
			selected_tex = &cube->texture[1];
		else if (cube->map[map_y][map_x] == 3)
			selected_tex = &cube->texture[3];
		else
			selected_tex = &cube->texture[1];
		if (side == 0)
			wall_x = cube->p_y / S_TEX + true_distance * ray_dir_y;
		else
			wall_x = cube->p_x / S_TEX + true_distance * ray_dir_x;
		wall_x -= floor(wall_x);
		tex_x = (int)(wall_x * selected_tex->width);
		if ((side == 0 && ray_dir_x < 0) || (side == 1 && ray_dir_y < 0))
			tex_x = selected_tex->width - tex_x - 1;

		draw_vertical_line_with_texture(cube, i, wall_height, tex_x,
			true_distance * S_TEX, selected_tex);
		i++;
	}
}


// double	get_distance(double x1, double y1, double x2, double y2)
// {
// 	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
// }

// void	cast_away(t_cube *cube)
// {
// 	double	ray_angle;
// 	int		i;
// 	double	distance;
// 	int		wall_height;
// 	int		hit_wall;
// 	double	true_distance;
// 	double	angle_diff;
// 	double	wall_x;
// 	double	x;
// 	double	y;
// 	double	dx;
// 	double	dy;
// 	int		map_x;
// 	int		map_y;
// 	int		tex_x;
// 	t_data	*selected_tex;
// 	int		color;

// 	cube->num_rays = WIDTH;
// 	cube->angle_step = FOV / cube->num_rays;
// 	cube->start_angle = cube->angle - (FOV / 2);
// 	cube->ray_step = 0.1;
// 	clean_display(cube);
// 	i = 0;
// 	while (i < cube->num_rays)
// 	{
// 		ray_angle = cube->start_angle + (i * cube->angle_step);
// 		ray_angle = fmod(ray_angle + 2 * PI, 2 * PI);
// 		dx = cos(ray_angle) * cube->ray_step;
// 		dy = sin(ray_angle) * cube->ray_step;
// 		x = cube->p_x;
// 		y = cube->p_y;
// 		hit_wall = 0;
// 		distance = 0.0;
// 		while (distance < 1000 && !hit_wall)
// 		{
// 			x += dx;
// 			y += dy;
// 			distance += cube->ray_step;
// 			map_x = (int)x / S_TEX;
// 			map_y = (int)y / S_TEX;
// 			selected_tex = NULL;
// 			if (map_x >= 0 && map_x < 10 && map_y >= 0 && map_y < 10
// 				&& cube->map[map_y][map_x] != 0)
// 			{
// 				hit_wall = 1;
// 				true_distance = get_distance(cube->p_x, cube->p_y, x, y);
// 				angle_diff = eye_fish_correction(ray_angle, cube);
// 				true_distance *= cos(angle_diff);
// 				if (true_distance < 0.5)
// 					true_distance = 0.5;
// 				wall_height = (int)((HEIGHT * S_TEX) / true_distance);
// 				if (cube->map[map_y][map_x] == 4)
// 					selected_tex = &cube->texture[0];
// 				else if (cube->map[map_y][map_x] == 2)
// 					selected_tex = &cube->texture[1];
// 				else if (cube->map[map_y][map_x] == 3)
// 					selected_tex = &cube->texture[3];
// 				else
// 					selected_tex = &cube->texture[1];
// 				if (fabs(x - map_x * S_TEX) < 0.1 || fabs(x - (map_x + 1)
// 						* S_TEX) < 0.1)
// 					wall_x = fmod(y, S_TEX) / S_TEX;
// 				else
// 					wall_x = fmod(x, S_TEX) / S_TEX;
// 				wall_x = wall_x - floor(wall_x);
// 				if (selected_tex && selected_tex->img)
// 				{
// 					tex_x = (int)(wall_x * selected_tex->width);
// 					draw_vertical_line_with_texture(cube, i, wall_height, tex_x,
// 						true_distance, selected_tex);
// 				}
// 				else
// 				{
// 					color = 0x00FFFFFF;
// 					if (cube->map[map_y][map_x] == 2)
// 						color = 0x0000FFFF;
// 					else if (cube->map[map_y][map_x] == 3)
// 						color = 0x00FFFF00;
// 					else if (cube->map[map_y][map_x] == 4)
// 						color = 0x00FF00FF;
// 					draw_vertical_line(cube, i, wall_height,
// 						color_shading(color, true_distance));
// 				}
// 				break ;
// 			}
// 		}
// 		if (!hit_wall)
// 			draw_vertical_line(cube, i, HEIGHT, 0x00000000);
// 		i++;
// 	}
// }