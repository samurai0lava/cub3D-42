/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:41:29 by iouhssei          #+#    #+#             */
/*   Updated: 2025/05/22 15:28:10 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

void	select_textures(t_cube *cube, t_raycast *rc)
{
	rc->wall_height = ((HEIGHT * S_TEX) / rc->perpwalldist);
	rc->hity = cube->p_y + rc->raydiry * rc->uncorrecteddist;
	rc->hitx = cube->p_x + rc->raydirx * rc->uncorrecteddist;
	if (rc->side == 0)
	{
		if (rc->raydirx > 0)
			rc->selected_tex = &cube->texture[0];
		else
			rc->selected_tex = &cube->texture[1];
		rc->wall_x = fmod(rc->hity, (double)S_TEX);
	}
	else
	{
		if (rc->raydiry > 0)
			rc->selected_tex = &cube->texture[2];
		else
			rc->selected_tex = &cube->texture[3];
		rc->wall_x = fmod(rc->hitx, (double)S_TEX);
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
			color_shading(rc->color, rc->perpwalldist));
	}
}

static void	small_update(t_raycast *rc)
{
	rc->hit_wall = 0;
	rc->side = 0;
	rc->safety = 10000;
}

void	init_raycast_steps(t_cube *cube, t_raycast *rc)
{
	if (rc->raydirx < 0)
	{
		rc->stepx = -1;
		rc->sidedistx = ((cube->p_x / (double)S_TEX) - rc->mapx)
			* rc->deltadistx;
	}
	else
	{
		rc->stepx = 1;
		rc->sidedistx = ((rc->mapx + 1.0) - (cube->p_x / (double)S_TEX))
			* rc->deltadistx;
	}
	if (rc->raydiry < 0)
	{
		rc->stepy = -1;
		rc->sidedisty = ((cube->p_y / (double)S_TEX) - rc->mapy)
			* rc->deltadisty;
	}
	else
	{
		rc->stepy = 1;
		rc->sidedisty = ((rc->mapy + 1.0) - (cube->p_y / (double)S_TEX))
			* rc->deltadisty;
	}
	small_update(rc);
}

int	on_key_press(int keycode, t_cube *cube)
{
	if (keycode == ESC)
		handle_esc(cube);
	if (keycode == W_KEY)
		cube->keys.w = 1;
	if (keycode == A_KEY)
		cube->keys.a = 1;
	if (keycode == S_KEY)
		cube->keys.s = 1;
	if (keycode == D_KEY)
		cube->keys.d = 1;
	if (keycode == LEFT_KEY)
		cube->keys.left = 1;
	if (keycode == RIGHT_KEY)
		cube->keys.right = 1;
	return (0);
}
