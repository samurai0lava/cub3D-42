/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_frames.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 14:39:37 by iouhssei          #+#    #+#             */
/*   Updated: 2025/02/17 14:08:47 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

// LOAD THE TEXTURES
// ADD  IT TO THE LINKED LIST IN ORDER (circular linked list)
// FUNCTION TO UPADTE THE MOUVEMENT

int	load_frames(t_cube *cube)
{
	char	*path;
	int		i;
	char	*stand;

	stand = "./textures/gnawa/pov";
	i = 0;
	while (i < 6)
	{
		path = ft_strjoin(stand, ft_strjoin(ft_itoa(i), ".xpm"));
		if (!path)
			return (perror("malloc"), 1);
		cube->weapon.texture[i].img = mlx_xpm_file_to_image(cube->mlx, path,
				&cube->weapon.orig_width, &cube->weapon.orig_height);
		if (!cube->weapon.texture[i].img)
			return (free(path), 1);
		free(path);
		cube->weapon.texture[i].addr = mlx_get_data_addr(cube->weapon.texture[i].img,
				&cube->weapon.texture[i].bits_per_pixel,
				&cube->weapon.texture[i].line_length,
				&cube->weapon.texture[i].endian);
		cube->weapon.texture[i].width = cube->weapon.orig_width;
		cube->weapon.texture[i].height = cube->weapon.orig_height;
		scale_weapon(cube);
		i++;
	}
	return (0);
}

void	add_frame_ls(t_cube *cube)
{
	t_frame_anime	*current;
    
}

void	update_frame(t_cube *cube)
{
}