#include "../../inc/cube3d.h"

void	print_error(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (write(2, &str[i], 1) == -1)
			return ;
		i++;
	}
}