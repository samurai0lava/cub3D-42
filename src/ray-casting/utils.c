/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:44:33 by iouhssei          #+#    #+#             */
/*   Updated: 2025/04/09 14:42:38 by iouhssei         ###   ########.fr       */
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

// garbage collector for every malloc that i used

// INIT THE GARBAGE COLLECTOR
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

// the tracked malloc
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
// free all the nodes

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

void destroy_mlx(t_cube *cube)
{
	int i;

	// Destroy MLX resources ONLY. Do not free pointers managed by GC (like cube->data)
	if (cube && cube->mlx)
	{
		// Destroy main image buffer *image*
		if (cube->data && cube->data->img) // Check cube->data is still valid
			mlx_destroy_image(cube->mlx, cube->data->img);

		// Destroy wall texture *images*
		i = 0;
		while (i < 4) // Assuming 4 wall textures
		{
			if (cube->texture[i].img)
				mlx_destroy_image(cube->mlx, cube->texture[i].img);
			i++;
		}

		// Destroy weapon texture *images*
		i = 0;
		while (i < 6) // Assuming 6 weapon frames
		{
			// Check weapon texture array pointer itself if it could be NULL
			if (cube->weapon.texture[i].img)
				mlx_destroy_image(cube->mlx, cube->weapon.texture[i].img);
			i++;
		}

		// Clear the circular frame list (Assuming list nodes are NOT GC managed)
		if (cube->frame)
		{
			t_list *start_node = cube->frame;
			t_list *current = start_node->next;
			t_list *next_node;

			start_node->next = NULL; // Break cycle

			while (current != NULL && current != start_node)
			{
				next_node = current->next;
				// If node content needs freeing AND is NOT GC managed:
				// ft_lstdelone(current, free);
				// Else, just free the node structure:
				free(current);
				current = next_node;
			}
			// Free the starting node (check content freeing policy as above)
			free(start_node);
			cube->frame = NULL;
		}

		// Destroy window and display AFTER images
		if (cube->mlx_window)
			mlx_destroy_window(cube->mlx, cube->mlx_window);
		// Add mlx_destroy_display if needed for your OS/MLX version
		mlx_destroy_display(cube->mlx);
		free(cube->mlx); 
		// Do NOT free cube->mlx itself here if it's managed elsewhere or not needed
	}
	// DO NOT free(cube->data) here if it's tracked by GC.
	// DO NOT free(cube) here.
}
