/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keypress.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:16:55 by iouhssei          #+#    #+#             */
/*   Updated: 2025/05/22 15:11:54 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

static void	game_loop_keypress(t_cube *cube)
{
	cast_away(cube);
	draw_weapon(cube);
	draw_circular_minimap(cube);
	mlx_put_image_to_window(cube->mlx, cube->mlx_window, cube->data->img, 0, 0);
}

void	init_colliding(t_cube *cube, double *px, double *py)
{
	cube->collid.left = *px - PLAYER_RADIUS;
	cube->collid.right = *px + PLAYER_RADIUS;
	cube->collid.top = *py - PLAYER_RADIUS;
	cube->collid.bottom = *py + PLAYER_RADIUS;
	cube->collid.left_tile = (int)(cube->collid.left / S_TEX);
	cube->collid.right_tile = (int)(cube->collid.right / S_TEX);
	cube->collid.top_tile = (int)(cube->collid.top / S_TEX);
	cube->collid.bottom_tile = (int)(cube->collid.bottom / S_TEX);
}

static int	is_colliding(t_cube *cube, double px, double py)
{
	int	ty;
	int	tx;

	init_colliding(cube, &px, &py);
	ty = cube->collid.top_tile;
	while (ty <= cube->collid.bottom_tile)
	{
		tx = cube->collid.left_tile;
		while (tx <= cube->collid.right_tile)
		{
			if (cube->map.map[ty][tx] != '0' && cube->map.map[ty][tx] != 'N'
				&& cube->map.map[ty][tx] != 'S' && cube->map.map[ty][tx] != 'E'
				&& cube->map.map[ty][tx] != 'W')
				return (1);
			tx++;
		}
		ty++;
	}
	return (0);
}

static void	mvm_keys(t_cube *cube)
{
	cube->hc.new_x = cube->p_x;
	cube->hc.new_y = cube->p_y;
	if (cube->keys.w)
	{
		cube->hc.new_x += cos(cube->angle) * MVM_SPEED;
		cube->hc.new_y += sin(cube->angle) * MVM_SPEED;
	}
	if (cube->keys.s)
	{
		cube->hc.new_x -= cos(cube->angle) * MVM_SPEED;
		cube->hc.new_y -= sin(cube->angle) * MVM_SPEED;
	}
	if (cube->keys.d)
	{
		cube->hc.new_x += cos(cube->angle + M_PI_2) * MVM_SPEED;
		cube->hc.new_y += sin(cube->angle + M_PI_2) * MVM_SPEED;
	}
	if (cube->keys.a)
	{
		cube->hc.new_x += cos(cube->angle - M_PI_2) * MVM_SPEED;
		cube->hc.new_y += sin(cube->angle - M_PI_2) * MVM_SPEED;
	}
}

int	key_loop(t_cube *cube)
{
	mvm_keys(cube);
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
	cube->hc.candidate_y = cube->hc.temp_y + (cube->hc.new_y - cube->p_y);
	if (!is_colliding(cube, cube->p_x, cube->hc.candidate_y))
		cube->p_y = cube->hc.candidate_y;
	update_frame(cube);
	game_loop_keypress(cube);
	return (0);
}
