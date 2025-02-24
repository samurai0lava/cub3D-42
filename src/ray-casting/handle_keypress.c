/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keypress.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:16:55 by iouhssei          #+#    #+#             */
/*   Updated: 2025/02/24 15:07:08 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

// int	handle_keypress(int keycode, t_cube *cube)
// {
// 	int		movement_speed;
// 	int		new_x;
// 	int		new_y;
// 	int		map_x;
// 	int		map_y;
// 	double	rotation_speed;

// 	map_x = new_x / S_TEX;
// 	map_y = new_y / S_TEX;
// 	movement_speed = 8;
// 	rotation_speed = 0.08;
// 	new_x = cube->p_x;
// 	new_y = cube->p_y;
// 	if (keycode == ESC)
// 	{
// 		if (cube->data && cube->data->img)
// 			mlx_destroy_image(cube->mlx, cube->data->img);
// 		mlx_destroy_window(cube->mlx, cube->mlx_window);
// 		free_all(cube->gc);
// 		free(cube);
// 		exit(0);
// 	}
// 	else if (keycode == W_KEY)
// 	{
// 		new_x += cos(cube->angle) * movement_speed;
// 		new_y += sin(cube->angle) * movement_speed;
// 	}
// 	else if (keycode == S_KEY)
// 	{
// 		new_x -= cos(cube->angle) * movement_speed;
// 		new_y -= sin(cube->angle) * movement_speed;
// 	}
// 	else if (keycode == D_KEY)
// 	{
// 		new_x += cos(cube->angle + M_PI_2) * movement_speed;
// 		new_y += sin(cube->angle + M_PI_2) * movement_speed;
// 	}
// 	else if (keycode == A_KEY)
// 	{
// 		new_x += cos(cube->angle - M_PI_2) * movement_speed;
// 		new_y += sin(cube->angle - M_PI_2) * movement_speed;
// 	}
// 	else if (keycode == LEFT_KEY)
// 		cube->angle -= rotation_speed;
// 	else if (keycode == RIGHT_KEY)
// 		cube->angle += rotation_speed;
// 	cube->angle = fmod(cube->angle + 2 * PI, 2 * PI);
// 	if (map_x >= 0 && map_x < 30 && map_y >= 0 && map_y < 30
// 		&& cube->map[map_y][map_x] == 0)
// 	{
// 		cube->p_x = new_x;
// 		cube->p_y = new_y;
// 	}
// 	cast_away(cube);
// 	draw_weapon(cube);
// 	draw_circular_minimap(cube);
// 	mlx_put_image_to_window(cube->mlx, cube->mlx_window, cube->data->img, 0, 0);
// 	update_frame(cube);
// 	return (1);
// }


int handle_keypress(int keycode, t_cube *cube)
{
    int     movement_speed;
    int     new_x;
    int     new_y;
    int     map_x;
    int     map_y;
    double  rotation_speed;

    movement_speed = 8;
    rotation_speed = 0.08;
    new_x = cube->p_x;
    new_y = cube->p_y;
    
    if (keycode == ESC)
    {
        if (cube->data && cube->data->img)
            mlx_destroy_image(cube->mlx, cube->data->img);
        mlx_destroy_window(cube->mlx, cube->mlx_window);
        free_all(cube->gc);
        free(cube);
        exit(0);
    }
    else if (keycode == W_KEY)
    {
        new_x += cos(cube->angle) * movement_speed;
        new_y += sin(cube->angle) * movement_speed;
    }
    else if (keycode == S_KEY)
    {
        new_x -= cos(cube->angle) * movement_speed;
        new_y -= sin(cube->angle) * movement_speed;
    }
    else if (keycode == D_KEY)
    {
        new_x += cos(cube->angle + M_PI_2) * movement_speed;
        new_y += sin(cube->angle + M_PI_2) * movement_speed;
    }
    else if (keycode == A_KEY)
    {
        new_x += cos(cube->angle - M_PI_2) * movement_speed;
        new_y += sin(cube->angle - M_PI_2) * movement_speed;
    }
    else if (keycode == LEFT_KEY)
        cube->angle -= rotation_speed;
    else if (keycode == RIGHT_KEY)
        cube->angle += rotation_speed;
    cube->angle = fmod(cube->angle + 2 * PI, 2 * PI);
    int temp_x = cube->p_x;
    int temp_y = cube->p_y;
    map_x = (temp_x + (new_x - cube->p_x)) / S_TEX;
    map_y = temp_y / S_TEX;
    if (map_x >= 0 && map_x < 30 && map_y >= 0 && map_y < 30
        && cube->map[map_y][map_x] == 0)
    {
        cube->p_x = temp_x + (new_x - cube->p_x);
    }
    map_x = cube->p_x / S_TEX;
    map_y = (temp_y + (new_y - temp_y)) / S_TEX;
    if (map_x >= 0 && map_x < 30 && map_y >= 0 && map_y < 30
        && cube->map[map_y][map_x] == 0)
    {
        cube->p_y = temp_y + (new_y - temp_y);
    }
    cast_away(cube);
    draw_weapon(cube);
    draw_circular_minimap(cube);
    mlx_put_image_to_window(cube->mlx, cube->mlx_window, cube->data->img, 0, 0);
    update_frame(cube);
    return (1);
}