/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:44:29 by iouhssei          #+#    #+#             */
/*   Updated: 2025/03/23 04:16:32 by iouhssei         ###   ########.fr       */
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
	cube->angle = 0;
	cube->weapon.orig_height = S_TEX;
	cube->weapon.orig_width = S_TEX;
	cube->minimap_radius = 0;
	cube->minimap_center_x = 0;
	cube->minimap_center_y = 0;
	cube->minimap_scale = 1.0;
	cube->player_dot_size = 3;
	cube->p_x = (cube->map.x) * S_TEX;
	cube->p_y = (cube->map.y) * S_TEX;
	// printf("cube->p_x :%f\n", cube->p_x);
	// printf("cube->p_y : %f\n", cube->p_y);
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

int	handle_errors(int err_code)
{
	if (err_code == 1)
		return (write(2, "invalid number of parametres\n", 30), 1);
	else if (err_code == 2)
		return (write(2, "file invalid\n", 14), 1);
	else if (err_code == 3)
		return (write(2, "invalid rgbs\n", 14), 1);
	else if (err_code == 4)
		return (write(2, "invalid map\n", 13), 1);
	return (1);
}

void	print_map_info(t_map *m)
{
	int	i;

	printf("----- Map 2D Array -----\n");
	if (m->map)
	{
		i = 0;
		while (m->map[i])
		{
			printf("%s\n", m->map[i]);
			i++;
		}
	}
	else
	{
		printf("  (No map data)\n");
	}
	// Print the individual texture paths / directions
	printf("\n----- Texture Paths -----\n");
	printf("SE: %s\n", m->se ? m->se : "(null)");
	printf("NO: %s\n", m->no ? m->no : "(null)");
	printf("WE: %s\n", m->we ? m->we : "(null)");
	printf("EA: %s\n", m->ea ? m->ea : "(null)");
	// Floor & ceiling
	printf("\n----- Colors -----\n");
	printf("Floor color string:   %s\n",
		m->floor_color ? m->floor_color : "(null)");
	printf("Ceiling color string: %s\n",
		m->celling_color ? m->celling_color : "(null)");
	printf("Floor RGB:   R=%d, G=%d, B=%d\n", m->f_rgb.r, m->f_rgb.g,
		m->f_rgb.b);
	printf("Ceiling RGB: R=%d, G=%d, B=%d\n", m->c_rgb.r, m->c_rgb.g,
		m->c_rgb.b);
	// Print the rest
	printf("\n----- Map Metadata -----\n");
	printf("is_valid:   %d\n", m->is_valid);
	printf("x:          %f\n", m->x);
	printf("y:          %f\n", m->y);
	printf("------------------------------------\n");
}

static int	parse_map(t_map *map, int ac, char **av)
{
	ft_memset(map, 0, sizeof(t_map));
	if (ac != 2)
		return (handle_errors(1));
	if (check_file_name(av[1]) == 0)
		return (handle_errors(2));
	initiliase_struct(map, av[1]);
	get_map_into2darray(map, av[1]);
	count_w_h(map);
	get_x_y(map);
	check_direction(map);
	if (check_rgbs(map) == 1)
	{
		free_map_struct(map);
		return (handle_errors(3));
	}
	else
		write(1, "valid rgbs\n", 12);
	if (check_map(map) == 0)
	{
		free_map_struct(map);
		return (handle_errors(4));
	}
	else
		write(2, "valid map\n", 11);
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
	{
		perror("malloc");
		return (-1);
	}
	cube->gc = init_garbage_collector();
	if (!cube->gc)
	{
		free(cube);
		return (-1);
	}
	data = tracked_malloc(cube->gc, sizeof(t_data));
	if (data == NULL)
	{
		free_all(cube->gc);
		return (1);
	}
	cube->data = data;
	cube->map = map;
	init_cube(cube, data);
	print_map_info(&cube->map);
	init_mlx(cube, data);
	free_map_struct(&cube->map);
	free_all(cube->gc);
	free(cube);
	return (0);
}
