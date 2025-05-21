/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_double_texture.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:41:45 by iouhssei          #+#    #+#             */
/*   Updated: 2025/05/20 14:41:46 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

int	count_occurrences(char **lines, const char *target)
{
    int count;
    int i;

    count = 0;
    i = 0;
    while (lines[i] != NULL)
    {
        if (ft_strncmp(lines[i], target, strlen(target)) == 0 &&
            (lines[i][strlen(target)] == ' ' || lines[i][strlen(target)] == '\t'))
        {
            count++;
        }
        i++;
    }
    return (count);
}

int	validate_textures(char **lines)
{
    const char	*required_textures[] = {"NO", "SO", "WE", "EA","F","C"};
    int			num_textures;
    int			i;
    int			count;


    num_textures = 6;
    i = 0;
    while (i < num_textures)
    {
        count = count_occurrences(lines, required_textures[i]);
        if (count != 1)
        {
            print_error("Error\nDuplicate or missing texture");
            return (0);
        }
        i++;
    }
    return (1);
}