/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:37:49 by iouhssei          #+#    #+#             */
/*   Updated: 2025/05/22 15:01:00 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

size_t	get_row_count(char **map)
{
	size_t	count;

	count = 0;
	while (map[count] != NULL)
		count++;
	return (count);
}

int	close_win(t_cube *cube)
{
	if (!cube)
		exit(1);
	destroy_mlx(cube);
	free_map_struct(&cube->map);
	free_all(cube->gc);
	free(cube);
	exit(0);
}

int	on_key_press(int keycode, t_cube *cube)
{
	if (keycode == ESC)
		handle_esc(cube);
	if (keycode == W_KEY)
		cube->keys.w = 1;
	if (keycode == A_KEY)
		cube->keys.a = 1;
	if (keycode == S_KEY)
		cube->keys.s = 1;
	if (keycode == D_KEY)
		cube->keys.d = 1;
	if (keycode == LEFT_KEY)
		cube->keys.left = 1;
	if (keycode == RIGHT_KEY)
		cube->keys.right = 1;
	return (0);
}

int	on_key_release(int keycode, t_cube *cube)
{
	if (keycode == W_KEY)
		cube->keys.w = 0;
	if (keycode == A_KEY)
		cube->keys.a = 0;
	if (keycode == S_KEY)
		cube->keys.s = 0;
	if (keycode == D_KEY)
		cube->keys.d = 0;
	if (keycode == LEFT_KEY)
		cube->keys.left = 0;
	if (keycode == RIGHT_KEY)
		cube->keys.right = 0;
	return (0);
}
