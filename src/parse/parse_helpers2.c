/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:41:26 by moaregra          #+#    #+#             */
/*   Updated: 2025/05/21 23:33:21 by iouhssei         ###   ########.fr       */
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

int	is_valid_rgb_string(const char *rgb)
{
	int	i;
	int	num_count;
	int	comma_count;
	int	digit_count;
	int	has_digit_after_comma;

	if (!rgb)
		return (0);
	i = 0;
	num_count = 0;
	comma_count = 0;
	digit_count = 0;
	has_digit_after_comma = 1;
	while (rgb[i])
	{
		if (rgb[i] >= '0' && rgb[i] <= '9')
		{
			digit_count++;
			has_digit_after_comma = 1;
			if (digit_count > 3)
				return (0);
			if (i == 0 || rgb[i - 1] == ',')
			{
				num_count++;
				digit_count = 1;
			}
		}
		else if (rgb[i] == ',')
		{
			comma_count++;
			digit_count = 0;
			has_digit_after_comma = 0;
			if (i == 0 || rgb[i + 1] == '\0')
				return (0);
		}
		else
			return (0);
		i++;
	}
	return (num_count == 3 && comma_count == 2 && has_digit_after_comma);
}

int	is_valid_rgb(int r, int g, int b)
{
	return (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255);
}

int	check_virgul(const char *str)
{
	int	i;
	int	count;
	int	len;

	if (!str)
		return (1);
	i = 0;
	count = 0;
	len = ft_strlen(str);
	while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t'))
		len--;
	if (len > 0 && str[len - 1] == ',')
		return (1);
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	return (count != 2);
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

	if (check_virgul(map->floor_color) == 0
		&& check_virgul(map->celling_color) == 0)
	{
		if (!is_valid_rgb_string(map->floor_color)
			|| !is_valid_rgb_string(map->celling_color))
		{
			print_error(RED INVF_RGB RESET);
			free_map_struct(map);
			exit(EXIT_FAILURE);
		}
		floor_rgb = ft_split(map->floor_color, ',');
		celling_rgb = ft_split(map->celling_color, ',');
		if (!floor_rgb || !celling_rgb || !floor_rgb[0] || !floor_rgb[1]
			|| !floor_rgb[2] || !celling_rgb[0] || !celling_rgb[1]
			|| !celling_rgb[2])
		{
			free_rgb_arrays(floor_rgb, celling_rgb);
			print_error(RED MEM_RGB RESET);
			free_map_struct(map);
			exit(EXIT_FAILURE);
		}
		map->f_rgb.r = ft_atoi(floor_rgb[0]);
		map->f_rgb.g = ft_atoi(floor_rgb[1]);
		map->f_rgb.b = ft_atoi(floor_rgb[2]);
		map->c_rgb.r = ft_atoi(celling_rgb[0]);
		map->c_rgb.g = ft_atoi(celling_rgb[1]);
		map->c_rgb.b = ft_atoi(celling_rgb[2]);
		if (check_rgbs(map))
		{
			free_rgb_arrays(floor_rgb, celling_rgb);
			print_error(RED RGB_VALUES RESET);
			free_map_struct(map);
			exit(EXIT_FAILURE);
		}
		free_rgb_arrays(floor_rgb, celling_rgb);
	}
	else
	{
		print_error(RED INV_RGB RESET);
		free_map_struct(map);
		exit(EXIT_FAILURE);
	}
}

int	check_rgbs(t_map *map)
{
	if (!is_valid_rgb(map->f_rgb.r, map->f_rgb.g, map->f_rgb.b))
		return (1);
	if (!is_valid_rgb(map->c_rgb.r, map->c_rgb.g, map->c_rgb.b))
		return (1);
	return (0);
}
