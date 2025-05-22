/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:13:08 by iouhssei          #+#    #+#             */
/*   Updated: 2025/05/22 15:19:40 by iouhssei         ###   ########.fr       */
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
	int			map_x;
	int			map_y;
	int			i;
	t_mini_map	m;

	i = 0;
	m.x = 0.0;
	m.y = 0.0;
	m.x_inc = cos(angle);
	m.y_inc = sin(angle);
	while (i < length)
	{
		map_x = (int)((cube->p_x + (m.x / cube->minimap_scale)) / S_TEX);
		map_y = (int)((cube->p_y + (m.y / cube->minimap_scale)) / S_TEX);
		if (cube->map.map[map_y][map_x] == '1')
			break ;
		draw_minimap_pixel(cube, (int)m.x, (int)m.y, color);
		m.x += m.x_inc;
		m.y += m.y_inc;
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
