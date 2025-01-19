/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:44:41 by iouhssei          #+#    #+#             */
/*   Updated: 2025/01/19 16:06:03 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

//----------------------------==----------//
//-----------MACROS-------====------------//
//--------------==------------------------//

// colors

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define ORANGE "\033[0;36m"
# define RESET "\033[0m"

// keys

# define ESC 65307
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define UP 126
# define DOWN 125
# define PI 3.14159265359
# define M_PI_2 1.57079632679489661923
# define LEFT_KEY 65361
# define RIGHT_KEY 65363
# define S_RES 800
# define FOV PI / 3

// Struct (raycaster)
typedef struct s_garbage_node
{
	void					*ptr;
	struct s_garbage_node	*next;
}							t_garbage_node;

typedef struct s_garbage_collector
{
	t_garbage_node			*head;
}							t_garbage_collector;

typedef struct s_data
{
	void					*img;
	char					*addr;
	int						bits_per_pixel;
	int						line_length;
	int						endian;
}							t_data;

typedef struct s_cube
{
	void					*mlx;
	void					*mlx_window;
	t_garbage_collector		*gc;
	t_data					*data;
	int						map[10][10];
	int						p_x;
	int						p_y;
	double					angle;
}							t_cube;

// FUNCTIONS :

//----INITIALIZATION-==---------------//
//------------------=--==-------------//
//----PARSING------------==-----------//
//-------------------------===--------//

//--------------------------------------//
//----RAY-CASTER------------------------//
//--------------------------------------//
//----DRAWING---------------------------//

void						print_error(char *str);
void						init_mlx(t_cube *cube, t_data *data);
t_garbage_collector			*init_garbage_collector(void);
void						add_garbage(t_garbage_collector *gc, void *ptr);
void						*free_all(t_garbage_collector *gc);
void						*tracked_malloc(t_garbage_collector *gc,
								size_t size);
void						my_mlx_pixel_put(t_data *data, int x, int y,
								int color);
int							handle_keypress(int keycode, t_cube *cube);
void						cast_away(t_cube *cube);
void						draw_line(t_cube *cube, int x1, int y1,
								double angle, int length, int color);
void						draw_mini_map(t_cube *cube);
void						cast_away_minirays(t_cube *cube);
#endif
