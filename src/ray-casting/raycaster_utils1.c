/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 03:05:38 by iouhssei          #+#    #+#             */
/*   Updated: 2025/04/06 09:17:30 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

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

void	clean_display(t_cube *cube)
{
	int x, y;
	if (!cube->data || !cube->data->addr)
		return ;
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

void	init_raycast(t_cube *cube, t_raycast *rc, int ray_index)
{
	init_raycast_angle_and_delta(cube, rc, ray_index);
	init_raycast_steps(cube, rc);
}