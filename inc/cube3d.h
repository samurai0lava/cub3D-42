/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:44:41 by iouhssei          #+#    #+#             */
/*   Updated: 2025/03/11 03:27:54 by iouhssei         ###   ########.fr       */
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
# define T_PI 6.28318530718
# define LEFT_KEY 65361
# define RIGHT_KEY 65363
# define S_RES 400
# define WIDTH 800
# define HEIGHT 800
# define S_TEX 64
# define MAP_SCALE 0.5
# define TILE_SIZE (S_TEX * MAP_SCALE)
# define RAY_STEP 0.1
# define MINIMAP_RADIUS 80
# define MINIMAP_X (MINIMAP_RADIUS + 10)
# define MINIMAP_Y (MINIMAP_RADIUS + HEIGHT - 180)
# define PLAYER_DOT_SIZE 3
# define MINIMAP_SCALE 3
# define FRAME_DELAY 3
# define MIN_DISTANCE 0.5
# define MAX_DISTANCE 1000.0
# define MOUSE_SENSITIVITY 0.001

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

typedef struct s_weapon
{
	t_data					texture[6];
	int						orig_width;
	int						orig_height;
	int						scaled_width;
	int						scaled_height;
	int						pos_x;
	int						pos_y;
}							t_weapon;

typedef struct s_bar
{
	t_data					texture;
	int						orig_width;
	int						orig_height;
	int						scaled_width;
	int						scaled_height;
	int						pos_x;
	int						pos_y;
}							t_bar;

typedef struct s_enemie
{
	t_data					texture;
	int						orig_width;
	int						orig_height;
	int						scaled_width;
	int						scaled_height;
	int						pos_x;
	int						pos_y;
}							t_enemie;

typedef struct s_cube
{
	void					*mlx;
	void					*mlx_window;
	t_garbage_collector		*gc;
	t_data					*data;
	t_data					texture[4];
	int						map[30][30];
	int						p_x;
	int						p_y;
	double					angle;
	int						move;
	int						start_y;
	int						end_y;
	t_weapon				weapon;
	t_bar					bar;
	t_enemie				enemie;
	int						num_rays;
	double					angle_step;
	double					ray_step;
	double					start_angle;
	t_list					*frame;
	t_list					*current_frame;
	int						mouse_x;
	int						mouse_y;
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
void						draw_map(t_data *data, int map[30][30]);
void						clean_screen(t_data *data);
void						init_textures(t_cube *cube);
int							color_shading(int color, double distance);
int							get_texture_pixel(t_data *texture, int x, int y);
void						draw_vertical_line(t_cube *cube, int x,
								int wall_height, int color);
void						draw_floor(t_cube *cube, int y, int x);
int							draw_sky(t_cube *cube, int x, int start_y);
double						eye_fish_correction(double ray_angle, t_cube *cube);
void						draw_vertical_line_with_texture(t_cube *cube, int x,
								int wall_height, int tex_x, double distance,
								t_data *selected_tex);
void						init_weapon(t_cube *cube);
void						draw_weapon(t_cube *cube);
void						scale_weapon(t_cube *cube);
void						draw_circular_minimap(t_cube *cube);
void						draw_minimap_pixel(t_cube *cube, int x, int y,
								int color);
void						draw_minimap_line(t_cube *cube, double angle,
								int length, int color);
void						draw_health_bar(t_cube *cube);
void						update_frame(t_cube *cube);
int							load_frames(t_cube *cube);
void						add_frame_ls(t_cube *cube);
int							handle_mouse_move(int x, int y, t_cube *cube);
void						draw_rectangle(t_data *data, int x, int y, int size,
								int color);
int							game_loop(t_cube *cube);
int							game_loop_wrapper(void *param);
void						draw_door(t_cube *cube);

#endif
