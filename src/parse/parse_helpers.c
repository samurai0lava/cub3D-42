/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaregra <moaregra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:38:53 by moaregra          #+#    #+#             */
/*   Updated: 2025/03/17 15:40:21 by moaregra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

void	free_all_lines(char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
		free(lines[i++]);
	free(lines);
}

void	alloc_clean_lines(char **all_line, char ***clean_line, int count)
{
	*clean_line = malloc(sizeof(char *) * (count + 1));
	if (!(*clean_line))
	{
		free_all_lines(all_line);
		return ;
	}
}

char	**count_and_alloc_lines(char **all_line, int *count)
{
	int		i;
	char	**clean_line;

	*count = 0;
	i = 0;
	while (all_line[i])
	{
		if (all_line[i][0] != '\n')
			(*count)++;
		i++;
	}
	alloc_clean_lines(all_line, &clean_line, *count);
	return (clean_line);
}

char	**split_file(char *s)
{
	char	**all_line;
	char	**clean_line;
	int		i;
	int		j;
	int		count;

	if (!s)
		return (NULL);
	all_line = ft_split(s, '\n');
	if (!all_line)
		return (NULL);
	clean_line = count_and_alloc_lines(all_line, &count);
	if (!clean_line)
		return (NULL);
	i = 0;
	j = 0;
	while (all_line[i])
	{
		if (all_line[i][0] != '\n')
		{
			clean_line[j] = ft_strdup(all_line[i]);
			if (!clean_line[j++])
				return (free_clean_lines(clean_line, j), NULL);
		}
		free(all_line[i++]);
	}
	clean_line[j] = NULL;
	free(all_line);
	return (clean_line);
}

void	*free_clean_lines(char **clean_line, int j)
{
	while (j > 0)
		free(clean_line[--j]);
	free(clean_line);
	return (NULL);
}
