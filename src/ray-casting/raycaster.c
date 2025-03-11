/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:44:24 by iouhssei          #+#    #+#             */
/*   Updated: 2025/03/11 03:24:28 by iouhssei         ###   ########.fr       */
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
		my_mlx_pixel_put(cube->data, x, y, 0x003E2723);
		y++;
	}
	return (y);
}

void	draw_vertical_line_with_texture(t_cube *cube, int x, int wall_height,
		int tex_x, double distance, t_data *selected_tex)
{
	double	tex_step;
	double	tex_pos;
	int		tex_y;
	int		y;
	int		color;

	if (wall_height <= 0 || !selected_tex || tex_x < 0
		|| tex_x >= selected_tex->width)
		return ;
	tex_step = (double)selected_tex->height / wall_height;
	cube->start_y = (HEIGHT / 2) - (wall_height / 2);
	if (cube->start_y < 0)
		cube->start_y = 0;
	cube->end_y = (HEIGHT / 2) + (wall_height / 2);
	if (cube->end_y > HEIGHT)
		cube->end_y = HEIGHT;
	y = draw_sky(cube, x, cube->start_y);
	tex_pos = (y - ((HEIGHT / 2) - (wall_height / 2))) * tex_step;
	while (y < cube->end_y)
	{
		tex_y = (int)tex_pos;
		if (tex_y >= selected_tex->height)
			tex_y = selected_tex->height - 1;
		color = get_texture_pixel(selected_tex, tex_x, tex_y);
		my_mlx_pixel_put(cube->data, x, y, color_shading(color, distance));
		tex_pos += tex_step;
		y++;
	}
	draw_floor(cube, y, x);
}




void clean_display(t_cube *cube)
{
    int x, y;

    if (!cube->data || !cube->data->addr)
        return;

    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            my_mlx_pixel_put(cube->data, x, y, 0x000000);
            x++;
        }
        y++;
    }
}

// shading by colors
int	color_shading(int color, double distance)
{
	int	shade;

	int r, g, b;
	shade = 0xFF - (int)(0xFF * (distance / 1000));
	if (shade < 0)
		shade = 0;
	if (shade < 54)
		shade = 54;
	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	r = (r * shade) / 0xFF;
	g = (g * shade) / 0xFF;
	b = (b * shade) / 0xFF;
	return ((r << 16) | (g << 8) | b);
}

double	eye_fish_correction(double ray_angle, t_cube *cube)
{
	double	angle_diff;

	angle_diff = ray_angle - cube->angle;
	if (angle_diff > PI)
		angle_diff -= 2 * PI;
	if (angle_diff < -PI)
		angle_diff += 2 * PI;
	return (angle_diff);
}

// void	cast_away(t_cube *cube)
// {
// 	double ray_angle;
// 	int i;
// 	double true_distance;
// 	double angle_diff;
// 	int wall_height;
// 	int tex_x;
// 	t_data *selected_tex;
// 	double wall_x;
// 	double ray_dir_x;
// 	double ray_dir_y;

// 	int map_x, map_y;
// 	int step_x, step_y;
// 	double side_dist_x, side_dist_y;
// 	double delta_dist_x, delta_dist_y;
// 	int hit_wall, side;

// 	cube->num_rays = WIDTH;
// 	cube->angle_step = FOV / cube->num_rays;
// 	cube->angle = fmod(cube->angle, 2 * PI);
// 	if (cube->angle < 0)
// 		cube->angle += 2 * PI;
// 	cube->start_angle = cube->angle - (FOV / 2);
// 	cube->start_angle = fmod(cube->start_angle + 2 * PI, 2 * PI);
// 	clean_display(cube);
// 	i = 0;
// 	while (i < cube->num_rays)
// 	{
// 		ray_angle = cube->start_angle + (i * cube->angle_step);
// 		ray_angle = fmod(ray_angle, 2 * PI);
// 		if (ray_angle < 0)
// 			ray_angle += 2 * PI;
// 		ray_dir_x = cos(ray_angle);
// 		ray_dir_y = sin(ray_angle);
// 		map_x = (int)(cube->p_x / S_TEX);
// 		map_y = (int)(cube->p_y / S_TEX);
// 		if (ray_dir_x == 0)
// 			delta_dist_x = 1e30;
// 		else
// 			delta_dist_x = fabs(1.0 / ray_dir_x);
// 		if (ray_dir_y == 0)
// 			delta_dist_y = 1e30;
// 		else
// 			delta_dist_y = fabs(1.0 / ray_dir_y);
// 		if (ray_dir_x < 0)
// 		{
// 			step_x = -1;
// 			side_dist_x = (cube->p_x / S_TEX - map_x) * delta_dist_x;
// 		}
// 		else
// 		{
// 			step_x = 1;
// 			side_dist_x = (map_x + 1.0 - cube->p_x / S_TEX) * delta_dist_x;
// 		}
// 		if (ray_dir_y < 0)
// 		{
// 			step_y = -1;
// 			side_dist_y = (cube->p_y / S_TEX - map_y) * delta_dist_y;
// 		}
// 		else
// 		{
// 			step_y = 1;
// 			side_dist_y = (map_y + 1.0 - cube->p_y / S_TEX) * delta_dist_y;
// 		}

		
// 		hit_wall = 0;
// 		while (!hit_wall)
// 		{
// 			if (side_dist_x < side_dist_y)
// 			{
// 				side_dist_x += delta_dist_x;
// 				map_x += step_x;
// 				side = 0;
// 			}
// 			else
// 			{
// 				side_dist_y += delta_dist_y;
// 				map_y += step_y;
// 				side = 1;
// 			}
// 			if (map_y < 0 || map_x < 0 || cube->map[map_y][map_x] > 0)
// 				hit_wall = 1;
// 		}
// 		if (side == 0)
// 			true_distance = side_dist_x - delta_dist_x;
// 		else
// 			true_distance = side_dist_y - delta_dist_y;
// 		angle_diff = eye_fish_correction(ray_angle, cube);
// 		true_distance *= cos(angle_diff);
// 		wall_height = (int)((HEIGHT) / (true_distance + 0.0001));
// 		if (cube->map[map_y][map_x] == 4)
// 			selected_tex = &cube->texture[0];
// 		else if (cube->map[map_y][map_x] == 2)
// 			selected_tex = &cube->texture[1];
// 		else if (cube->map[map_y][map_x] == 3)
// 			selected_tex = &cube->texture[3];
// 		else
// 			selected_tex = &cube->texture[1];
// 		if (side == 0)
// 			wall_x = cube->p_y / S_TEX + true_distance * ray_dir_y;
// 		else
// 			wall_x = cube->p_x / S_TEX + true_distance * ray_dir_x;
// 		wall_x -= floor(wall_x);
// 		tex_x = (int)(wall_x * selected_tex->width);
// 		if ((side == 0 && ray_dir_x < 0) || (side == 1 && ray_dir_y < 0))
// 			tex_x = selected_tex->width - tex_x - 1;
// 		draw_vertical_line_with_texture(cube, i, wall_height, tex_x,
// 			true_distance * S_TEX, selected_tex);
// 		i++;
// 	}
// }


// double	get_distance(double x1, double y1, double x2, double y2)
// {
// 	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
// }

// void	cast_away(t_cube *cube)
// {
// 	double	ray_angle;
// 	int		i;
// 	double	distance;
// 	int		wall_height;
// 	int		hit_wall;
// 	double	true_distance;
// 	double	angle_diff;
// 	double	wall_x;
// 	double	x;
// 	double	y;
// 	double	dx;
// 	double	dy;
// 	int		map_x;
// 	int		map_y;
// 	int		tex_x;
// 	t_data	*selected_tex;
// 	int		color;

// 	cube->num_rays = WIDTH;
// 	cube->angle_step = FOV / cube->num_rays;
// 	cube->start_angle = cube->angle - (FOV / 2);
// 	cube->ray_step = 0.1;
// 	clean_display(cube);	
// 	i = 0;
// 	while (i < cube->num_rays)
// 	{
// 		ray_angle = cube->start_angle + (i * cube->angle_step);
// 		ray_angle = fmod(ray_angle + 2 * PI, 2 * PI);
// 		dx = cos(ray_angle) * cube->ray_step;
// 		dy = sin(ray_angle) * cube->ray_step;
// 		x = cube->p_x;
// 		y = cube->p_y;
// 		hit_wall = 0;
// 		distance = 0.0;
// 		while (distance < 5000 && !hit_wall)
// 		{
// 			x += dx;
// 			y += dy;
// 			distance += cube->ray_step;
// 			map_x = (int)x / S_TEX;
// 			map_y = (int)y / S_TEX;
// 			selected_tex = NULL;
// 			if (map_x >= 0 && map_x < 30 && map_y >= 0 && map_y < 30
// 				&& cube->map[map_y][map_x] != 0)
// 			{
// 				hit_wall = 1;
// 				true_distance = get_distance(cube->p_x, cube->p_y, x, y);
// 				angle_diff = eye_fish_correction(ray_angle, cube);
// 				true_distance *= cos(angle_diff);
// 				if (true_distance < 0.5)
// 					true_distance = 0.5;
// 				wall_height = (int)((HEIGHT * S_TEX) / true_distance);
// 				if (cube->map[map_y][map_x] == 4)
// 					selected_tex = &cube->texture[0];
// 				else if (cube->map[map_y][map_x] == 2)
// 					selected_tex = &cube->texture[1];
// 				else if (cube->map[map_y][map_x] == 3)
// 					selected_tex = &cube->texture[3];
// 				else
// 					selected_tex = &cube->texture[1];
// 				if (fabs(x - map_x * S_TEX) < 0.1 || fabs(x - (map_x + 1)
// 						* S_TEX) < 0.1)
// 					wall_x = fmod(y, S_TEX) / S_TEX;
// 				else
// 					wall_x = fmod(x, S_TEX) / S_TEX;
// 				wall_x = wall_x - floor(wall_x);
// 				if (selected_tex && selected_tex->img)
// 				{
// 					tex_x = (int)(wall_x * selected_tex->width);
// 					draw_vertical_line_with_texture(cube, i, wall_height, tex_x,
// 						true_distance, selected_tex);
// 				}
// 				else
// 				{
// 					color = 0x00FFFFFF;
// 					if (cube->map[map_y][map_x] == 2)
// 						color = 0x0000FFFF;
// 					else if (cube->map[map_y][map_x] == 3)
// 						color = 0x00FFFF00;
// 					else if (cube->map[map_y][map_x] == 4)
// 						color = 0x00FF00FF;
// 					draw_vertical_line(cube, i, wall_height,
// 						color_shading(color, true_distance));
// 				}
// 				break ;
// 			}
// 		}
// 		if (!hit_wall)
// 		{
// 			printf("test\n");	
// 			draw_vertical_line(cube, i, HEIGHT, 0x00000000);
// 		}
// 		i++;
// 	}
// }
#include <math.h>
#include <stdio.h>

// Depending on your headers, you may need these (or not):
// #define PI 3.141592653589793
// #define WIDTH 1280
// #define HEIGHT 720
// #define FOV (60 * (PI / 180.0))
// #define S_TEX 64  // size of each map cell in “world” units, etc.

// -----------------------------------------------------------------
// Example "cast_away" using DDA
// -----------------------------------------------------------------
void cast_away(t_cube *cube)
{
    int     i;
    double  ray_angle;

    // Setup
    cube->num_rays   = WIDTH;
    cube->angle_step = FOV / (double)cube->num_rays;
    cube->start_angle = cube->angle - (FOV / 2.0);

    clean_display(cube);

    // Loop over each “vertical” ray (one per screen column)
    for (i = 0; i < cube->num_rays; i++)
    {
        // Current angle for this ray
        ray_angle = cube->start_angle + i * cube->angle_step;
        // Normalize to [0..2π)
        ray_angle = fmod(ray_angle + 2.0 * PI, 2.0 * PI);

        // Ray direction
        double rayDirX = cos(ray_angle);
        double rayDirY = sin(ray_angle);

        // Which cell of the map we’re in
        int mapX = (int)(cube->p_x / S_TEX);
        int mapY = (int)(cube->p_y / S_TEX);

        // Length of ray from one x-side to the next x-side (or y-side)
        double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1.0 / rayDirX);
        double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1.0 / rayDirY);

        // Step (+1 or -1) and initial sideDist to the first boundary
        int stepX, stepY;
        double sideDistX, sideDistY;

        // Calculate stepX and sideDistX
        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = ( (cube->p_x / (double)S_TEX) - mapX ) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = ( (mapX + 1.0) - (cube->p_x / (double)S_TEX) ) * deltaDistX;
        }

        // Calculate stepY and sideDistY
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = ( (cube->p_y / (double)S_TEX) - mapY ) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = ( (mapY + 1.0) - (cube->p_y / (double)S_TEX) ) * deltaDistY;
        }

        // DDA loop
        int hit_wall = 0;
        int side     = 0; // 0 if we hit x-side, 1 if we hit y-side
        int safety   = 10000; // in case we get stuck, break after many steps

        while (!hit_wall && --safety > 0)
        {
            // Step in x or y direction
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0; // just crossed a vertical boundary
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1; // just crossed a horizontal boundary
            }

            // Bounds check
            if (mapX < 0 || mapX >= 30 || mapY < 0 || mapY >= 30)
                break;

            // Check if there's a wall
            if (cube->map[mapY][mapX] != 0)
                hit_wall = 1;
        }

        // --------------------------------------------------
        // Compute “true distance” from player to wall
        // (the perpendicular distance to avoid fish-eye)
        // --------------------------------------------------
        double perpWallDist;
        // sideDistX or sideDistY ended up overshooting by one iteration:
        // if side == 0, we moved in X last
        // if side == 1, we moved in Y last
        if (side == 0)
        {
            // we stepped in x just now, so subtract deltaDistX:
            perpWallDist = sideDistX - deltaDistX;
        }
        else
        {
            perpWallDist = sideDistY - deltaDistY;
        }

        // sideDist was measured in “tiles,” so multiply by S_TEX
        // if you want distances in the same scale as (cube->p_x, cube->p_y):
        perpWallDist *= (double)S_TEX;

        // Optional: further fish-eye correction if you prefer your own approach
        double angle_diff = eye_fish_correction(ray_angle, cube);
        perpWallDist *= cos(angle_diff);

        // Don’t let distance get too small
        if (perpWallDist < 0.5)
            perpWallDist = 0.5;

        // --------------------------------------------------
        // Calculate wall height in screen space
        // --------------------------------------------------
        int wall_height = (int)((HEIGHT * (double)S_TEX) / perpWallDist);

        // --------------------------------------------------
        // Pick the texture & compute horizontal offset
        // --------------------------------------------------
        t_data *selected_tex = NULL;
        int tile_val = 0; // which tile we hit
        if (mapX >= 0 && mapX < 30 && mapY >= 0 && mapY < 30)
            tile_val = cube->map[mapY][mapX];

        // Choose your texture based on tile_val
        if (tile_val == 4)
            selected_tex = &cube->texture[0];
        else if (tile_val == 2)
            selected_tex = &cube->texture[1];
        else if (tile_val == 3)
            selected_tex = &cube->texture[3];
        else
            selected_tex = &cube->texture[1]; // fallback

        // Find exact point where the ray hit the wall in “world” coords
        double hitX, hitY;
        // To get intersection, we do: player_pos + rayDir * distance
        // But we must be consistent with the distance in world coords.
        hitX = cube->p_x + rayDirX * perpWallDist;
        hitY = cube->p_y + rayDirY * perpWallDist;

        // wall_x for texture sampling
        // Typically: if side == 0, we hit a vertical boundary => use hitY
        //            else we used hitX
        double wall_x;
        if (side == 0)
            wall_x = fmod(hitY, (double)S_TEX);
        else
            wall_x = fmod(hitX, (double)S_TEX);

        // Convert [0..S_TEX) to [0..1)
        wall_x /= (double)S_TEX;

        // Make sure it's within [0..1)
        //  (depending on how you do fmod with negative coords, you might want:
        //    if (wall_x < 0) wall_x += 1.0; )
        if (wall_x < 0) 
            wall_x += 1.0;

        // --------------------------------------------------
        // Render the vertical slice
        // --------------------------------------------------
        if (selected_tex && selected_tex->img)
        {
            int tex_x = (int)(wall_x * selected_tex->width);
            // side == 1 => we might want a different orientation or shading
            draw_vertical_line_with_texture(
                cube,
                i,              // column
                wall_height,
                tex_x,
                perpWallDist,
                selected_tex
            );
        }
        else
        {
            // No texture? Use a flat color
            int color = 0x00FFFFFF;
            if (tile_val == 2)
                color = 0x0000FFFF;
            else if (tile_val == 3)
                color = 0x00FFFF00;
            else if (tile_val == 4)
                color = 0x00FF00FF;

            draw_vertical_line(cube, i, wall_height,
                color_shading(color, perpWallDist));
        }
    } // end for (i in [0..num_rays))
}
