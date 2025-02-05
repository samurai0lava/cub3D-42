/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:38:48 by moaregra          #+#    #+#             */
/*   Updated: 2025/02/05 16:19:36 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../inc/cube3d.h"

// void	print_2d(char **s)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		printf("%s\n", s[i]);
// 		i++;
// 	}
// }

// int main(int ac, char **av)
// {
//     t_map map;

//     // Initialize the structure to zero
//     ft_memset(&map, 0, sizeof(t_map));

//     if (ac != 2)
//     {
//         if (write(2, "invalid number of parametres\n", 30) < 0)
//             return (1);
//         return (1);
//     }

//     if (check_file_name(av[1]) == 0)
//     {
//         if (write(2, "file invalid\n", 14) < 0)
//             return (1);
//         return (1);
//     }

//     initiliase_struct(&map, av[1]);
//     printf("%s\n", map.no);
//     printf("%s\n", map.se);
//     printf("%s\n", map.ea);
//     printf("%s\n", map.we);
//     printf("%d\n", map.c_rgb.r);
//     printf("%d\n", map.c_rgb.g);
//     printf("%d\n", map.c_rgb.b);

//     get_map_into2darray(&map, av[1]);
//     print_2d(map.map);

//     if (check_map(&map) == 0)
//     {
//         if (write(2, "invalid map\n", 13) < 0)
//             return (1);
//         return (1);
//     }
//     else
//     {
//         if (write(2, "valid map\n", 11) < 0)
//             return (1);
//         return (1);
//     }

//     return (0);
// }