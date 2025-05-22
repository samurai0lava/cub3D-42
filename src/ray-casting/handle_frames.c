/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_frames.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 14:39:37 by iouhssei          #+#    #+#             */
/*   Updated: 2025/05/22 13:19:54 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

static char	*build_texture_path(int frame_num, t_cube *cube)
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

static int	load_single_texture(t_cube *cube, int index, char *path)
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

static void	set_texture_prop(t_cube *cube, int index)
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

static void	calculate_weapon_ratios(t_cube *cube)
{
	cube->weapon.x_ratio = (float)cube->weapon.orig_width
		/ cube->weapon.scaled_width;
	cube->weapon.y_ratio = (float)cube->weapon.orig_height
		/ cube->weapon.scaled_height;
}

static void	get_texture_coordinates(t_cube *cube, int x, int y)
{
	cube->weapon.tex_x = x * cube->weapon.x_ratio;
	cube->weapon.tex_y = y * cube->weapon.y_ratio;
	cube->weapon.color = get_texture_pixel((t_data *)cube->frame->content,
			cube->weapon.tex_x, cube->weapon.tex_y);
}

static void	calculate_screen_position(t_cube *cube, int x, int y)
{
	cube->weapon.screen_x = cube->weapon.pos_x + x;
	cube->weapon.screen_y = cube->weapon.pos_y + y;
}

static int	is_pixel_in_bounds(t_cube *cube)
{
	return (cube->weapon.screen_x >= 0 && cube->weapon.screen_x < WIDTH
		&& cube->weapon.screen_y >= 0 && cube->weapon.screen_y < HEIGHT);
}

static int	is_pixel_visible(t_cube *cube)
{
	return ((cube->weapon.color & 0xFF000000) == 0);
}

static void	draw_weapon_pixel(t_cube *cube, int x, int y)
{
	get_texture_coordinates(cube, x, y);
	if (is_pixel_visible(cube))
	{
		calculate_screen_position(cube, x, y);
		if (is_pixel_in_bounds(cube))
		{
			my_mlx_pixel_put(cube->data, cube->weapon.screen_x,
				cube->weapon.screen_y, cube->weapon.color);
		}
	}
}

void	draw_weapon(t_cube *cube)
{
	int	x;
	int	y;

	calculate_weapon_ratios(cube);
	y = 0;
	while (y < cube->weapon.scaled_height)
	{
		x = 0;
		while (x < cube->weapon.scaled_width)
		{
			draw_weapon_pixel(cube, x, y);
			x++;
		}
		y++;
	}
}
