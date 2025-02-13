/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 01:49:25 by a                 #+#    #+#             */
/*   Updated: 2025/02/13 20:30:34 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "cub3d_def.h"
# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>

typedef struct s_slope
{
	double	x_a;
	double	x_b;
	double	y_a;
	double	y_b;
	double	dx;
	double	dy;
	double	p;
	int		i;
	int		j;
}			t_slope;

# define NORTH 1
# define SOUTH 2
# define EAST 3
# define WEST 4

typedef struct s_img
{
	void	*data;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}			t_img;

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
}			t_color;

typedef struct s_cub
{
	int		i;
	int		x;
	char	**map;
	int		map_height;
	int		map_width;
	void	*mlx;
	void	*win;
	t_img	*img;
	t_img	*mini_map;
	t_color	*floor;
	t_color	*ceiling;
	t_img	*texture_n;
	t_img	*texture_s;
	t_img	*texture_w;
	t_img	*texture_e;
	double dir_x;     // player direction
	double dir_y;     // player direction
	double dir_angle; // direction angle
	double pos_x;     // player position
	double pos_y;     // player position
	double plane_x;   // camera plane
	double plane_y;   // camera plane
	int		text_x;
	int		text_y;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	prep_wall_dist;
	int		step_x;
	int		step_y;
	int		side;
	double	wall_x;
	int		ray_x;
	int		ray_y;
	int		ray_y_start;
	int		ray_y_end;
	int		ray_text_x;
	int		ray_text_y;
	int		draw_start;
	int		draw_end;
}			t_cub;

// INIT STRUCT
void		init_mlx(t_cub *cub);
void		init_all(t_cub *cub);
void		init_two(t_cub *cub);

// PARSING
void		check_arg(int argc, char **argv);
void		parsing(t_cub *cub, char *file);
void		handle_element(t_cub *cub, char *line);
void		handle_texture(t_cub *cub, t_img *img, char *line);
void		handle_colors(t_cub *cub, t_color *rgb, char *line);
void		check_elements(t_cub *cub);

// MAP
void		handle_map(t_cub *cub);
void		check_map_space(t_cub *cub, int i, int j);
void		check_map_elem(t_cub *cub, char elem, int i, int j);

// RAY
void		test_ray(t_cub *cub);
void		pixel_on_img(t_img *img, int rgb, int x, int y);
void		paint_line(t_cub *cub, int rgb);

// FREE
void		free_cub(t_cub *cub);
void		exit_error(t_cub *cub, char *str);
int			close_all(t_cub *cub);

// UTILS
int			is_space(char c);
void		print_cub(t_cub *cub);
int			is_in(char c, char *str);
int			line_is_empty(t_cub *cub, char *line);
int			max(int a, int b);

// INIT MAP
int			init_max(t_cub *cub, int fd, int n);
void		init_map(t_cub *cub, char *file, int n);
void		add_map_line(t_cub *cub, char *line);
void		save_map(t_cub *cub, char *file, char *line, int n);
int			player_pixel(t_cub *cub, int i, int j, int color);

// EVENTS HANDLER
int			mouse_hook(t_cub *cub, int button, int x, int y);
int			key_hook(t_cub *cub, int key);

// MINI CARTE
void		draw_map(t_cub *cub);
void		pixel_to_map(t_cub *cub, int rgb, int x, int y);
void		miniray(t_cub *cub, int i0, int j0);
void		pixel_to_img(t_img *img, int x, int y, int color);
void		mini_map(t_cub *cub);
int			is_in_img(int x, int y, int width, int height);
int			big_pixel(t_cub *cub, int i, int j, int color);
void		center_map(t_cub *cub);
void		erase_map(t_cub *cub);
void		mini_map(t_cub *cub);
int			first_row(t_cub *cub);
void		map_grid(t_cub *cub, int i0, int j0);
void		center_map(t_cub *cub);

// bresenham
void		segment(t_cub *cub, int x_a, int y_a, int x_b, int y_b);
void		segment_vertical(t_cub *cub, t_slope *ab);
void		segment_q1(t_cub *cub, t_slope *ab);
void		segment_q2(t_cub *cub, t_slope *ab);
void		segment_q3(t_cub *cub, t_slope *ab);
void		segment_q4(t_cub *cub, t_slope *ab);

// background
void		background(t_cub *cub);

#endif
