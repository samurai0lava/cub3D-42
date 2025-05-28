/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:38:42 by moaregra          #+#    #+#             */
/*   Updated: 2025/05/26 16:16:24 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

void	parse_texture(t_map *map, char *line, char *identifier, char **dest)
{
	char	*tmp;

	(void)map;
	if (ft_strnstr(line, identifier, ft_strlen(line)))
	{
		tmp = ft_strdup(line);
		if (!tmp)
			return ;
		*dest = parse_line(tmp, identifier);
		free(tmp);
	}
}

void	fill_struct_helper(t_map *map, char **file)
{
	int	i;

	i = 0;
	while (file[i])
	{
		parse_texture(map, file[i], "NO ", &map->no);
		parse_texture(map, file[i], "SO ", &map->se);
		parse_texture(map, file[i], "EA ", &map->ea);
		parse_texture(map, file[i], "WE ", &map->we);
		parse_texture(map, file[i], "F ", &map->floor_color);
		parse_texture(map, file[i], "C ", &map->celling_color);
		i++;
	}
}

static void	handle_validation_error(char *s, char **file)
{
	free_file_resources(s, file);
	exit(1);
}


void	fill_struct(t_map *map, char *av)
{
	char	*s;
	char	**file;

	s = get_file_in_char(av);
	file = split_file(s);
	if (!validate_inputs(s, file, map))
		return ;
	if(check_newline_in_map(s) == 1)
	{
		free_file_resources(s,file);
		exit(1);
	}
	if(check_all_double(s) == 0)
	{
		free_file_resources(s, file);
		print_error("Error\nDuplicate texture identifiers found\n");
		exit(1);
	}
	if (!validate_textures(file))
		handle_validation_error(s, file);
	fill_struct_helper(map, file);
	free_file_resources(s, file);
}

void	initiliase_struct(t_map *map, char *av)
{
	fill_struct(map, av);
	if (check_texture(map) == 0)
	{
		free_map_struct(map);
		print_error(RED IVT RESET);
		exit(1);
	}
	fill_rgb(map);
}
int	is_valid_cub_path(char *path)
{
    int		len;
    int		i;

    if (!path)
        return (0);
    len = 0;
    while (path[len])
        len++;
    if (len < 4)
        return (0);
    if (path[len - 4] != '.' || path[len - 3] != 'c'
        || path[len - 2] != 'u' || path[len - 1] != 'b')
        return (0);
    i = 0;
    while (i < len)
    {
        if (path[i] == ' ')
            return (0);
        i++;
    }
    return (1);
}