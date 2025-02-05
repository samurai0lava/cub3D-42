/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:44:41 by iouhssei          #+#    #+#             */
/*   Updated: 2025/02/05 16:19:27 by iouhssei         ###   ########.fr       */
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
# define S_RES 1000
# define S_TEX 64
# define MAP_SCALE 0.5
# define TILE_SIZE (S_TEX * MAP_SCALE)
# define RAY_STEP 0.1

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
	int						width;
	int						height;
}							t_data;

typedef struct s_cube
{
	void					*mlx;
	void					*mlx_window;
	t_garbage_collector		*gc;
	t_data					*data;
	t_data					texture[4];
	int						map[10][10];
	int						p_x;
	int						p_y;
	double					angle;
}							t_cube;

typedef struct s_rgb
{
	int						r;
	int						g;
	int						b;
	char					*rgb_in_hex;
}							t_rgb;

typedef struct s_map
{
	char					**map;
	char					*se;
	char					*no;
	char					*we;
	char					*ea;
	char					*floor_color;
	char					*celling_color;
	int						is_valid;
	int						map_height;
	int						map_width;
	int						x;
	int						y;
	t_rgb					f_rgb;
	t_rgb					c_rgb;
}							t_map;

int							count_till_newline(char *s);
int							get_bigger_mapline(char **s);
int							get_line_of_biggervalue(char **s);
int							check_map(t_map *map);
void						print_2d(char **s);
int							check_line(t_map *map);
char						**split_file(char *s);
int							check_file_name(char *s);
void						fill_struct(t_map *map, char *av);
int							check_texture(t_map *map);
char						*get_file_in_char(char *av);
void						initiliase_struct(t_map *map, char *av);
void						get_map_into2darray(t_map *map, char *av);
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
void						draw_line(t_cube *cube, double angle, int length,
								int color);
void						cast_away_minirays(t_cube *cube);
void						draw_filled_circle(t_cube *cube, int radius,
								int color);
void						draw_map(t_data *data, int map[10][10]);
void						clean_screen(t_data *data);
void						init_textures(t_cube *cube);
int							color_shading(int color, double distance);
int							get_texture_pixel(t_data *texture, int x, int y);
double						normalize_angle(double angle);
void						cast_rays(t_cube *cube);

#endif
