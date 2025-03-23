/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:44:41 by iouhssei          #+#    #+#             */
/*   Updated: 2025/03/21 00:26:25 by iouhssei         ###   ########.fr       */
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

//----------------------------------------//
//-----------MACROS-----------------------//
//----------------------------------------//

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
# define LEFT_KEY 65361
# define RIGHT_KEY 65363

// constants

# define PI 3.14159265359
# define M_PI_2 1.57079632679489661923
# define T_PI 6.28318530718
# define RAY_STEP 0.1
# define PLAYER_RADIUS 5

// game resolution

# define S_RES 400
# define WIDTH 800
# define HEIGHT 800
# define S_TEX 64
# define MAP_SCALE 0.5
# define TILE_SIZE (S_TEX * MAP_SCALE)
# define FOV PI / 3

// minimap

# define MINIMAP_RADIUS 80
# define MINIMAP_X (MINIMAP_RADIUS + 10)
# define MINIMAP_Y (MINIMAP_RADIUS + HEIGHT - 180)
# define PLAYER_DOT_SIZE 3
# define MINIMAP_SCALE 3
# define MIN_DISTANCE 0.5
# define MAX_DISTANCE 1000.0

// animations

# define FRAME_DELAY 20
# define MVM_SPEED 1.5
# define RT_SPEED 0.02
# define MOUSE_SENSITIVITY 0.001

// Structs

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
	int						tex_x;
	int						tex_y;
	int						color;
	float					x_ratio;
	float					y_ratio;
	int						screen_x;
	int						screen_y;
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

typedef struct s_raycast
{
	double					ray_angle;
	double					rayDirX;
	double					rayDirY;
	int						mapX;
	int						mapY;
	double					deltaDistX;
	double					deltaDistY;
	int						stepX;
	int						stepY;
	double					sideDistX;
	double					sideDistY;
	int						hit_wall;
	int						side;
	int						safety;
	double					perpWallDist;
	double					angle_diff;
	int						wall_height;
	t_data					*selected_tex;
	double					wall_x;
	int						tex_x;
	int						color;
	int						tile_val;
	double					hitX;
	double					hitY;
}							t_raycast;

typedef struct s_handle_keys
{
	double					movement_speed;
	double					rotation_speed;
	double					new_x;
	double					new_y;
	double					temp_x;
	double					temp_y;
	double					candidate_x;
	double					candidate_y;

}							t_handle_keys;

typedef struct s_keys
{
	int						w;
	int						a;
	int						s;
	int						d;
	int						left;
	int						right;
}							t_keys;

typedef struct s_is_collidding
{
	double					left;
	double					right;
	double					top;
	double					bottom;
	int						left_tile;
	int						right_tile;
	int						top_tile;
	int						bottom_tile;
	int						ty;
	int						tx;
}							t_is_collidding;
typedef struct s_rgb
{
	int						r;
	int						g;
	int						b;
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
	double					x;
	double					y;
	t_rgb					f_rgb;
	t_rgb					c_rgb;
	double					start_angle;
}							t_map;

typedef struct s_cube
{
	void					*mlx;
	void					*mlx_window;
	t_garbage_collector		*gc;
	t_data					*data;
	t_data					texture[4];
	double					p_x;
	double					p_y;
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
	int						minimap_radius;
	int						minimap_center_x;
	int						minimap_center_y;
	double					minimap_scale;
	int						player_dot_size;
	t_is_collidding			collid;
	t_handle_keys			hc;
	t_keys					keys;
	t_map					map;
}							t_cube;

void						print_2d(char **s);
void						free_map_textures(t_map *map);
void						free_map_struct(t_map *map);
int							handle_errors(int err_code);

/* parse.c */
int							check_file_name(char *s);
int							check_texture(t_map *map);
size_t						ft_strlenewline(char *s);
int							check_virgul(char *av);
char						*get_file_in_char(char *av);

/* parse_helpers1.c */
void						free_all_lines(char **lines);
void						alloc_clean_lines(char **all_line,
								char ***clean_line, int count);
char						**count_and_alloc_lines(char **all_line,
								int *count);
char						**split_file(char *s);
void						*free_clean_lines(char **clean_line, int j);

/* parse_helpers2.c */
char						*parse_line(char *s, char *to_trim);
void						free_rgb_arrays(char **floor_rgb,
								char **celling_rgb);
void						fill_rgb(t_map *map);
int							is_valid_rgb(int r, int g, int b);
int							check_rgbs(t_map *map);

/* parse_helpers3.c */
void						parse_texture(t_map *map, char *line,
								char *identifier, char **dest);
void						fill_struct_helper(t_map *map, char **file);
void						fill_struct(t_map *map, char *av);
void						initiliase_struct(t_map *map, char *av);

/* parse_map1.c */
int							check_map_line(char *s);
void						count_map_lines(char **all_file, int *lines,
								int *map_started);
void						fill_map_array(t_map *map, char **all_file,
								int lines);
void						get_map_into2darray(t_map *map, char *av);
int							count_double_char(char **s);
/*parse_helpers.c*/

void						count_w_h(t_map *map);
void						get_x_y(t_map *map);

/* parse_map2.c */
int							check_borders(char *s);
int							check_top_and_bottom(char *s);
int							check_line_endings(char **map, int i,
								int current_len, int prev_len);
int							check_map_steps(t_map *map);
int							check_surroundings(t_map *map, int i, int j,
								int size);

/* parse_map3.c */
int							check_map_content(t_map *map, int size);
int							check_map(t_map *map);
int							count_till_newline(char *s);
int							get_bigger_mapline(char **s);
int							get_line_of_biggervalue(char **s);
int							check_map_content(t_map *map, int size);
void						check_direction(t_map *map);
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
void						draw_map(t_data *data, t_cube *cube);
void						clean_screen(t_data *data, t_cube *cube);
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
void						update_frame(t_cube *cube);
int							load_frames(t_cube *cube);
void						add_frame_ls(t_cube *cube);
int							handle_mouse_move(int x, int y, t_cube *cube);
void						draw_rectangle(t_data *data, int x, int y, int size,
								int color);
int							game_loop(t_cube *cube);
int							game_loop_wrapper(void *param);
void						draw_door(t_cube *cube);
void						init_minimap_params(t_cube *cube);
void						init_raycast(t_cube *cube, t_raycast *rc,
								int ray_index);
void						compute_wall_distance(t_cube *cube, t_raycast *rc);
void						run_dda(t_cube *cube, t_raycast *rc);
void						select_textures(t_cube *cube, t_raycast *rc);
void						draw_slice(t_cube *cube, t_raycast *rc,
								int screen_x);
void						init_raycast_steps(t_cube *cube, t_raycast *rc);
void						init_raycast_angle_and_delta(t_cube *cube,
								t_raycast *rc, int ray_index);
void						clean_display(t_cube *cube);
int							on_key_release(int keycode, t_cube *cube);
int							on_key_press(int keycode, t_cube *cube);
int							key_loop(t_cube *cube);
int							close_win(t_cube *cube);
void						destroy_mlx(t_cube *cube);

#endif
