/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaregra <moaregra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:38:50 by moaregra          #+#    #+#             */
/*   Updated: 2025/01/22 13:17:27 by moaregra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

int	check_file_name(char *s)
{
	if (access(s, F_OK) == -1)
		return (0);
	return (1);
}
int	check_texture(t_map *map)
{
	if (access(map->no, F_OK) == -1)
		return (0);
	if (access(map->ea, F_OK) == -1)
		return (0);
	if (access(map->se, F_OK) == -1)
		return (0);
	if (access(map->we, F_OK) == -1)
		return (0);
	return (1);
}