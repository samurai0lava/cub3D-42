/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper_3_complete.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:33:45 by moaregra          #+#    #+#             */
/*   Updated: 2025/05/25 22:02:05 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

void	free_rgb_arrays(char **floor_rgb, char **ceiling_rgb)
{
	int	i;

	if (floor_rgb)
	{
		i = 0;
		while (floor_rgb[i])
			free(floor_rgb[i++]);
		free(floor_rgb);
	}
	if (ceiling_rgb)
	{
		i = 0;
		while (ceiling_rgb[i])
			free(ceiling_rgb[i++]);
		free(ceiling_rgb);
	}
}

void	handle_error_and_exit(t_map *map, char *msg, char **f_rgb, char **c_rgb)
{
	free_rgb_arrays(f_rgb, c_rgb);
	print_error(msg);
	free_map_struct(map);
	exit(EXIT_FAILURE);
}

int	validate_rgb_strings(t_map *map)
{
	if (check_virgul(map->floor_color) != 0
		|| check_virgul(map->celling_color) != 0)
		return (0);
	if (!is_valid_rgb_string(map->floor_color)
		|| !is_valid_rgb_string(map->celling_color))
		return (0);
	return (1);
}
