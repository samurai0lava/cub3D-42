/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 19:13:34 by iouhssei          #+#    #+#             */
/*   Updated: 2025/02/19 17:12:26 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

void	scale_weapon(t_cube *cube)
{
	float	scale_factor;

	scale_factor = (float)(HEIGHT / 2) / cube->weapon.orig_height;
	if (cube->weapon.orig_width * scale_factor > WIDTH * 0.8)
		scale_factor = (float)(WIDTH * 0.8) / cube->weapon.orig_width;
	cube->weapon.scaled_width = cube->weapon.orig_width * scale_factor;
	cube->weapon.scaled_height = cube->weapon.orig_height * scale_factor;
	cube->weapon.pos_x = (WIDTH - cube->weapon.scaled_width) / 2;
	cube->weapon.pos_y = HEIGHT - cube->weapon.scaled_height;
}

void	init_weapon(t_cube *cube)
{
	int	bpp;
	int	line_length;
	int	endian;

	cube->weapon.texture[0].img = mlx_xpm_file_to_image(cube->mlx,
			"./textures/gnawa/pov.xpm", &cube->weapon.orig_width,
			&cube->weapon.orig_height);
	if (!cube->weapon.texture[0].img)
	{
		print_error(RED "Failed to load weapon\n" RESET);
		return ;
	}
	cube->weapon.texture[0].addr = mlx_get_data_addr(cube->weapon.texture[0].img,
			&bpp, &line_length, &endian);
	cube->weapon.texture[0].bits_per_pixel = bpp;
	cube->weapon.texture[0].line_length = line_length;
	cube->weapon.texture[0].endian = endian;
	cube->weapon.texture[0].width = cube->weapon.orig_width;   // Add these
	cube->weapon.texture[0].height = cube->weapon.orig_height; // Add these
	scale_weapon(cube);
}
