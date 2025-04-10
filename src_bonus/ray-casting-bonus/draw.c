/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:37:49 by iouhssei          #+#    #+#             */
/*   Updated: 2025/03/22 23:54:02 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_rectangle(t_data *data, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = x;
	while (i < x + size)
	{
		j = y;
		while (j < y + size)
		{
			if (i >= 0 && i < WIDTH && j >= 0 && j < HEIGHT)
			{
				my_mlx_pixel_put(data, i, j, color);
			}
			j++;
		}
		i++;
	}
}

void	clean_screen(t_data *data, t_cube *cube)
{
	int	x;
	int	y;

	(void)cube;
	x = 0;
	while (x < HEIGHT)
	{
		y = 0;
		while (y < WIDTH)
		{
			my_mlx_pixel_put(data, x, y, 0x00000000);
			y++;
		}
		x++;
	}
}

void	draw_map(t_data *data, t_cube *cube)
{
	int	x;
	int	y;
	int	scaled_tex;

	scaled_tex = S_TEX * MAP_SCALE;
	clean_screen(data, cube);
	y = 0;
	while (y < cube->map.map_height)
	{
		x = 0;
		while (x < cube->map.map_width)
		{
			if (cube->map.map[x][y] != 0)
				draw_rectangle(data, x * scaled_tex, y * scaled_tex, scaled_tex,
					0x00FFEEFF);
			else
				draw_rectangle(data, x * scaled_tex, y * scaled_tex, scaled_tex,
					0x00000000);
			x++;
		}
		y++;
	}
}
