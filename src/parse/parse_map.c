/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaregra <moaregra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:42:06 by moaregra          #+#    #+#             */
/*   Updated: 2025/05/06 11:00:20 by moaregra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

int	check_map_line(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != '1' && s[i] != '0' && s[i] != 'N' && s[i] != 'S'
			&& s[i] != 'E' && s[i] != 'W' && s[i] != '\t' && s[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

void	count_map_lines(char **all_file, int *lines, int *map_started)
{
	int	i;

	i = 0;
	*lines = 0;
	*map_started = 0;
	while (all_file[i])
	{
		if (check_map_line(all_file[i]) == 0)
		{
			*map_started = 1;
			(*lines)++;
		}
		else if (*map_started)
			break ;
		i++;
	}
}

void	fill_map_array(t_map *map, char **all_file, int lines)
{
	int	i;
	int	j;
	int	map_started;

	i = 0;
	j = 0;
	map_started = 0;
	map->map = malloc(sizeof(char *) * (lines + 1));
	while (all_file[i])
	{
		if (check_map_line(all_file[i]) == 0)
		{
			map_started = 1;
			map->map[j] = ft_strdup(all_file[i]);
			j++;
		}
		else if (map_started)
			break ;
		i++;
	}
	map->map[j] = NULL;
}

void	get_map_into2darray(t_map *map, char *av)
{
	int		lines;
	int		map_started;
	char	*s;
	char	**all_file;
	int		i;

		i = 0;
	s = get_file_in_char(av);
	if(s == NULL)
		return ;
	all_file = split_file(s);
	if(all_file == NULL)
		return ;
	count_map_lines(all_file, &lines, &map_started);
	fill_map_array(map, all_file, lines);
	if(check_map_last(map,all_file) == 0)
	{
		// printf("alo \n"); segfault instantly after this
		free_map_struct(map);
			while (all_file[i])
				{
					free(all_file[i]);
					i++;
				}
			free(all_file);
			free(s);
			exit(1);
	}
	while (all_file[i])
	{
		free(all_file[i]);
		i++;
	}
	free(all_file);
	free(s);
}
int find_last_line_occurance(t_map *map,char **av)
{
	char	*last_map_line = map->map[count_double_char(map->map)];
	int		i;
	i = 0;
	int biggest_index = 0;
	while(av[i])
	{
		if (ft_strncmp(av[i], last_map_line,ft_strlen(av[i])) == 0)
		{
			biggest_index = i;
		}
		i++;
	}
	return biggest_index;
}
int	check_map_last(t_map *map, char **all_file)
{
    int		i;
    int		found_last_map_line;
	
	if(map->map[0] == NULL)
		return 0;
    char	*last_map_line = map->map[count_double_char(map->map)];

    found_last_map_line = 0;
    i = 0;
	int biggest_index = find_last_line_occurance(map,all_file);
    while (all_file[i])
    {
        if (biggest_index == i)
		{
            found_last_map_line = 1;	
		}
        else if (found_last_map_line && all_file[i][0] != '\0')
        {
            write(2, "Error: Content found after map\n", 31);
            return (0);
        }
        i++;
    }
    if (!found_last_map_line)
    {
        write(2, "Error: Last map line not found in file\n", 39);
        return (0);
    }
    return (1);
}

int	count_double_char(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i - 1);
}
