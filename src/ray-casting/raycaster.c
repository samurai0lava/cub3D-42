/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:44:24 by iouhssei          #+#    #+#             */
/*   Updated: 2025/01/17 12:36:52 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

void	cast_away(t_cube *cube)
{
	int		num_rays;
	double	ray_angle;
	double	start_angle;
	double	angle_step;
	int		i;

	num_rays = 60;
	angle_step = FOV / num_rays;
	start_angle = cube->angle - (FOV / 2);
	i = 0;
	while (i < num_rays)
	{
		ray_angle = start_angle + (i * angle_step);
		ray_angle = fmod(ray_angle + 2 * PI, 2 * PI);
		draw_line(cube, cube->p_x, cube->p_y, ray_angle, 300, 0x00FF0000);
		i++;
	}
}
