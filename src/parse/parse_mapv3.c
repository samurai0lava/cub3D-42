/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_mapv3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaregra <moaregra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:39:38 by moaregra          #+#    #+#             */
/*   Updated: 2025/05/19 18:26:37 by moaregra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

int	check_map_content(t_map *map, int size)
{
	int	i;
	int	j;
	int	players;
	int	result;

	i = 0;
	players = 0;
	while (map->map[i])
	{
		if (check_borders(map->map[i]) == 1)
			return (0);
		j = 0;
		while (map->map[i][j])
		{
			result = check_surroundings(map, i, j, size);
			if (result == 0)
				return (0);
			else if (result == 2)
				players++;
			j++;
		}
		i++;
	}
	if (players != 1)
		return (0);
	return (1);
}

int	check_map(t_map *map)
{
	int	size;

	size = count_double_char(map->map);
	if (!check_map_steps(map))
		return (0);
		// printf("test1\n");
	if (check_top_and_bottom(map->map[0]) == 1
		|| check_top_and_bottom(map->map[size]) == 1)
		return (0);
		printf("test2\n");
	return (check_map_content(map, size));
}

int	count_till_newline(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
}

int	get_bigger_mapline(char **s)
{
	int	i;
	int	bigger_value;
	int	current_length;

	i = 0;
	if (!s || !s[0])
		return (0);
	bigger_value = count_till_newline(s[0]);
	while (s[i])
	{
		current_length = count_till_newline(s[i]);
		if (current_length > bigger_value)
			bigger_value = current_length;
		i++;
	}
	return (bigger_value);
}

int	get_line_of_biggervalue(char **s)
{
	int	i;
	int	max_length;

	i = 0;
	if (!s || !s[0])
		return (0);
	max_length = get_bigger_mapline(s);
	while (s[i])
	{
		if (count_till_newline(s[i]) == max_length)
			return (i);
		i++;
	}
	return (i - 1);
}
