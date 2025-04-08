/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 10:40:03 by iouhssei          #+#    #+#             */
/*   Updated: 2025/04/08 10:57:59 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

static t_wall	calculate_wall_draw_params(t_raycast *rc)
{
	t_wall	params;

	params.tex_step = (double)rc->selected_tex->height / rc->wall_height;
	params.start_y = (HEIGHT / 2) - (rc->wall_height / 2);
	params.end_y = (HEIGHT / 2) + (rc->wall_height / 2);
	if (params.start_y < 0)
		params.start_y = 0;
	if (params.end_y > HEIGHT)
		params.end_y = HEIGHT;
	return (params);
}

static void	draw_textured_wall_segment(t_cube *cube, t_raycast *rc,
		t_wall params, int draw_start_y)
{
	double	tex_pos;
	int		tex_y;
	int		y;
	int		color;

	tex_pos = (draw_start_y - (HEIGHT / 2.0 - rc->wall_height / 2.0))
		* params.tex_step;
	y = draw_start_y;
	while (y < params.end_y)
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		else if (tex_y >= rc->selected_tex->height)
			tex_y = rc->selected_tex->height - 1;
		color = get_texture_pixel(rc->selected_tex, rc->tex_x, tex_y);
		my_mlx_pixel_put(cube->data, rc->x, y, color_shading(color,
				rc->perpWallDist));
		tex_pos += params.tex_step;
		y++;
	}
}

void	draw_vertical_line_with_texture(t_cube *cube, int x, t_raycast *rc)
{
	t_wall params;
	int start_y;

    rc->x = x;
	if (rc->wall_height <= 0 || !rc->selected_tex || rc->tex_x < 0
		|| rc->tex_x >= rc->selected_tex->width)
	{
		start_y = draw_sky(cube, x, 0);
		draw_floor(cube, start_y, x);  
		return ;
	}
	params = calculate_wall_draw_params(rc);
	start_y = draw_sky(cube, x, params.start_y);
	draw_textured_wall_segment(cube, rc, params, start_y);
	draw_floor(cube, params.end_y, x);
}
