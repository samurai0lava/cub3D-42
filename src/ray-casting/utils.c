/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:44:33 by iouhssei          #+#    #+#             */
/*   Updated: 2025/01/11 15:44:34 by iouhssei         ###   ########.fr       */
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
		print_error(RED "Failed to initialize garbage collector" RESET);
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
		print_error(RED "Failed to initialize garbage collector" RESET);
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
		print_error(RED "Failed to allocate memory\n" RESET);
		return (NULL);
	}
	add_garbage(gc, ptr);
	return (ptr);
}
//free all the nodes

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
	return (NULL);
}
