/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:44:33 by iouhssei          #+#    #+#             */
/*   Updated: 2025/05/20 14:46:54 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

void	print_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (write(2, &str[i], 1) == -1)
			return ;
		i++;
	}
}

t_garbage_collector	*init_garbage_collector(void)
{
	t_garbage_collector	*gc;

	gc = (t_garbage_collector *)malloc(sizeof(t_garbage_collector));
	if (!gc)
	{
		perror("malloc");
		return (NULL);
	}
	gc->head = NULL;
	return (gc);
}

// add the a new node each malloc
void	add_garbage(t_garbage_collector *gc, void *ptr)
{
	t_garbage_node	*new_node;

	if (!gc || !ptr)
		return ;
	new_node = (t_garbage_node *)malloc(sizeof(t_garbage_node));
	if (!new_node)
	{
		perror("malloc");
		return ;
	}
	new_node->ptr = ptr;
	new_node->next = gc->head;
	gc->head = new_node;
}

void	*tracked_malloc(t_garbage_collector *gc, size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		perror("malloc");
		return (NULL);
	}
	add_garbage(gc, ptr);
	return (ptr);
}

void	*free_all(t_garbage_collector *gc)
{
	t_garbage_node	*current;
	t_garbage_node	*temp;

	if (!gc)
		return (NULL);
	current = gc->head;
	while (current)
	{
		free(current->ptr);
		temp = current;
		current = current->next;
		free(temp);
	}
	free(gc);
	gc = NULL;
	return (NULL);
}

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
