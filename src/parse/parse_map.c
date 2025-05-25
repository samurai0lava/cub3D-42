/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaregra <moaregra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:42:06 by moaregra          #+#    #+#             */
/*   Updated: 2025/05/25 18:53:21 by moaregra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

void	fill_map_array(t_map *map, char **all_file, int lines)
{
	int	i;
	int	j;
	int	map_started;

	i = 0;
	j = 0;
	map_started = 0;
	map->map = malloc(sizeof(char *) * (lines + 1));
	while (all_file[i])
	{
		if (check_map_line(all_file[i]) == 0)
		{
			map_started = 1;
			map->map[j] = ft_strdup(all_file[i]);
			j++;
		}
		else if (map_started)
			break ;
		i++;
	}
	map->map[j] = NULL;
}

void	get_map_into2darray(t_map *map, char *av)
{
	int		lines;
	int		map_started;
	char	*s;
	char	**all_file;
	int		i;

	i = 0;
	s = get_file_in_char(av);
	if (s == NULL)
		return ;
	all_file = split_file(s);
	if (all_file == NULL)
		return ;
	count_map_lines(all_file, &lines, &map_started);
	fill_map_array(map, all_file, lines);
	if (check_map_last(map, all_file) == 0)
	{
		free_map_struct(map);
		free_file_resources(s, all_file);
		exit(1);
	}
	free_file_resources(s, all_file);
}

int	find_last_line_occurance(t_map *map, char **av)
{
	char	*last_map_line;
	int		i;
	int		biggest_index;

	last_map_line = map->map[count_double_char(map->map)];
	i = 0;
	biggest_index = 0;
	while (av[i])
	{
		if (ft_strncmp(av[i], last_map_line, ft_strlen(av[i])) == 0)
		{
			biggest_index = i;
		}
		i++;
	}
	return (biggest_index);
}

int	check_map_last(t_map *map, char **all_file)
{
	int	i;
	int	found_last_map_line;
	int	biggest_index;

	if (map->map[0] == NULL)
		return (0);
	found_last_map_line = 0;
	i = 0;
	biggest_index = find_last_line_occurance(map, all_file);
	while (all_file[i])
	{
		if (biggest_index == i)
		{
			found_last_map_line = 1;
		}
		else if (found_last_map_line && all_file[i][0] != '\0')
			return (print_error(RED "Error\nContent found after map\n" RESET)
				, 0);
		i++;
	}
	if (!found_last_map_line)
		return (print_error(
				RED "Error\nLast map line not found in file\n" RESET)
			, 0);
	return (1);
}

int	count_double_char(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i - 1);
}
