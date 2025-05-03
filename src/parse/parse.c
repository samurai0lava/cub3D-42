/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaregra <moaregra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:38:50 by moaregra          #+#    #+#             */
/*   Updated: 2025/04/17 16:40:31 by moaregra         ###   ########.fr       */
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

int	check_virgul(char *av)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!av)
		return (0);
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
	char	*temp_join;
	char	*map_content;

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
				free(line);
				close(fd);
				return (NULL);
			}
			map_content = temp_join;
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (map_content == NULL)
		map_content = ft_strdup("");
	if (!map_content)
	{
		close(fd);
		return (NULL);
	}
	return (map_content);
}
