/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:25:25 by iouhssei          #+#    #+#             */
/*   Updated: 2025/03/12 00:47:26 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

static void	game_loop_mouse(t_cube *cube)
{
	cast_away(cube);
	draw_weapon(cube);
	draw_circular_minimap(cube);
	mlx_put_image_to_window(cube->mlx, cube->mlx_window, cube->data->img, 0, 0);
}

int	handle_mouse_move(int x, int y, t_cube *cube)
{
	static int	inRecenter;
	int			dx;

	if (inRecenter)
	{
		inRecenter = 0;
		cube->mouse_x = x;
		return (0);
	}
	(void)y;
	dx = x - cube->mouse_x;
	if (dx != 0)
	{
		cube->angle += dx * MOUSE_SENSITIVITY;
		cube->angle = fmod(cube->angle + 2 * PI, 2 * PI);
	}
	if (x != WIDTH / 2)
	{
		inRecenter = 1;
		mlx_mouse_move(cube->mlx, cube->mlx_window, WIDTH / 2, HEIGHT / 2);
	}
	game_loop_mouse(cube);
	cube->mouse_x = x;
	return (0);
}
