/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:25:25 by iouhssei          #+#    #+#             */
/*   Updated: 2025/02/19 17:55:53 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

int	handle_mouse_move(int x, int y, t_cube *cube)
{
	int dx;
	static int first_move = 1;
	(void)y;
	if (first_move)
	{
		first_move = 0;
		cube->mouse_x = x;
		return (0);
	}
	dx = x - cube->mouse_x;
	cube->angle += dx * MOUSE_SENSITIVITY;
	cube->angle = fmod(cube->angle + 2 * PI, 2 * PI);
	mlx_mouse_move(cube->mlx, cube->mlx_window, WIDTH / 2, HEIGHT / 2);
	cube->mouse_x = WIDTH / 2;
	cast_away(cube);
	draw_weapon(cube);
	// update_frame(cube);
	draw_circular_minimap(cube);
	mlx_put_image_to_window(cube->mlx, cube->mlx_window, cube->data->img, 0, 0);
	return (0);
}