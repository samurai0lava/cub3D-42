/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:02:54 by iouhssei          #+#    #+#             */
/*   Updated: 2025/04/05 15:37:05 by iouhssei         ###   ########.fr       */
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
	int		i;

	i = 0;
	x = 0.0;
	y = 0.0;
	x_inc = cos(angle);
	y_inc = sin(angle);
	while (i < length)
	{
		map_x = (int)((cube->p_x + (x / cube->minimap_scale)) / S_TEX);
		map_y = (int)((cube->p_y + (y / cube->minimap_scale)) / S_TEX);
		if (map_x < 0 || map_x >= cube->map.map_width || map_y < 0
			|| map_y >= cube->map.map_height)
			break ;
		if (cube->map.map[map_y][map_x] == '1')
			break ;
		draw_minimap_pixel(cube, (int)x, (int)y, color);
		x += x_inc;
		y += y_inc;
		i++;
	}
}

size_t	get_row_count(char **map)
{
	size_t	count;

	count = 0;
	while (map[count] != NULL)
		count++;
	return (count);
}

void    draw_walls_mini_map(t_cube *cube)
{
    int     local_x;
    int     local_y;
    int     row_count;
    double  world_x;
    double  world_y;
    size_t  col_count;
    int     map_x;
    int     map_y;

    row_count = get_row_count(cube->map.map);
    local_y = -cube->minimap_radius;
    while (local_y <= cube->minimap_radius)
    {
        local_x = -cube->minimap_radius;
        while (local_x <= cube->minimap_radius)
        {
            world_x = cube->p_x + (local_x / cube->minimap_scale);
            world_y = cube->p_y + (local_y / cube->minimap_scale);
            map_x = (int)(world_x / S_TEX);
            map_y = (int)(world_y / S_TEX);
            if (map_y >= 0 && map_y < row_count)
            {
                col_count = ft_strlen(cube->map.map[map_y]);
                if (map_x >= 0 && map_x < (int)col_count)
                {
                    if (cube->map.map[map_y][map_x] == '1')
                        draw_minimap_pixel(cube, local_x, local_y, 0x003F3733);
                }
            }
            local_x++;
        }
        local_y++;
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
