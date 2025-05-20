/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:44:29 by iouhssei          #+#    #+#             */
/*   Updated: 2025/05/20 14:47:33 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube3d.h"

void	init_cube(t_cube *cube, t_data *data)
{
	cube->mlx = NULL;
	cube->mlx_window = NULL;
	data->img = NULL;
	data->addr = NULL;
	data->bits_per_pixel = 0;
	data->endian = 0;
	data->line_length = 0;
	cube->angle = cube->map.start_angle;
	cube->weapon.orig_height = S_TEX;
	cube->weapon.orig_width = S_TEX;
	cube->minimap_radius = 0;
	cube->minimap_center_x = 0;
	cube->minimap_center_y = 0;
	cube->minimap_scale = 1.0;
	cube->player_dot_size = 3;
	cube->p_x = (cube->map.x * S_TEX) + (S_TEX / 2);
	cube->p_y = (cube->map.y * S_TEX) + (S_TEX / 2);
	cube->keys.w = 0;
	cube->keys.s = 0;
	cube->keys.d = 0;
	cube->keys.a = 0;
	cube->keys.right = 0;
	cube->keys.left = 0;
	cube->frame = NULL;
}

void	free_map_textures(t_map *map)
{
	if (map->no)
		free(map->no);
	if (map->se)
		free(map->se);
	if (map->ea)
		free(map->ea);
	if (map->we)
		free(map->we);
	if (map->floor_color)
		free(map->floor_color);
	if (map->celling_color)
		free(map->celling_color);
}

void	free_map_struct(t_map *map)
{
	int	i;

	if (map->map)
	{
		i = 0;
		while (map->map[i])
			free(map->map[i++]);
		free(map->map);
	}
	free_map_textures(map);
}

static int	parse_map(t_map *map, int ac, char **av)
{
	ft_memset(map, 0, sizeof(t_map));
	if (ac != 2)
		return (1);
	if (check_file_name(av[1]) == 0)
	{
		print_error("Error\nInvalid file name\n");
		return (1);
	}
	initiliase_struct(map, av[1]);
	get_map_into2darray(map, av[1]);
	get_x_y(map);
	count_w_h(map);
	check_direction(map);
	if (check_rgbs(map) == 1)
	{
		free_map_struct(map);
		print_error("Error\nInvalid RGB\n");
		return (1);
	}
	if (check_map(map) == 0)
	{
		free_map_struct(map);
		print_error("Error\nMap is invalid\n");
		return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_map	map;
	t_cube	*cube;
	t_data	*data;

	if (parse_map(&map, ac, av) != 0)
		return (1);
	cube = (t_cube *)malloc(sizeof(t_cube));
	if (!cube)
		return (perror("malloc"), -1);
	cube->gc = init_garbage_collector();
	if (!cube->gc)
		return (free(cube), -1);
	data = tracked_malloc(cube->gc, sizeof(t_data));
	if (data == NULL)
		return (free_all(cube->gc), 1);
	cube->data = data;
	cube->map = map;
	init_cube(cube, data);
	init_mlx(cube, data);
	free_map_struct(&cube->map);
	free_all(cube->gc);
	free(cube);
	return (0);
}
