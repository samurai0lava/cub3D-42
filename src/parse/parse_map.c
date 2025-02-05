/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaregra <moaregra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:42:06 by moaregra          #+#    #+#             */
/*   Updated: 2025/01/26 19:02:41 by moaregra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

int check_map_line(char *s)
{
    int i = 0;
    while (s[i] != '\0')
    {
        if (s[i] != '1' && s[i] != '0' && s[i] != 'N' && s[i] != 'S'
            && s[i] != 'E' && s[i] != 'W' && s[i] != '\t' && s[i] != ' ')
            return (1);
        i++;
    }
    return (0);
}
void	get_map_into2darray(t_map *map, char *av)
{
	int		lines;
	int		map_started;
	char	*s;
	char	**all_file;
	int		i;
	int		j;

	lines = 0;
	map_started = 0;
	s = get_file_in_char(av);
	all_file = split_file(s);
	i = 0;
	j = 0;
	while (all_file[i])
	{
		if (check_map_line(all_file[i]) == 0)
		{
			map_started = 1;
			lines++;
		}
		else if (map_started)
			break ;
		i++;
	}
	map->map = malloc(sizeof(char *) * (lines + 1));
	i = 0;
	map_started = 0;
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
	i = 0;
	while (all_file[i])
	{
		free(all_file[i]);
		i++;
	}
	free(all_file);
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
int	check_borders(char *s)
{
	int	i;
	int last_valid;

	i = 0;
	// Skip leading spaces
	while(s[i] && (s[i] == ' ' || s[i] == '\t'))
		i++;
	
	// Find last valid character (not space or tab)
	last_valid = ft_strlen(s) - 1;
	while(last_valid >= 0 && (s[last_valid] == ' ' || s[last_valid] == '\t'))
		last_valid--;
	
	// Empty line check
	if (last_valid < 0)
		return (1);
		
	// Check first and last valid characters are '1'
	if (s[i] != '1' || s[last_valid] != '1')
		return (1);
		
	return (0);
}
int	check_top_and_bottom(char *s)
{
	int	i;

	i = 0;
	while(s[i] && (s[i] == ' ' || s[i] == '\t' ))
		i++;
	while (s[i])
	{
		if (s[i] != '1')
			return (1);
		i++;
	}
	return (0);
}

int check_map_steps(t_map *map)
{
    int i;
    int current_len;
    int prev_len;
    
    i = count_double_char(map->map); // Get last index
    
    while (i > 0) // Start from bottom, go up
    {
        current_len = ft_strlen(map->map[i]);
        prev_len = ft_strlen(map->map[i - 1]);
        
        // Skip trailing spaces when counting length
        while (current_len > 0 && (map->map[i][current_len - 1] == ' ' || map->map[i][current_len - 1] == '\t'))
            current_len--;
        while (prev_len > 0 && (map->map[i - 1][prev_len - 1] == ' ' || map->map[i - 1][prev_len - 1] == '\t'))
            prev_len--;
            
        // If previous line is longer than current
        if (prev_len > current_len)
        {
            // Check if all characters beyond current_len in prev line are '1's
            int j = current_len;
            while (j < prev_len)
            {
                if (map->map[i - 1][j] != '1')
                    return (0); // Invalid map - found an opening
                j++;
            }
        }
        i--;
    }
    return (1);
}
// Modify your existing check_map function to include this new check
int check_map(t_map *map)
{
    int players = 0;
    int size = count_double_char(map->map);
    int i = 0;
    int j;

    // First check steps
    if (!check_map_steps(map))
        return (0);

    // Check top and bottom rows are all walls
    if (check_top_and_bottom(map->map[0]) == 1 || 
        check_top_and_bottom(map->map[size]) == 1)
        return (0);
        
    // Rest of your existing validation...
    while (map->map[i])
    {
        if (check_borders(map->map[i]) == 1)
            return (0);

        j = 0;
        while (map->map[i][j])
        {
            char c = map->map[i][j];
            if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
            {
                players++;
                if (i == 0 || i == size || j == 0 || 
                    map->map[i - 1][j] == ' ' || map->map[i + 1][j] == ' ' ||
                    map->map[i][j - 1] == ' ' || map->map[i][j + 1] == ' ')
                    return (0);
            }
            if (c == '0')
            {
                if (i == 0 || i == size || j == 0 || 
                    map->map[i-1][j] == ' ' || map->map[i+1][j] == ' ' ||
                    map->map[i][j-1] == ' ' || map->map[i][j+1] == ' ')
                    return (0);
            }
            j++;
        }
        i++;
    }

    if (players != 1)
        return (0);

    return (1);
}