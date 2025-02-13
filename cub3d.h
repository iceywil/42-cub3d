/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 01:49:25 by a                 #+#    #+#             */
/*   Updated: 2025/02/11 19:27:21 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "cub3d_def.h"
# include "libft/libft.h"
# include "mlx.h"
# include <fcntl.h>

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

typedef struct s_cub
{
	int		i;
	int		start_map_i;
	int		x;
	char	**map;
	char	player_dir;
	int		player_x;
	int		player_y;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*f;
	char	*c;
	int		f_rgb;
	int		c_rgb;
	t_img	*texture_n;
	t_img	*texture_s;
	t_img	*texture_w;
	t_img	*texture_e;
	int		map_height;
	int		map_width;
	void	*mlx;
	void	*win;
	t_img	*img;
	t_img	*mini_map;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
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
void		parsing(t_cub *cub, char *file);
void		handle_element(t_cub *cub, char *line);
void		handle_texture(t_cub *cub, t_img *img, char *line);
void		handle_colors(t_cub *cub, int *rgb, char *line);
void		check_elements(t_cub *cub);

// MAP
void		handle_map(t_cub *cub);
void		check_map_space(t_cub *cub, int i, int j);

// RAY
void		test_ray(t_cub *cub);
void		pixel_on_img(t_img *img, int rgb, int x, int y);
int			rgb_to_int(int red, int green, int blue);
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

// INIT MAP
int			init_max(t_cub *cub, int fd);
void		init_map(t_cub *cub, char *file);
void		add_map_line(t_cub *cub, char *line);
void		save_map(t_cub *cub, char *file, char *line);

// EVENTS HANDLER
int			mouse_hook(t_cub *cub, int button, int x, int y);
int			key_hook(t_cub *cub, int key);

// MINI CARTE
void		draw_map(t_cub *cub);
void		pixel_to_map(t_cub *cub, int rgb, int x, int y);

#endif
