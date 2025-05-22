/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_weapon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:57:54 by iouhssei          #+#    #+#             */
/*   Updated: 2025/05/22 14:11:29 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

void	calculate_screen_position(t_cube *cube, int x, int y)
{
	cube->weapon.screen_x = cube->weapon.pos_x + x;
	cube->weapon.screen_y = cube->weapon.pos_y + y;
}

int	is_pixel_in_bounds(t_cube *cube)
{
	return (cube->weapon.screen_x >= 0 && cube->weapon.screen_x < WIDTH
		&& cube->weapon.screen_y >= 0 && cube->weapon.screen_y < HEIGHT);
}

int	is_pixel_visible(t_cube *cube)
{
	return ((cube->weapon.color & 0xFF000000) == 0);
}

void	draw_weapon_pixel(t_cube *cube, int x, int y)
{
	get_texture_coordinates(cube, x, y);
	if (is_pixel_visible(cube))
	{
		calculate_screen_position(cube, x, y);
		if (is_pixel_in_bounds(cube))
		{
			my_mlx_pixel_put(cube->data, cube->weapon.screen_x,
				cube->weapon.screen_y, cube->weapon.color);
		}
	}
}

void	draw_weapon(t_cube *cube)
{
	int x;
	int y;

	calculate_weapon_ratios(cube);
	y = 0;
	while (y < cube->weapon.scaled_height)
	{
		x = 0;
		while (x < cube->weapon.scaled_width)
		{
			draw_weapon_pixel(cube, x, y);
			x++;
		}
		y++;
	}
}