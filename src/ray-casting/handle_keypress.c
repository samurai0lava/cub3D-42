/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keypress.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:16:55 by iouhssei          #+#    #+#             */
/*   Updated: 2025/03/14 04:06:39 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

static void	game_loop_keypress(t_cube *cube)
{
	cast_away(cube);
	draw_weapon(cube);
	draw_circular_minimap(cube);
	mlx_put_image_to_window(cube->mlx, cube->mlx_window, cube->data->img, 0, 0);
	update_frame(cube);
}
static void	handle_esc(t_cube *cube)
{
	if (cube->data && cube->data->img)
		mlx_destroy_image(cube->mlx, cube->data->img);
	mlx_destroy_window(cube->mlx, cube->mlx_window);
	free_all(cube->gc);
	free(cube);
}

static int	is_colliding(t_cube *cube, double px, double py)
{
	cube->collid.left = px - PLAYER_RADIUS;
	cube->collid.right = px + PLAYER_RADIUS;
	cube->collid.top = py - PLAYER_RADIUS;
	cube->collid.bottom = py + PLAYER_RADIUS;
	cube->collid.left_tile = (int)(cube->collid.left / S_TEX);
	cube->collid.right_tile = (int)(cube->collid.right / S_TEX);
	cube->collid.top_tile = (int)(cube->collid.top / S_TEX);
	cube->collid.bottom_tile = (int)(cube->collid.bottom / S_TEX);
	cube->collid.ty = cube->collid.top_tile;
	while (cube->collid.ty <= cube->collid.bottom_tile)
	{
		cube->collid.tx = cube->collid.left_tile;
		while (cube->collid.tx <= cube->collid.right_tile)
		{
			if (cube->collid.ty < 0 || cube->collid.ty >= 30
				|| cube->collid.tx < 0 || cube->collid.tx >= 30)
				return (1);
			if (cube->map[cube->collid.ty][cube->collid.tx] != 0)
				return (1);
			cube->collid.tx++;
		}
		cube->collid.ty++;
	}
	return (0);
}

int	handle_keypress(int keycode, t_cube *cube)
{
	cube->hc.movement_speed = 8;
	cube->hc.rotation_speed = 0.08;
	cube->hc.new_x = cube->p_x;
	cube->hc.new_y = cube->p_y;
	if (keycode == ESC)
	{
		handle_esc(cube);
		exit(0);
	}
	else if (keycode == W_KEY)
	{
		cube->hc.new_x += cos(cube->angle) * cube->hc.movement_speed;
		cube->hc.new_y += sin(cube->angle) * cube->hc.movement_speed;
	}
	else if (keycode == S_KEY)
	{
		cube->hc.new_x -= cos(cube->angle) * cube->hc.movement_speed;
		cube->hc.new_y -= sin(cube->angle) * cube->hc.movement_speed;
	}
	else if (keycode == D_KEY)
	{
		cube->hc.new_x += cos(cube->angle + M_PI_2) * cube->hc.movement_speed;
		cube->hc.new_y += sin(cube->angle + M_PI_2) * cube->hc.movement_speed;
	}
	else if (keycode == A_KEY)
	{
		cube->hc.new_x += cos(cube->angle - M_PI_2) * cube->hc.movement_speed;
		cube->hc.new_y += sin(cube->angle - M_PI_2) * cube->hc.movement_speed;
	}
	else if (keycode == LEFT_KEY)
		cube->angle -= cube->hc.rotation_speed;
	else if (keycode == RIGHT_KEY)
		cube->angle += cube->hc.rotation_speed;
	cube->angle = fmod(cube->angle + 2 * PI, 2 * PI);
	cube->hc.temp_x = cube->p_x;
	cube->hc.temp_y = cube->p_y;
	cube->hc.candidate_x = cube->hc.temp_x + (cube->hc.new_x - cube->p_x);
	if (!is_colliding(cube, cube->hc.candidate_x, cube->hc.temp_y))
		cube->p_x = cube->hc.candidate_x;
	cube->hc.candidate_y = cube->hc.temp_y + (cube->hc.new_y - cube->hc.temp_y);
	if (!is_colliding(cube, cube->p_x, cube->hc.candidate_y))
		cube->p_y = cube->hc.candidate_y;
	game_loop_keypress(cube);
	return (1);
}
