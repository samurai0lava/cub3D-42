/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:37:16 by iouhssei          #+#    #+#             */
/*   Updated: 2025/05/22 14:37:33 by iouhssei         ###   ########.fr       */
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
	t_garbage_node *current;
	t_garbage_node *temp;

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
