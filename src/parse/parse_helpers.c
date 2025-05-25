/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:38:53 by moaregra          #+#    #+#             */
/*   Updated: 2025/05/25 19:47:09 by iouhssei         ###   ########.fr       */
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
	t_split	spl;

	spl.all_line = ft_split(s, '\n');
	if (!s || !spl.all_line)
		return (NULL);
	spl.count = count_valid_lines(spl.all_line);
	spl.clean_line = allocate_clean_array(spl.all_line, spl.count);
	if (!(spl.clean_line))
		return (NULL);
	spl.i = 0;
	spl.j = 0;
	while (spl.all_line[spl.i])
	{
		if (spl.all_line[spl.i][0] != '\n')
		{
			spl.clean_line[spl.j] = ft_strdup(spl.all_line[spl.i]);
			if (!spl.clean_line[spl.j++])
				return (free_clean_lines(spl.clean_line, spl.j),
					free_all_lines(spl.all_line), NULL);
		}
		free(spl.all_line[spl.i++]);
	}
	spl.clean_line[spl.j] = NULL;
	return (free(spl.all_line), spl.clean_line);
}
