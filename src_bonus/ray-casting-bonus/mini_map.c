/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:02:54 by iouhssei          #+#    #+#             */
/*   Updated: 2025/05/22 15:15:25 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

static void	draw_mp(t_cube *cube, t_mini_map m)
{
	if (m.map_x >= 0 && m.map_x < (int)m.col_count)
	{
		if (cube->map.map[m.map_y][m.map_x] == '1')
			draw_minimap_pixel(cube, m.local_x, m.local_y, 0x00FFFFFF);
	}
}

void	draw_walls_mini_map(t_cube *cube)
{
	t_mini_map	m;

	m.row_count = get_row_count(cube->map.map);
	m.local_y = -cube->minimap_radius;
	while (m.local_y <= cube->minimap_radius)
	{
		m.local_x = -cube->minimap_radius;
		while (m.local_x <= cube->minimap_radius)
		{
			m.world_x = cube->p_x + (m.local_x / cube->minimap_scale);
			m.world_y = cube->p_y + (m.local_y / cube->minimap_scale);
			m.map_x = (int)(m.world_x / S_TEX);
			m.map_y = (int)(m.world_y / S_TEX);
			if (m.map_y >= 0 && m.map_y < m.row_count)
			{
				m.col_count = ft_strlen(cube->map.map[m.map_y]);
				draw_mp(cube, m);
			}
			m.local_x++;
		}
		m.local_y++;
	}
}

void	draw_circular_minimap(t_cube *cube)
{
	int	distsq;
	int	y;
	int	x;

	draw_walls_mini_map(cube);
	y = -cube->player_dot_size;
	while (y <= cube->player_dot_size)
	{
		x = -cube->player_dot_size;
		while (x <= cube->player_dot_size)
		{
			distsq = x * x + y * y;
			if (distsq <= (cube->player_dot_size * cube->player_dot_size))
				draw_minimap_pixel(cube, x, y, 0xFF0000);
			x++;
		}
		y++;
	}
	draw_minimap_line(cube, cube->angle, cube->player_dot_size * 4, 0xFF0000);
}
