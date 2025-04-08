/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:39:01 by iouhssei          #+#    #+#             */
/*   Updated: 2025/04/08 13:05:36 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin( char *stash, char *buffer)
{
	char	*line;
	size_t	i;
	size_t	j;

	if (!stash)
	{
		stash = (char *)malloc(1 * sizeof(char));
		if (!stash)
			return (NULL);
		stash[0] = '\0';
	}
	if (!stash || !buffer)
		return (NULL);
	line = malloc(ft_strlen(stash) + ft_strlen(buffer) + 1);
	if (!line)
		return (NULL);
	i = -1;
	j = 0;
	while (stash[++i] != '\0')
		line[i] = stash[i];
	while (buffer[j] != '\0')
		line[i++] = buffer[j++];
	line[ft_strlen(stash) + ft_strlen(buffer)] = '\0';
	// free(stash);
	return (line);
}
