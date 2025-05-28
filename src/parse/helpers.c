/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaregra <moaregra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 19:51:05 by moaregra          #+#    #+#             */
/*   Updated: 2025/05/28 20:00:10 by moaregra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

int	check_double(char *s, char *to_find)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strnstr(s, to_find, ft_strlen(s));
	if (tmp == NULL)
		return (0);
	if (tmp != NULL)
	{
		if (tmp + 1 == NULL)
			return (0);
		tmp2 = ft_strnstr(tmp + 1, to_find, ft_strlen(s));
		if (tmp2 != NULL)
			return (0);
	}
	return (1);
}

int	check_all_double(char *s)
{
	char	*d[6];
	int		i;

	i = 0;
	d[0] = "NO";
	d[1] = "SO";
	d[2] = "WE";
	d[3] = "EA";
	d[4] = "F";
	d[5] = "C";
	while (i < 6)
	{
		if (check_double(s, d[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_cub_path(char *path)
{
	int	len;
	int	i;

	if (!path)
		return (0);
	len = 0;
	while (path[len])
		len++;
	if (len < 4)
		return (0);
	if (path[len - 4] != '.' || path[len - 3] != 'c' || path[len - 2] != 'u'
		|| path[len - 1] != 'b')
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
