/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkikuchi <kkikuchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 23:56:51 by kkikuchi          #+#    #+#             */
/*   Updated: 2021/01/12 04:16:04 by kikuchika        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include <stdint.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include "mlx.h"
# include "../libft/libft.h"

# define SUCESS 1
# define END 0
# define ERROR -1
# define TABLE_SIZE 29999
# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_RELEASE 3
# define X_EVENT_KEY_EXIT 17
# define MAP_WIDTH 1024
# define MAP_HEIGHT 1024
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define K_W 119
# define K_S 115
# define K_D 100
# define K_A 97
# define RIGHT 65363
# define LEFT 65361
# define K_ESC 65307
# define K_UP 65362
# define K_DOWN 65364

typedef struct		s_img
{
	void			*img;
	int				*data;
	int				size_l;
	int				bpp;
	int				endian;
	int				img_w;
	int				img_h;
}					t_img;

typedef struct		s_win
{
	void			*ptr;
	int				w;
	int				h;
}					t_win;

typedef struct		s_tex
{
	int				*addr;
	int				w;
	int				h;
}					t_tex;

typedef struct		s_sprite
{
	double			x;
	double			y;
	double			dist;
	int				order;
}					t_sprite;

typedef struct		s_key
{
	int				key_a;
	int				key_w;
	int				key_s;
	int				key_d;
	int				key_esc;
	int				key_left;
	int				key_right;
}					t_key;

typedef struct		s_state
{
	int				x;
	int				y;
	struct s_state	*hash_link;
}					t_state;

typedef struct		s_raycasting
{
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			prep_wall_dist;
	double			wall_x;
	double			step;
	double			tex_pos;
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	int				side;
	int				hit;
	int				line_height;
	int				draw_start;
	int				draw_end;
	int				tex_num;
	int				tex_x;
	int				tex_y;
	int				color;
}					t_raycasting;

typedef struct		s_data
{
	char			map[MAP_HEIGHT][MAP_WIDTH];
	int				**buf;
	t_win			win;
	t_tex			tex[5];
	t_sprite		*sprite;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	void			*mlx;
	t_key			key;
	t_img			img;
	double			*z_buffer;
	double			move_speed;
	double			rot_speed;
	int				sp_n;
	int				sp_max;
	uint32_t		color[2];
	t_state			*hash_table[TABLE_SIZE];
}					t_data;

typedef struct		s_pair
{
	int				first;
	int				second;
}					t_pair;

typedef struct		s_sprite_draw
{
	double			x;
	double			y;
	double			inv_det;
	double			trans_form_x;
	double			trans_form_y;
	int				screen_x;
	int				height;
	int				v_move_screen;
	int				width;
	int				draw_start_y;
	int				draw_end_y;
	int				draw_start_x;
	int				draw_end_x;
	int				tex_x;
	int				tex_y;
	int				color;
}					t_sprite_draw;

typedef struct		s_header
{
	uint32_t		file_size;
	int				offset;
	int				header_size;
	int				planes;
	int				bpp;
}					t_header;

int					get_next_line(int fd, char **line);
void				read_cubfile(t_data *data, char *filename);
void				error(char *msg);
void				check_map(t_data *info);
void				key_update(t_data *info);
void				key_update(t_data *info);
int					key_press(int key, t_data *info);
int					key_release(int key, t_data *info);
void				create_bmp(t_data *info, char **argv);
void				draw(t_data *info);
void				sprite_casting(t_data *info);
void				wall_casting(t_data *info);
void				draw_flor(t_data *info);
void				sort_order(t_data *info);
int					*load_img(t_data *info, char **str, int j, int *i);
uint32_t			load_color(char **str, int *i, char *line);
void				free_str(char **map);
int					int_filter(char *s);
void				load_win(t_data *data, char **str, int *i, char *line);
void				load_map(t_data *data, char *line, int *j, int *map_flag);
void				check_map_closed(t_data *data);
int					check_map_form(t_data *info);
int					set(int x, int y, t_data *info);
void				free_hash_table(t_data *info);
void				kw(t_data *info);
void				ad(t_data *info);
void				calc_param(t_data *info, t_raycasting *rc, int x);
void				calc_draw_param(t_data *info, t_raycasting *rc);
void				free_int(int **map);
#endif
