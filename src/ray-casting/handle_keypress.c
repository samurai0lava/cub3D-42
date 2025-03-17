/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keypress.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:16:55 by iouhssei          #+#    #+#             */
/*   Updated: 2025/03/15 23:17:43 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

int	close_win(t_cube *cube)
{
	if (cube->data && cube->data->img)
		mlx_destroy_image(cube->mlx, cube->data->img);
	mlx_destroy_window(cube->mlx, cube->mlx_window);
	free_all(cube->gc);
	free(cube);
	return (0);
}

static void	game_loop_keypress(t_cube *cube)
{
	cast_away(cube);
	draw_weapon(cube);
	draw_circular_minimap(cube);
	mlx_put_image_to_window(cube->mlx, cube->mlx_window, cube->data->img, 0, 0);
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
int	on_key_press(int keycode, t_cube *cube)
{
	if (keycode == ESC)
	{
		handle_esc(cube);
		exit(0);
	}
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

int	on_key_release(int keycode, t_cube *cube)
{
	if (keycode == W_KEY)
		cube->keys.w = 0;
	if (keycode == A_KEY)
		cube->keys.a = 0;
	if (keycode == S_KEY)
		cube->keys.s = 0;
	if (keycode == D_KEY)
		cube->keys.d = 0;
	if (keycode == LEFT_KEY)
		cube->keys.left = 0;
	if (keycode == RIGHT_KEY)
		cube->keys.right = 0;
	return (0);
}

int	key_loop(t_cube *cube)
{
	cube->hc.new_x = cube->p_x;
	cube->hc.new_y = cube->p_y;
	if (cube->keys.w)
	{
		cube->hc.new_x += cos(cube->angle) * MVM_SPEED;
		cube->hc.new_y += sin(cube->angle) * MVM_SPEED;
		update_frame(cube);
	}
	if (cube->keys.s)
	{
		cube->hc.new_x -= cos(cube->angle) * MVM_SPEED;
		cube->hc.new_y -= sin(cube->angle) * MVM_SPEED;
		update_frame(cube);
	}
	if (cube->keys.d)
	{
		cube->hc.new_x += cos(cube->angle + M_PI_2) * MVM_SPEED;
		cube->hc.new_y += sin(cube->angle + M_PI_2) * MVM_SPEED;
		update_frame(cube);
	}
	if (cube->keys.a)
	{
		cube->hc.new_x += cos(cube->angle - M_PI_2) * MVM_SPEED;
		cube->hc.new_y += sin(cube->angle - M_PI_2) * MVM_SPEED;
		update_frame(cube);
	}
	if (cube->keys.left)
		cube->angle -= RT_SPEED;
	if (cube->keys.right)
		cube->angle += RT_SPEED;
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
	return (0);
}
