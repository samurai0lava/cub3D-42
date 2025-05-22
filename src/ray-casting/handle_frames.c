/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_frames.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 14:39:37 by iouhssei          #+#    #+#             */
/*   Updated: 2025/05/22 14:02:16 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

char	*build_texture_path(int frame_num, t_cube *cube)
{
	char	*stand;
	char	*path;
	char	*temp;
	char	*num;

	stand = ft_strdup("./textures/gnawa/pov");
	num = ft_itoa(frame_num);
	if (!num)
		return (perror("malloc"), NULL);
	temp = ft_strjoin(num, ".xpm");
	if (!temp)
		return (perror("malloc"), NULL);
	path = ft_strjoin(stand, temp);
	add_garbage(cube->gc, temp);
	if (!path)
		return (perror("malloc"), NULL);
	add_garbage(cube->gc, path);
	return (path);
}

int	load_single_texture(t_cube *cube, int index, char *path)
{
	cube->weapon.texture[index].img = mlx_xpm_file_to_image(cube->mlx, path,
			&cube->weapon.orig_width, &cube->weapon.orig_height);
	if (!cube->weapon.texture[index].img)
		return (perror("mlx_xpm_file_to_image"), 1);
	cube->weapon.texture[index].addr = mlx_get_data_addr(cube->weapon.texture[index].img,
			&cube->weapon.texture[index].bits_per_pixel,
			&cube->weapon.texture[index].line_length,
			&cube->weapon.texture[index].endian);
	return (0);
}

void	set_texture_prop(t_cube *cube, int index)
{
	cube->weapon.texture[index].width = cube->weapon.orig_width;
	cube->weapon.texture[index].height = cube->weapon.orig_height;
	scale_weapon(cube);
}

int	load_frames(t_cube *cube)
{
	char	*path;
	int		i;

	i = 0;
	while (i < 6)
	{
		path = build_texture_path(i + 1, cube);
		if (!path)
			return (1);
		if (load_single_texture(cube, i, path))
			return (1);
		set_texture_prop(cube, i);
		i++;
	}
	return (0);
}
