/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:37:49 by iouhssei          #+#    #+#             */
/*   Updated: 2025/02/20 20:17:12 by iouhssei         ###   ########.fr       */
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
void	clean_screen(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	while (x < 30)
	{
		y = 0;
		while (y < 30)
		{
			my_mlx_pixel_put(data, x, y, 0x00000000);
			y++;
		}
		x++;
	}
}

void	draw_map(t_data *data, int map[30][30])
{
	int	x;
	int	y;
	int	scaled_tex;

	scaled_tex = S_TEX * MAP_SCALE;
	clean_screen(data);
	y = 0;
	while (y < 30)
	{
		x = 0;
		while (x < 30)
		{
			if (map[y][x] != 0)
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
