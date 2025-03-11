/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:25:25 by iouhssei          #+#    #+#             */
/*   Updated: 2025/03/11 03:48:16 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

#include "../../inc/cube3d.h"

int handle_mouse_move(int x, int y, t_cube *cube)
{
    static int inRecenter = 0; 
    int        dx;

    // If we *just* called mlx_mouse_move to recenter, 
    // then skip to avoid re-triggering our own event.
    if (inRecenter)
    {
        inRecenter = 0;
        cube->mouse_x = x; // update the stored mouse_x so dx=0 next time
        return (0);
    }

    // We ignore vertical look in this example:
    (void)y;

    // Compute how far the mouse moved in X relative to last known position
    dx = x - cube->mouse_x;

    // Rotate the view
    if (dx != 0)
    {
        cube->angle += dx * MOUSE_SENSITIVITY;
        cube->angle = fmod(cube->angle + 2 * PI, 2 * PI);
    }

    // If the mouse is not already in the center, recenter it.
    // This will trigger a new motion event, so we set 'inRecenter' to 1.
    if (x != WIDTH / 2)
    {
        inRecenter = 1;
        mlx_mouse_move(cube->mlx, cube->mlx_window, WIDTH / 2, HEIGHT / 2);
    }

    // Draw the new frame
    cast_away(cube);
    draw_weapon(cube);
    draw_circular_minimap(cube);
    mlx_put_image_to_window(cube->mlx, cube->mlx_window, cube->data->img, 0, 0);

    // Store the last mouse X for next time
    cube->mouse_x = x;

    return (0);
}
