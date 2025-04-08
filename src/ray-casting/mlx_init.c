/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:44:52 by iouhssei          #+#    #+#             */
/*   Updated: 2025/04/08 11:02:09 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

int	get_texture_pixel(t_data *texture, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	pixel = texture->addr + (y * texture->line_length + x
			* (texture->bits_per_pixel / 8));
	return (*(unsigned int *)pixel);
}

void	init_textures(t_cube *cube)
{
	char	*path[4];
	int		i;

	i = 0;
	path[1] = cube->map.ea;
	path[0] = cube->map.no;
	path[2] = cube->map.se;
	path[3] = cube->map.we;
	while (i < 4)
	{
		cube->texture[i].img = mlx_xpm_file_to_image(cube->mlx, path[i],
				&cube->texture[i].width, &cube->texture[i].height);
		if (!cube->texture[i].img)
		{
			print_error(RED "failed to load textures\n" RESET);
			return ;
		}
		cube->texture[i].addr = mlx_get_data_addr(cube->texture[i].img,
				&cube->texture[i].bits_per_pixel, &cube->texture[i].line_length,
				&cube->texture[i].endian);
		if (!cube->texture[i].addr)
			return ;
		i++;
	}
}
static void mlx_hook_cube(t_cube *cube)
{
	mlx_hook(cube->mlx_window, 17, 1L << 17, close_win, cube);
	mlx_hook(cube->mlx_window, 2, 1L << 0, on_key_press, cube);
	mlx_hook(cube->mlx_window, 3, 1L << 1, on_key_release, cube);
}
void	init_mlx(t_cube *cube, t_data *data)
{

	cube->mlx = mlx_init();
	if (cube->mlx == NULL)
	{
		print_error(RED "mlx_init failed\n" RESET);
		free_all(cube->gc);
		return ;
	}
	cube->mlx_window = mlx_new_window(cube->mlx, WIDTH, HEIGHT, "Cub3D");
	if (cube->mlx_window == NULL)
	{
		print_error(RED "mlx_window failed\n" RESET);
		return ;
	}
	data->img = mlx_new_image(cube->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	init_textures(cube);
	load_frames(cube);
	add_frame_ls(cube);
	mlx_hook_cube(cube);
	init_minimap_params(cube);
	cast_away(cube);
	draw_weapon(cube);
	draw_circular_minimap(cube);
	mlx_put_image_to_window(cube->mlx, cube->mlx_window, cube->data->img, 0, 0);
	mlx_loop_hook(cube->mlx, key_loop, cube);
	mlx_loop(cube->mlx);
}


