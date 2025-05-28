/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:39:54 by moaregra          #+#    #+#             */
/*   Updated: 2025/05/28 14:26:49 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

char	*parse_line(char *s, char *to_trim)
{
	char	*new;
	char	*result;
	int		len;
	int		i;
	int		j;

	new = ft_strtrim(s, to_trim);
	i = 0;
	j = 0;
	if (!new)
		return (NULL);
	len = ft_strlen(new);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (free(new), NULL);
	while (new[i])
	{
		result[j++] = new[i];
		i++;
	}
	result[j] = '\0';
	return (free(new), result);
}

int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int	validate_char(char c, char next, int *digit_cnt, int *num_cnt)
{
	if (is_digit(c))
	{
		(*digit_cnt)++;
		if (*digit_cnt > 3)
			return (0);
		if (*digit_cnt == 1)
			(*num_cnt)++;
	}
	else if (c == ',')
	{
		if (*digit_cnt == 0 || !is_digit(next))
			return (0);
		*digit_cnt = 0;
	}
	else
		return (0);
	return (1);
}

void	free_file_resources(char *s, char **file)
{
	int	i;

	i = 0;
	if (file)
	{
		while (file[i])
			free(file[i++]);
		free(file);
	}
	if (s)
		free(s);
}

int	validate_inputs(char *s, char **file, t_map *map)
{
	if (!s)
		return (0);
	if (!file)
	{
		free(s);
		return (0);
	}
	if (!map)
	{
		free_file_resources(s, file);
		return (0);
	}
	return (1);
}
