#include "../../inc/cube3d.h"

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
