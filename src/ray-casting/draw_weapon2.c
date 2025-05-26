/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_weapon2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:58:55 by iouhssei          #+#    #+#             */
/*   Updated: 2025/05/22 13:59:10 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

void	add_frame_ls(t_cube *cube)
{
	int		i;
	t_list	*last;

	i = 0;
	cube->frame = ft_lstnew(&cube->weapon.texture[i]);
	if (!cube->frame)
		return (perror("malloc"));
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

void	calculate_weapon_ratios(t_cube *cube)
{
	cube->weapon.x_ratio = (float)cube->weapon.orig_width
		/ cube->weapon.scaled_width;
	cube->weapon.y_ratio = (float)cube->weapon.orig_height
		/ cube->weapon.scaled_height;
}

void	get_texture_coordinates(t_cube *cube, int x, int y)
{
	cube->weapon.tex_x = x * cube->weapon.x_ratio;
	cube->weapon.tex_y = y * cube->weapon.y_ratio;
	cube->weapon.color = get_texture_pixel((t_data *)cube->frame->content,
			cube->weapon.tex_x, cube->weapon.tex_y);
}
