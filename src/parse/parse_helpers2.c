/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaregra <moaregra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:41:26 by moaregra          #+#    #+#             */
/*   Updated: 2025/05/25 18:43:41 by moaregra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

int	is_valid_rgb_string(const char *rgb)
{
	int	i;
	int	digit_cnt;
	int	num_cnt;
	int	comma_cnt;

	if (!rgb || !rgb[0])
		return (0);
	i = 0;
	digit_cnt = 0;
	num_cnt = 0;
	comma_cnt = 0;
	while (rgb[i])
	{
		if (rgb[i] == ',')
			comma_cnt++;
		if (!validate_char(rgb[i], rgb[i + 1], &digit_cnt, &num_cnt))
			return (0);
		i++;
	}
	return (num_cnt == 3 && comma_cnt == 2 && digit_cnt > 0);
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
