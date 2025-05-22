/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaregra <moaregra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:41:26 by moaregra          #+#    #+#             */
/*   Updated: 2025/05/22 18:40:18 by moaregra         ###   ########.fr       */
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
		if (new[i] != ' ')
			result[j++] = new[i];
		i++;
	}
	result[j] = '\0';
	return (free(new), result);
}

int	is_valid_rgb_string(const char *rgb)
{
	int	i;
	int	num_count;
	int	comma_count;
	int	digit_count;
	int	has_digit_after_comma;

	if (!rgb)
		return (0);
	i = 0;
	num_count = 0;
	comma_count = 0;
	digit_count = 0;
	has_digit_after_comma = 1;
	while (rgb[i])
	{
		if (rgb[i] >= '0' && rgb[i] <= '9')
		{
			digit_count++;
			has_digit_after_comma = 1;
			if (digit_count > 3)
				return (0);
			if (i == 0 || rgb[i - 1] == ',')
			{
				num_count++;
				digit_count = 1;
			}
		}
		else if (rgb[i] == ',')
		{
			comma_count++;
			digit_count = 0;
			has_digit_after_comma = 0;
			if (i == 0 || rgb[i + 1] == '\0')
				return (0);
		}
		else
			return (0);
		i++;
	}
	return (num_count == 3 && comma_count == 2 && has_digit_after_comma);
}

int	is_valid_rgb(int r, int g, int b)
{
	return (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255);
}

int	check_virgul(const char *str)
{
	int	i;
	int	count;
	int	len;

	if (!str)
		return (1);
	i = 0;
	count = 0;
	len = ft_strlen(str);
	while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t'))
		len--;
	if (len > 0 && str[len - 1] == ',')
		return (1);
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	return (count != 2);
}
