/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 03:04:06 by iouhssei          #+#    #+#             */
/*   Updated: 2025/04/08 12:55:19 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

void	draw_vertical_line(t_cube *cube, int x, int wall_height, int color)
{
	int	y;

	cube->start_y = (HEIGHT / 2) - (wall_height / 2);
	if (cube->start_y < 0)
		cube->start_y = 0;
	cube->end_y = (HEIGHT / 2) + (wall_height / 2);
	if (cube->end_y >= HEIGHT)
		cube->end_y = HEIGHT - 1;
	y = 0;
	while (y < cube->start_y)
	{
		my_mlx_pixel_put(cube->data, x, y, 0x0087CEEB);
		y++;
	}
	while (y < cube->end_y)
	{
		my_mlx_pixel_put(cube->data, x, y, color);
		y++;
	}
	while (y < HEIGHT)
	{
		my_mlx_pixel_put(cube->data, x, y, 0x00333333);
		y++;
	}
}

void	draw_floor(t_cube *cube, int y, int x)
{
	while (y < HEIGHT)
	{
		my_mlx_pixel_put(cube->data, x, y, 0x003E2723);
		y++;
	}
}

int	draw_sky(t_cube *cube, int x, int start_y)
{
	int	y;

	y = 0;
	while (y < start_y)
	{
		my_mlx_pixel_put(cube->data, x, y, 0X00000000);
		y++;
	}
	return (y);
}

void	init_raycast_angle_and_delta(t_cube *cube, t_raycast *rc, int ray_index)
{
	rc->ray_angle = cube->start_angle + ray_index * cube->angle_step;
	rc->ray_angle = fmod(rc->ray_angle + 2.0 * PI, 2.0 * PI);
	rc->rayDirX = cos(rc->ray_angle);
	rc->rayDirY = sin(rc->ray_angle);

	rc->mapX = (int)(cube->p_x / S_TEX);
	rc->mapY = (int)(cube->p_y / S_TEX);
	if (rc->rayDirX == 0)
		rc->deltaDistX = 1e30;
	else
		rc->deltaDistX = fabs(1.0 / rc->rayDirX);
	if (rc->rayDirY == 0)
		rc->deltaDistY = 1e30;
	else
		rc->deltaDistY = fabs(1.0 / rc->rayDirY);
}

void	init_raycast_steps(t_cube *cube, t_raycast *rc)
{
	if (rc->rayDirX < 0)
	{
		rc->stepX = -1;
		rc->sideDistX = ((cube->p_x / (double)S_TEX) - rc->mapX)
			* rc->deltaDistX;
	}
	else
	{
		rc->stepX = 1;
		rc->sideDistX = ((rc->mapX + 1.0) - (cube->p_x / (double)S_TEX))
			* rc->deltaDistX;
	}
	if (rc->rayDirY < 0)
	{
		rc->stepY = -1;
		rc->sideDistY = ((cube->p_y / (double)S_TEX) - rc->mapY)
			* rc->deltaDistY;
	}
	else
	{
		rc->stepY = 1;
		rc->sideDistY = ((rc->mapY + 1.0) - (cube->p_y / (double)S_TEX))
			* rc->deltaDistY;
	}
	rc->hit_wall = 0;
	rc->side = 0;
	rc->safety = 10000;
}