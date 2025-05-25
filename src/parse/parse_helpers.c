/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaregra <moaregra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:38:53 by moaregra          #+#    #+#             */
/*   Updated: 2025/05/25 18:32:44 by moaregra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

void	free_all_lines(char **lines)
{
	int	i;

	if (!lines)
		return ;
	i = 0;
	while (lines[i])
		free(lines[i++]);
	free(lines);
}

void	*free_clean_lines(char **clean_line, int j)
{
	while (j > 0)
		free(clean_line[--j]);
	free(clean_line);
	return (NULL);
}

static int	count_valid_lines(char **all_line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (all_line[i])
	{
		if (all_line[i][0] != '\n')
			count++;
		i++;
	}
	return (count);
}

static char	**allocate_clean_array(char **all_line, int count)
{
	char	**clean_line;

	clean_line = malloc(sizeof(char *) * (count + 1));
	if (!clean_line)
		free_all_lines(all_line);
	return (clean_line);
}

char	**split_file(char *s)
{
	char	**all_line;
	char	**clean_line;
	int		i;
	int		j;
	int		count;

	if (!s || !(all_line = ft_split(s, '\n')))
		return (NULL);
	count = count_valid_lines(all_line);
	if (!(clean_line = allocate_clean_array(all_line, count)))
		return (NULL);
	i = 0;
	j = 0;
	while (all_line[i])
	{
		if (all_line[i][0] != '\n')
		{
			clean_line[j] = ft_strdup(all_line[i]);
			if (!clean_line[j++])
				return (free_clean_lines(clean_line, j), free_all_lines(all_line), NULL);
		}
		free(all_line[i++]);
	}
	clean_line[j] = NULL;
	return (free(all_line), clean_line);
}
