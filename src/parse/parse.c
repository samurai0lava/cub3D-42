/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:38:50 by moaregra          #+#    #+#             */
/*   Updated: 2025/04/08 13:08:34 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

int	check_file_name(char *s)
{
	if (access(s, F_OK) == -1)
		return (0);
	return (1);
}

int	check_texture(t_map *map)
{
	if (access(map->no, F_OK) == -1)
		return (0);
	if (access(map->ea, F_OK) == -1)
		return (0);
	if (access(map->se, F_OK) == -1)
		return (0);
	if (access(map->we, F_OK) == -1)
		return (0);
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

int	check_virgul(char *av)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (av[i])
	{
		if (av[i] == ',')
			count++;
		i++;
	}
	if (count == 2)
		return (0);
	return (1);
}

char	*get_file_in_char(char *av)
{
	char	*line;
	int		fd;
	char	*map_content;
	char	*temp_join;

	map_content = NULL;
	fd = open(av, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (NULL);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (map_content == NULL)
		{
			map_content = ft_strdup(line);
			if (!map_content)
			{
				free(line);
				close(fd);
				return (NULL);
			}
		}
		else
		{
			temp_join = ft_strjoin(map_content, line);
			if (!temp_join)
			{
				free(map_content);
				free(line);
				close(fd);
				return (NULL);
			}
			free(map_content);
			map_content = temp_join;
		}
		free(line);
		line = NULL;
		line = get_next_line(fd);
	}
	close(fd);
	if (map_content == NULL)
		map_content = ft_strdup("");
	return (map_content);
}
