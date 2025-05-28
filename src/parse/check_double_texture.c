/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_double_texture.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaregra <moaregra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:33:06 by moaregra          #+#    #+#             */
/*   Updated: 2025/05/28 19:55:50 by moaregra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

int	count_occurrences(char **lines, const char *target)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (lines[i] != NULL)
	{
		if (ft_strncmp(lines[i], target, strlen(target)) == 0
			&& (lines[i][strlen(target)] == ' '
			|| lines[i][strlen(target)] == '\t'))
		{
			count++;
		}
		i++;
	}
	return (count);
}

int	validate_textures(char **lines)
{
	const char	*required_textures[] = {"NO", "SO", "WE", "EA", "F", "C"};
	int			num_textures;
	int			i;
	int			count;

	num_textures = 6;
	i = 0;
	while (i < num_textures)
	{
		count = count_occurrences(lines, required_textures[i]);
		if (count != 1)
		{
			print_error(RED "Error\nInvalid\n" RESET);
			return (0);
		}
		i++;
	}
	return (1);
}

int	is_texture_line(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
		return (1);
	return (0);
}

int	check_map_after_newline(char *s, int start, int len)
{
	int	j;

	j = start;
	while (j < len && (s[j] == ' ' || s[j] == '\t' || s[j] == '\n'))
		j++;
	if (j < len && is_map_char(s[j]) && s[j] != ' ')
		return (1);
	return (0);
}

int	check_newline_in_map(char *s)
{
	int	i;
	int	map_started;
	int	len;

	i = -1;
	map_started = 0;
	len = ft_strlen(s);
	while (++i < len)
	{
		if (is_texture_line(&s[i]))
		{
			while (i < len && s[i] != '\n')
				i++;
			continue ;
		}
		if (is_map_char(s[i]) && s[i] != ' ')
			map_started = 1;
		if (map_started && s[i] == '\n' && i + 1 < len && s[i + 1] == '\n'
			&& check_map_after_newline(s, i + 2, len))
			return (1);
	}
	return (0);
}
