/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:44:33 by iouhssei          #+#    #+#             */
/*   Updated: 2025/05/22 15:19:24 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

static void	destroy_text(t_cube *cube)
{
	int	i;

	if (cube->data && cube->data->img)
		mlx_destroy_image(cube->mlx, cube->data->img);
	i = 0;
	while (i < 4)
	{
		if (cube->texture[i].img)
			mlx_destroy_image(cube->mlx, cube->texture[i].img);
		i++;
	}
	i = 0;
	while (i < 6)
	{
		if (cube->weapon.texture[i].img)
			mlx_destroy_image(cube->mlx, cube->weapon.texture[i].img);
		i++;
	}
}

static void	another_destory_img(t_cube *cube)
{
	if (cube->mlx_window)
		mlx_destroy_window(cube->mlx, cube->mlx_window);
	mlx_destroy_display(cube->mlx);
	free(cube->mlx);
}

void	destroy_mlx(t_cube *cube)
{
	t_list	*start_node;
	t_list	*current;
	t_list	*next_node;

	if (cube && cube->mlx)
	{
		destroy_text(cube);
		if (cube->frame)
		{
			start_node = cube->frame;
			current = start_node->next;
			start_node->next = NULL;
			while (current != NULL && current != start_node)
			{
				next_node = current->next;
				free(current);
				current = next_node;
			}
			free(start_node);
			cube->frame = NULL;
		}
		another_destory_img(cube);
	}
}

void	handle_esc(t_cube *cube)
{
	if (!cube)
		exit(1);
	destroy_mlx(cube);
	free_map_struct(&cube->map);
	free_all(cube->gc);
	free(cube);
	exit(0);
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
