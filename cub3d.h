/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 01:49:25 by a                 #+#    #+#             */
/*   Updated: 2025/02/24 14:09:34 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "cub3d_def.h"
# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>

typedef struct s_slope
{
	double		x_a;
	double		x_b;
	double		y_a;
	double		y_b;
	double		dx;
	double		dy;
	double		p;
	int			i;
	int			j;
}				t_slope;

typedef struct s_player
{
	double		x;
	double		y;
	float		angle;
	int			x0;
	int			y0;
	bool		key_up;
	bool		key_down;
	bool		key_left;
	bool		key_right;

	bool		left_rotate;
	bool		right_rotate;
}				t_player;

typedef struct s_img
{
	void		*data;
	char		*addr;
	int			bpp;
	int			size_line;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct s_cub
{
	int			i;
	int			x;
	char		**map;
	int			map_height;
	int			map_width;
	void		*mlx;
	void		*win;
	t_img		img;
	t_img		mini_map;
	t_color		floor;
	t_color		ceiling;
	t_img		texture_n;
	t_img		texture_s;
	t_img		texture_w;
	t_img		texture_e;
	t_player	player;
	t_img		*wall_texture;
	int			pos_j;
	int			pos_i;
	double		ray_x;
	double		ray_y;
	int			side;
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	double		delta_dist_x;
	double		delta_dist_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		prep_wall_dist;
	int			step_x;
	int			step_y;
	double		wall_x;
}				t_cub;

// INIT STRUCT
void			init_mlx(t_cub *cub);
void			init_all(t_cub *cub);
void			init_two(t_cub *cub);
void			init_player(t_cub *cub);

// PARSING
void			check_arg(int argc, char **argv);
void			parsing(t_cub *cub, char *file);
void			handle_element(t_cub *cub, char *line);
void			handle_texture(t_cub *cub, char *line);
void			handle_colors(t_cub *cub, t_color *rgb, char *line);
void			check_elements(t_cub *cub);
void			handle_map(t_cub *cub);
void			check_map_space(t_cub *cub, int i, int j);
void			check_map_elem(t_cub *cub, char elem, int i, int j);
void			set_direction(t_cub *cub, char elem);
void			draw_player(t_img *img, int x, int y, int color);

// RAY
int				key_press(int keycode, t_cub *cub);
int				key_release(int keycode, t_player *player);
void			move_player(t_player *player, t_cub *cub);
int				draw_loop(t_cub *cub);
void			draw_square(t_cub *cub, int x, int y, int color);
void			clear_image(t_img *img, int height, int width);
void			draw_map(t_cub *cub);
bool			touch(t_cub *cub, float px, float py);
void			hit_texture(t_cub *cub, float start_x, int x);
void			draw_line(t_cub *cub, t_img *texture, int x);

// CALC UTILS
float			distance(float x, float y);
float			fixed_dist(t_player player, float x, float y);

// PIXEL UTILS
void			put_pixel(t_img *img, int x, int y, int color);
int				get_pixel(t_img *img, int x, int y);

// FREE
void			free_cub(t_cub *cub);
void			exit_error(t_cub *cub, char *str);
int				close_all(t_cub *cub);

// UTILS
int				is_space(char c);
void			print_cub(t_cub *cub);
int				is_in(char c, char *str);
int				line_is_empty(t_cub *cub, char *line);
void			print_mlx(t_cub *cub);
int				max(int a, int b);

// INIT MAP
int				init_max(t_cub *cub, int fd, int n);
void			init_map(t_cub *cub, char *file, int n);
void			add_map_line(t_cub *cub, char *line);
void			save_map(t_cub *cub, char *file, char *line, int n);

//texture
void			get_texture(t_cub *cub);

// background
void			background(t_cub *cub);

#endif