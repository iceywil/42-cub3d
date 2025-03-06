/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 01:49:25 by a                 #+#    #+#             */
/*   Updated: 2025/03/06 12:21:22 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "cub3d_def.h"
# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>

typedef struct s_ray
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		sidedist_x;
	double		sidedist_y;
	double		deltadist_x;
	double		deltadist_y;
	float		step_x;
	float		step_y;
}				t_ray;

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
	t_ray		ray;
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
	char		*line;
	int			fd;
	int			i;
	int			j;
	bool		map_show;
	bool		tex_show;
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
	t_img		door;
	t_img		sprite;
	t_img		*wall_texture;
	t_player	player;
	t_ray		ray;
	int			side;
	float		fraction;
}				t_cub;

// INIT STRUCT
void			init_mlx(t_cub *cub);
void			init_all(t_cub *cub);
void			init_two(t_cub *cub);
void			init_player(t_cub *cub);
void			init_ray(t_ray *ray, t_cub *cub, double angle);

// PARSING
void			check_arg(int argc, char **argv);
void			parsing(t_cub *cub, char *file);
void			handle_element(t_cub *cub, char *line);
void			handle_texture(t_cub *cub, char *line);
void			check_elements(t_cub *cub);
void			handle_colors(t_cub *cub, t_color *rgb, char *line);
void			handle_map(t_cub *cub);
void			save_map(t_cub *cub, char *file, char *line, int n);
void			init_map(t_cub *cub, char *file, int n);
void			add_map_line(t_cub *cub, char *line);
void			init_max(t_cub *cub, int fd, int n);

// EVENTS
int				key_press(int keycode, t_cub *cub);
int				key_release(int keycode, t_player *player);

// RAY
void			move_player(t_player *player, t_cub *cub);
int				draw_loop(t_cub *cub);
void			draw_square(t_cub *cub, int x, int y, int color);
void			clear_image(t_img *img, int height, int width);
void			draw_map(t_cub *cub);
bool			touch(t_cub *cub, float px, float py);
void			wall_texture(t_cub *cub, double angle, int x);
void			draw_wall(t_cub *cub, t_img *texture, int x);
void			calc_side(t_cub *cub, double angle, int x);
void			show_texture(t_cub *cub);

// CALC UTILS
float			distance(float x, float y);
float			fixed_dist(t_player player, float x, float y);
int				is_null(char **map, int i, int j);
void			calc_ray(t_ray *ray, t_player *player);

// PIXEL UTILS
void			put_pixel(t_img *img, int x, int y, int color);
int				get_pixel(t_img *img, int x, int y);

// FREE
void			free_cub(t_cub *cub);
void			exit_error(t_cub *cub, char *str);
int				close_all(t_cub *cub);

// UTILS
int				is_space(char c);
int				is_in(char c, char *str);
int				line_is_empty(t_cub *cub, char *line);
int				max(int a, int b);
int				coma_ctr(char *str);

// background
void			background(t_cub *cub);

// bonus
void			init_door(t_cub *cub);
int				is_door_forward(char **map, t_player player);
void			door_action(char **map, t_player player);
int				is_door_closed(char **map, float x, float y);

void			init_sprite(t_cub *cub);
int				is_sprite_forward(char **map, double x, double y);
void			sprite_action(char **map, t_player player);
void			init_ray_player(t_cub *cub, t_ray *ray, t_player *player);
#endif
