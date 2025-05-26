/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper_2_complete.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaregra <moaregra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:22:36 by moaregra          #+#    #+#             */
/*   Updated: 2025/05/25 18:34:23 by moaregra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

static int	validate_split_arrays(char **floor_rgb, char **celling_rgb)
{
	if (!floor_rgb || !celling_rgb)
		return (0);
	if (!floor_rgb[0] || !floor_rgb[1] || !floor_rgb[2])
		return (0);
	if (!celling_rgb[0] || !celling_rgb[1] || !celling_rgb[2])
		return (0);
	return (1);
}

static void	assign_rgb_values(t_map *map, char **f_rgb, char **c_rgb)
{
	map->f_rgb.r = ft_atoi(f_rgb[0]);
	map->f_rgb.g = ft_atoi(f_rgb[1]);
	map->f_rgb.b = ft_atoi(f_rgb[2]);
	map->c_rgb.r = ft_atoi(c_rgb[0]);
	map->c_rgb.g = ft_atoi(c_rgb[1]);
	map->c_rgb.b = ft_atoi(c_rgb[2]);
}

void	fill_rgb(t_map *map)
{
	char	**floor_rgb;
	char	**celling_rgb;

	if (!validate_rgb_strings(map))
		handle_error_and_exit(map, RED INV_RGB RESET, NULL, NULL);
	floor_rgb = ft_split(map->floor_color, ',');
	celling_rgb = ft_split(map->celling_color, ',');
	if (!validate_split_arrays(floor_rgb, celling_rgb))
		handle_error_and_exit(map, RED MEM_RGB RESET, floor_rgb, celling_rgb);
	assign_rgb_values(map, floor_rgb, celling_rgb);
	if (check_rgbs(map))
		handle_error_and_exit(map, RED RGB_VALUES RESET, floor_rgb,
			celling_rgb);
	free_rgb_arrays(floor_rgb, celling_rgb);
}

int	check_rgbs(t_map *map)
{
	if (!is_valid_rgb(map->f_rgb.r, map->f_rgb.g, map->f_rgb.b))
		return (1);
	if (!is_valid_rgb(map->c_rgb.r, map->c_rgb.g, map->c_rgb.b))
		return (1);
	return (0);
}
