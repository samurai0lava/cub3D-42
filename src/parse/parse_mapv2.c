/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_mapv2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaregra <moaregra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:40:44 by moaregra          #+#    #+#             */
/*   Updated: 2025/03/17 15:42:27 by moaregra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

int	check_borders(char *s)
{
	int	i;
	int	last_valid;

	i = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '\t'))
		i++;
	last_valid = ft_strlen(s) - 1;
	while (last_valid >= 0 && (s[last_valid] == ' ' || s[last_valid] == '\t'))
		last_valid--;
	if (last_valid < 0)
		return (1);
	if (s[i] != '1' || s[last_valid] != '1')
		return (1);
	return (0);
}

int	check_top_and_bottom(char *s)
{
	int	i;

	i = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '\t'))
		i++;
	while (s[i])
	{
		if (s[i] != '1')
			return (1);
		i++;
	}
	return (0);
}

int	check_line_endings(char **map, int i, int current_len, int prev_len)
{
	int	j;

	if (prev_len > current_len)
	{
		j = current_len;
		while (j < prev_len)
		{
			if (map[i - 1][j] != '1')
				return (0);
			j++;
		}
	}
	return (1);
}

int	check_map_steps(t_map *map)
{
	int	i;
	int	current_len;
	int	prev_len;

	i = count_double_char(map->map);
	while (i > 0)
	{
		current_len = ft_strlen(map->map[i]);
		prev_len = ft_strlen(map->map[i - 1]);
		while (current_len > 0 && (map->map[i][current_len - 1] == ' '
			|| map->map[i][current_len - 1] == '\t'))
			current_len--;
		while (prev_len > 0 && (map->map[i - 1][prev_len - 1] == ' '
			|| map->map[i - 1][prev_len - 1] == '\t'))
			prev_len--;
		if (!check_line_endings(map->map, i, current_len, prev_len))
			return (0);
		i--;
	}
	return (1);
}

int	check_surroundings(t_map *map, int i, int j, int size)
{
	char	c;

	c = map->map[i][j];
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (i == 0 || i == size || j == 0 || map->map[i - 1][j] == ' '
			|| map->map[i + 1][j] == ' ' || map->map[i][j - 1] == ' '
			|| map->map[i][j + 1] == ' ')
			return (0);
		return (2);
	}
	if (c == '0')
	{
		if (i == 0 || i == size || j == 0 || map->map[i - 1][j] == ' '
			|| map->map[i + 1][j] == ' ' || map->map[i][j - 1] == ' '
			|| map->map[i][j + 1] == ' ')
			return (0);
	}
	return (1);
}
