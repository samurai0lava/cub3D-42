/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:44:52 by iouhssei          #+#    #+#             */
/*   Updated: 2025/01/12 12:17:35 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char	*dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

void draw_rectangle(t_data *data, int x, int y, int size, int color)
{
    for (int i = x; i < x + size; i++)
    {
        for (int j = y; j < y + size; j++)
        {
            if (i >= 0 && i < 500 && j >= 0 && j < 500)
            {
                my_mlx_pixel_put(data, i, j, color);
            }
        }
    }
}

void draw_map(t_data *data, int map[10][10])
{
	int x;
	int y;

	x = 0;
    while (x < 500)
	{
		y = 0;
        while (y < 500)
		{
            my_mlx_pixel_put(data, x, y, 0x00000000);
			y++;
		}
		x++;
	}
	y = 0;
    while (y < 10)
    {
		x = 0;
        while (x < 10)
        {
            if (map[y][x] == 1)
                draw_rectangle(data, x * 50, y * 50, 50, 0x00FFFFFF);
            else 
                draw_rectangle(data, x * 50, y * 50, 50, 0x00333333);
			x++;
        }
		y++;
    }
}

void draw_filled_circle(t_data *data, int center_x, int center_y, int radius, int color)
{
    int radius_squared = radius * radius;
    int x, y;


    for (y = center_y - radius; y <= center_y + radius; y++)
    {
        for (x = center_x - radius; x <= center_x + radius; x++)
        {
            if (((x - center_x) * (x - center_x) + (y - center_y) * (y - center_y)) <= radius_squared)
            {
                if (x >= 0 && x < 500 && y >= 0 && y < 500)
                {
                    my_mlx_pixel_put(data, x, y, color);
                }
            }
        }
    }
}

void	init_mlx(t_cube *cube, t_data *data)
{
    int example_map[10][10] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 1, 1, 1, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
    
    cube->mlx = mlx_init();
    if (cube->mlx == NULL)
    {
        print_error(RED "mlx_init failed\n" RESET);
        free_all(cube->gc);
        return ;
    }
    cube->mlx_window = mlx_new_window(cube->mlx, 500, 500, "Cub3D");
    if (cube->mlx_window == NULL)
    {
        print_error(RED "mlx_window failed\n" RESET);
        return ;
    }
    data->img = mlx_new_image(cube->mlx, 500, 500);
    data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
            &data->line_length, &data->endian);
    cube->data = data;
    cube->p_x = 250;
    cube->p_y = 250;
    ft_memcpy(cube->map, example_map, sizeof(example_map));
    draw_map(data, cube->map);
    draw_filled_circle(data, cube->p_x, cube->p_y, 10, 0x00FFFFFF);
    mlx_put_image_to_window(cube->mlx, cube->mlx_window, data->img, 0, 0);
    mlx_hook(cube->mlx_window, 2, 1L << 0, handle_keypress, cube);
    mlx_loop(cube->mlx);
}

int handle_keypress(int keycode, t_cube *cube)
{
    int movement_speed;
    int new_x;
    int new_y;

	movement_speed = 6;
	new_x = cube->p_x;
	new_y = cube->p_y;
    if (keycode == ESC)
    {
        if (cube->data && cube->data->img)
            mlx_destroy_image(cube->mlx, cube->data->img);
        mlx_destroy_window(cube->mlx, cube->mlx_window);
        free_all(cube->gc);
        exit(0);
    }
    else if (keycode == W_KEY)
        new_y -= movement_speed;
    else if (keycode == S_KEY)
        new_y += movement_speed;
    else if (keycode == A_KEY)
        new_x -= movement_speed;
    else if (keycode == D_KEY)
        new_x += movement_speed;

    int map_x = new_x / 50;
    int map_y = new_y / 50;
    
    if (map_x >= 0 && map_x < 10 && map_y >= 0 && map_y < 10 && 
        cube->map[map_y][map_x] != 1)
    {
        cube->p_x = new_x;
        cube->p_y = new_y;
    }
    draw_map(cube->data, cube->map);
    draw_filled_circle(cube->data, cube->p_x, cube->p_y, 10, 0x00FFFFFF);
    mlx_put_image_to_window(cube->mlx, cube->mlx_window, cube->data->img, 0, 0);
    return (1);
}