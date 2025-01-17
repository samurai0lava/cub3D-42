/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:44:24 by iouhssei          #+#    #+#             */
/*   Updated: 2025/01/17 12:18:28 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

void	cast_away(t_cube *cube)
{
	double fov = PI / 3;
	int num_rays = 60;
	double ray_angle;
	double angle_step = fov / num_rays;
	int ray_length = 250;
	int i = 0;

	double start_angle = cube->angle - (fov / 2);

	// Cast rays from left to right of FOV
	while (i < num_rays)
	{
		ray_angle = start_angle + (i * angle_step);

		// Normalize angle to stay within 0 to 2*PI
		ray_angle = fmod(ray_angle + 2 * PI, 2 * PI);

		// Draw the ray
		draw_line(cube, cube->p_x, cube->p_y, ray_angle, ray_length,
			0x00FF0000);
		i++;
	}
}