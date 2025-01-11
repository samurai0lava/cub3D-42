/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:44:29 by iouhssei          #+#    #+#             */
/*   Updated: 2025/01/11 16:21:15 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

void init_cube(t_cube *cube)
{
    cube->gc = init_garbage_collector();
    if(cube->gc)
        return ;
    cube->mlx = NULL;
    cube->mlx_window = NULL;
}

int main()
{
    t_cube *cube;

    cube = (t_cube *)tracked_malloc(cube->gc, sizeof(t_cube));
    if(!cube)
    {
        print_error(RED "Failed malloc\n" RESET);
        return (-1);
    }
    init_cube(cube);
    init_mlx(cube);
    return (0);
}
