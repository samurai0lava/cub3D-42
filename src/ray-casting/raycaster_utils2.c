/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:40:05 by iouhssei          #+#    #+#             */
/*   Updated: 2025/05/22 14:41:03 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

void	select_textures(t_cube *cube, t_raycast *rc)
{
	rc->wall_height = ((HEIGHT * S_TEX) / rc->perpWallDist);
	rc->hitY = cube->p_y + rc->rayDirY * rc->uncorrectedDist;
	rc->hitX = cube->p_x + rc->rayDirX * rc->uncorrectedDist;
	if (rc->side == 0)
	{
		if (rc->rayDirX > 0)
			rc->selected_tex = &cube->texture[0];
		else
			rc->selected_tex = &cube->texture[1];
		rc->wall_x = fmod(rc->hitY, (double)S_TEX);
	}
	else
	{
		if (rc->rayDirY > 0)
			rc->selected_tex = &cube->texture[2];
		else
			rc->selected_tex = &cube->texture[3];
		rc->wall_x = fmod(rc->hitX, (double)S_TEX);
	}
	rc->wall_x /= (double)S_TEX;
	if (rc->wall_x < 0)
		rc->wall_x += 1.0;
}

void	draw_slice(t_cube *cube, t_raycast *rc, int screen_x)
{
	if (rc->selected_tex && rc->selected_tex->img)
	{
		rc->tex_x = (int)(rc->wall_x * rc->selected_tex->width);
		draw_vertical_line_with_texture(cube, screen_x, rc);
	}
	else
	{
		rc->color = 0x00FFFFFF;
		if (rc->tile_val == 2)
			rc->color = 0x0000FFFF;
		else if (rc->tile_val == 3)
			rc->color = 0x00FFFF00;
		else if (rc->tile_val == 4)
			rc->color = 0x00FF00FF;
		draw_vertical_line(cube, screen_x, rc->wall_height,
			color_shading(rc->color, rc->perpWallDist));
	}
}
