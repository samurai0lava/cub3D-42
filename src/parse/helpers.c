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
	char	*d[7] = {"NO", "SO", "WE", "EA", "F", "C", NULL};
	int		i;

	i = 0;
	while (d[i])
	{
		if (check_double(s, d[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

///////////////////////////////////////////////