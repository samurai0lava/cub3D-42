/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:44:24 by iouhssei          #+#    #+#             */
/*   Updated: 2025/04/08 10:09:00 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

void	run_dda(t_cube *cube, t_raycast *rc)
{
	size_t	row_count;
	size_t	col_count;

	row_count = get_row_count(cube->map.map);
	while (!rc->hit_wall)
	{
		if (rc->sideDistX < rc->sideDistY)
		{
			rc->sideDistX += rc->deltaDistX;
			rc->mapX += rc->stepX;
			rc->side = 0;
		}
		else
		{
			rc->sideDistY += rc->deltaDistY;
			rc->mapY += rc->stepY;
			rc->side = 1;
		}
		if (rc->mapY > row_count)
			break ;
		col_count = ft_strlen(cube->map.map[rc->mapY]);
		if (rc->mapX > col_count)
			break ;
		if (cube->map.map[rc->mapY][rc->mapX] == '1')
			rc->hit_wall = 1;
	}
}

void	compute_wall_distance(t_cube *cube, t_raycast *rc)
{
	if (rc->side == 0)
		rc->perpWallDist = rc->sideDistX - rc->deltaDistX;
	else
		rc->perpWallDist = rc->sideDistY - rc->deltaDistY;
	rc->perpWallDist *= (double)S_TEX;
	rc->angle_diff = eye_fish_correction(rc->ray_angle, cube);
	rc->perpWallDist *= cos(rc->angle_diff);
	if (rc->perpWallDist < 0.5)
		rc->perpWallDist = 0.5;
}

void	select_textures(t_cube *cube, t_raycast *rc)
{
	rc->wall_height = (int)((HEIGHT * S_TEX) / rc->perpWallDist);
	rc->hitX = cube->p_x + rc->rayDirX * rc->perpWallDist;
	rc->hitY = cube->p_y + rc->rayDirY * rc->perpWallDist;
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

void	cast_away(t_cube *cube)
{
	int			i;
	t_raycast	rc;

	cube->num_rays = WIDTH;
	cube->angle_step = FOV / (double)cube->num_rays;
	cube->start_angle = cube->angle - (FOV / 2.0);
	i = 0;
	while (i < cube->num_rays)
	{
		init_raycast(cube, &rc, i);
		run_dda(cube, &rc);
		compute_wall_distance(cube, &rc);
		select_textures(cube, &rc);
		draw_slice(cube, &rc, i);
		i++;
	}
}
