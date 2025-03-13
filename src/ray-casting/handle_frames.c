/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_frames.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 14:39:37 by iouhssei          #+#    #+#             */
/*   Updated: 2025/03/12 00:42:11 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

int	load_frames(t_cube *cube)
{
	char	*path;
	int		i;
	char	*stand;
	int		j;

	stand = "./textures/gnawa/pov";
	i = 0;
	j = 1;
	while (i < 6)
	{
		path = ft_strjoin(stand, ft_strjoin(ft_itoa(j), ".xpm"));
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
		j++;
	}
	return (0);
}

void	add_frame_ls(t_cube *cube)
{
	int		i;
	t_list	*last;

	i = 0;
	cube->frame = ft_lstnew(&cube->weapon.texture[i]);
	if (!cube->frame)
	{
		perror("malloc");
		return ;
	}
	last = cube->frame;
	i++;
	while (i < 6)
	{
		last->next = ft_lstnew(&cube->weapon.texture[i]);
		last = last->next;
		i++;
	}
	last->next = cube->frame;
}

void	update_frame(t_cube *cube)
{
	static int	frame_delay = 0;

	frame_delay++;
	if (frame_delay >= FRAME_DELAY)
	{
		frame_delay = 0;
		if (cube->frame)
			cube->frame = cube->frame->next;
	}
}

void	draw_weapon(t_cube *cube)
{
	int		x;
	int		y;


	cube->weapon.x_ratio = (float)cube->weapon.orig_width / cube->weapon.scaled_width;
	cube->weapon.y_ratio = (float)cube->weapon.orig_height / cube->weapon.scaled_height;
	y = 0;
	while (y < cube->weapon.scaled_height)
	{
		x = 0;
		while (x < cube->weapon.scaled_width)
		{
			cube->weapon.tex_x = x * cube->weapon.x_ratio;
			cube->weapon.tex_y = y * cube->weapon.y_ratio;
			cube->weapon.color = get_texture_pixel((t_data *)cube->frame->content, cube->weapon.tex_x,
					cube->weapon.tex_y);
			if ((cube->weapon.color & 0xFF000000) == 0)
			{
				cube->weapon.screen_x = cube->weapon.pos_x + x;
				cube->weapon.screen_y = cube->weapon.pos_y + y;
				if (cube->weapon.screen_x >= 0 && cube->weapon.screen_x < WIDTH && cube->weapon.screen_y >= 0
					&& cube->weapon.screen_y < HEIGHT)
				{
					my_mlx_pixel_put(cube->data, cube->weapon.screen_x, cube->weapon.screen_y, cube->weapon.color);
				}
			}
			x++;
		}
		y++;
	}
}
