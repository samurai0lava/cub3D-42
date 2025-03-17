/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaregra <moaregra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:38:42 by moaregra          #+#    #+#             */
/*   Updated: 2025/03/17 15:40:26 by moaregra         ###   ########.fr       */
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

void	fill_struct(t_map *map, char *av)
{
	char	*s;
	char	**file;
	int		i;

	s = get_file_in_char(av);
	file = split_file(s);
	i = 0;
	if (!s || !file || !map)
		return ;
	fill_struct_helper(map, file);
	i = 0;
	while (file[i])
	{
		free(file[i]);
		i++;
	}
	free(file);
	free(s);
}

void	initiliase_struct(t_map *map, char *av)
{
	fill_struct(map, av);
	fill_rgb(map);
}
