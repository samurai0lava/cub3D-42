/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:38:50 by moaregra          #+#    #+#             */
/*   Updated: 2025/05/25 21:48:23 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

int	check_file_name(char *s)
{
	int	fd;

	fd = open(s, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

int	check_texture(t_map *map)
{
	int	fd;

	fd = open(map->no, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	fd = open(map->ea, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	fd = open(map->se, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	fd = open(map->we, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

size_t	ft_strlenewline(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
}

static char	*utils_gnl(int fd)
{
	char	*map_content;
	char	*temp_join;
	char	*line;

	map_content = NULL;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (map_content == NULL)
		{
			map_content = ft_strdup(line);
			if (!map_content)
				return (free(line), close(fd), NULL);
		}
		else
		{
			temp_join = ft_strjoin(map_content, line);
			if (!temp_join)
				return (free(line), close(fd), NULL);
			map_content = temp_join;
		}
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), map_content);
}

char	*get_file_in_char(char *av)
{
	int		fd;
	char	*map_content;

	map_content = NULL;
	fd = open(av, O_RDONLY);
	if (fd == -1)
		return (perror("Error opening file"), NULL);
	map_content = utils_gnl(fd);
	if (map_content == NULL)
		map_content = ft_strdup("");
	if (!map_content)
		return (close(fd), NULL);
	return (map_content);
}
