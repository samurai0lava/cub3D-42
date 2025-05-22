/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:44:24 by iouhssei          #+#    #+#             */
/*   Updated: 2025/05/22 15:28:10 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

static void	update_sides(t_raycast *rc)
{
	if (rc->sidedistx < rc->sidedisty)
	{
		rc->sidedistx += rc->deltadistx;
		rc->mapx += rc->stepx;
		rc->side = 0;
	}
	else
	{
		rc->sidedisty += rc->deltadisty;
		rc->mapy += rc->stepy;
		rc->side = 1;
	}
}

void	run_dda(t_cube *cube, t_raycast *rc)
{
	size_t	row_count;
	size_t	col_count;

	row_count = get_row_count(cube->map.map);
	while (!rc->hit_wall)
	{
		update_sides(rc);
		if (rc->mapy > row_count)
			break ;
		col_count = ft_strlen(cube->map.map[rc->mapy]);
		if (rc->mapx > col_count)
			break ;
		if (cube->map.map[rc->mapy][rc->mapx] == '1')
			rc->hit_wall = 1;
	}
}

void	compute_wall_distance(t_cube *cube, t_raycast *rc)
{
	if (rc->side == 0)
		rc->perpwalldist = rc->sidedistx - rc->deltadistx;
	else
		rc->perpwalldist = rc->sidedisty - rc->deltadisty;
	rc->uncorrecteddist = rc->perpwalldist * S_TEX;
	rc->angle_diff = eye_fish_correction(rc->ray_angle, cube);
	rc->perpwalldist *= cos(rc->angle_diff) * S_TEX;
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
