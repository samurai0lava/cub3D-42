/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaregra <moaregra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:41:26 by moaregra          #+#    #+#             */
/*   Updated: 2025/03/17 15:41:31 by moaregra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

char	*parse_line(char *s, char *to_trim)
{
	char	*new;
	char	*result;
	int		len;
	int		i;
	int		j;

	new = ft_strtrim(s, to_trim);
	i = 0;
	j = 0;
	if (!new)
		return (NULL);
	len = ft_strlen(new);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
	{
		free(new);
		return (NULL);
	}
	while (new[i])
	{
		if (new[i] != ' ')
			result[j++] = new[i];
		i++;
	}
	result[j] = '\0';
	free(new);
	return (result);
}

void	free_rgb_arrays(char **floor_rgb, char **celling_rgb)
{
	int	i;

	i = 0;
	while (floor_rgb[i])
		free(floor_rgb[i++]);
	free(floor_rgb);
	i = 0;
	while (celling_rgb[i])
		free(celling_rgb[i++]);
	free(celling_rgb);
}

void	fill_rgb(t_map *map)
{
	char	**floor_rgb;
	char	**celling_rgb;

	if (check_virgul(map->celling_color) == 0
		&& check_virgul(map->floor_color) == 0)
	{
		floor_rgb = ft_split(map->floor_color, ',');
		celling_rgb = ft_split(map->celling_color, ',');
		map->f_rgb.r = ft_atoi(floor_rgb[0]);
		map->f_rgb.g = ft_atoi(floor_rgb[1]);
		map->f_rgb.b = ft_atoi(floor_rgb[2]);
		map->c_rgb.r = ft_atoi(celling_rgb[0]);
		map->c_rgb.g = ft_atoi(celling_rgb[1]);
		map->c_rgb.b = ft_atoi(celling_rgb[2]);
		free_rgb_arrays(floor_rgb, celling_rgb);
	}
}

int	is_valid_rgb(int r, int g, int b)
{
	return (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255);
}

int	check_rgbs(t_map *map)
{
	if (!is_valid_rgb(map->f_rgb.r, map->f_rgb.g, map->f_rgb.b))
		return (1);
	if (!is_valid_rgb(map->c_rgb.r, map->c_rgb.g, map->c_rgb.b))
		return (1);
	return (0);
}
