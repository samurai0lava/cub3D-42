/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaregra <moaregra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:38:50 by moaregra          #+#    #+#             */
/*   Updated: 2025/03/17 15:37:57 by moaregra         ###   ########.fr       */
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
	char	*map;
	char	*temp;

	map = NULL;
	fd = open(av, O_RDONLY);
	if (fd == -1)
	{
		printf("Error opening file\n");
		exit(1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		if (map == NULL)
			map = ft_strdup(line);
		else
		{
			temp = ft_strjoin(map, line);
			map = temp;
		}
		free(line);
	}
	close(fd);
	return (map);
}
