/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 19:13:34 by iouhssei          #+#    #+#             */
/*   Updated: 2025/02/14 17:17:00 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

void    scale_weapon(t_cube *cube)
{
    float   scale_factor;

    scale_factor = (float)(HEIGHT / 2) / cube->weapon.orig_height;
    if (cube->weapon.orig_width * scale_factor > WIDTH * 0.8)
        scale_factor = (float)(WIDTH * 0.8) / cube->weapon.orig_width;
    cube->weapon.scaled_width = cube->weapon.orig_width * scale_factor;
    cube->weapon.scaled_height = cube->weapon.orig_height * scale_factor;    
    cube->weapon.pos_x = (WIDTH - cube->weapon.scaled_width) / 2;
    cube->weapon.pos_y = HEIGHT - cube->weapon.scaled_height;
}

void    init_weapon(t_cube *cube)
{
    int     bpp;
    int     line_length;
    int     endian;

    cube->weapon.texture.img = mlx_xpm_file_to_image(cube->mlx, "./textures/gnawa/pov.xpm",
            &cube->weapon.orig_width, &cube->weapon.orig_height);;
	if(!cube->weapon.texture.img)
	{
		print_error(RED "Failed to load weapon\n" RESET);
		return;
	}
    cube->weapon.texture.addr = mlx_get_data_addr(cube->weapon.texture.img, &bpp, &line_length,
            &endian);
    cube->weapon.texture.bits_per_pixel = bpp;
    cube->weapon.texture.line_length = line_length;
    cube->weapon.texture.endian = endian;
    cube->weapon.texture.width = cube->weapon.orig_width;   // Add these
    cube->weapon.texture.height = cube->weapon.orig_height; // Add these
    scale_weapon(cube);
}

void	draw_weapon(t_cube *cube)
{
	int x, y;
	int tex_x;
	int tex_y;
	int color;
	float x_ratio;
	float y_ratio;

	x_ratio = (float)cube->weapon.orig_width / cube->weapon.scaled_width;
	y_ratio = (float)cube->weapon.orig_height / cube->weapon.scaled_height;
	y = 0;
	while (y < cube->weapon.scaled_height)
	{
		x = 0;
		while (x < cube->weapon.scaled_width)
		{
			tex_x = x * x_ratio;
			tex_y = y * y_ratio;
			color = get_texture_pixel(&cube->weapon.texture, tex_x, tex_y);
			if ((color & 0xFF000000) == 0)
			{
				int screen_x = cube->weapon.pos_x + x;
				int screen_y = cube->weapon.pos_y + y;
				if (screen_x >= 0 && screen_x < WIDTH && screen_y >= 0
					&& screen_y < HEIGHT)
				{
					my_mlx_pixel_put(cube->data, screen_x, screen_y, color);
				}
			}
			x++;
		}
		y++;
	}
}