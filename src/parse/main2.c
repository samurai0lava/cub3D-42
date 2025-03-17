/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaregra <moaregra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:38:48 by moaregra          #+#    #+#             */
/*   Updated: 2025/03/17 15:18:23 by moaregra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

void	print_2d(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		printf("%s\n", s[i]);
		i++;
	}
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

int	main(int ac, char **av)
{
	t_map	map;

	ft_memset(&map, 0, sizeof(t_map));
	if (ac != 2)
		return (handle_errors(1));
	if (check_file_name(av[1]) == 0)
		return (handle_errors(2));
	initiliase_struct(&map, av[1]);
	get_map_into2darray(&map, av[1]);
	if (check_rgbs(&map) == 1)
	{
		free_map_struct(&map);
		return (handle_errors(3));
	}
	else
		write(1, "valid rgbs\n", 12);
	if (check_map(&map) == 0)
	{
		free_map_struct(&map);
		return (handle_errors(4));
	}
	else
		write(2, "valid map\n", 11);
	free_map_struct(&map);
	return (0);
}
