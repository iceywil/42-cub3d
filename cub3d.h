/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 01:49:25 by a                 #+#    #+#             */
/*   Updated: 2025/02/12 14:06:32 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "cub3d_def.h"
# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>

typedef struct s_slope {
	double	x_a;
	double	x_b;
	double	y_a;
	double	y_b;
	double	dx;
	double	dy;
	double	p;
	int	i;
	int	j;
}	t_slope;

typedef struct s_img
{
	void	*mlx;
	char	*addr;
	int		bpp;
	int		line;
	int		endian;
}			t_img;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;
	
typedef struct s_cub
{
	int		i;
	int		x;
	char	**map;
	double	dir_x; //player direction
	double	dir_y; //player direction
	double	dir_angle; //direction angle
	double	pos_x; //player position
	double	pos_y; //player position
	double	plane_x; //camera plane
	double	plane_y; //camera plane
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		text_x;
	int		text_y;
	char	*floor;
	char	*ceiling;
	t_rgb	f;
	t_rgb	c;
	void	*text_n;
	void	*text_s;
	void	*text_w;
	void	*text_e;
	int		map_height;
	int		map_width;
	void	*mlx;
	void	*win;
	t_img	img;
	t_img	mini_carte;
}			t_cub;

// INIT STRUCT
void		ft_init_mlx(t_cub *cub);
void		init_all(t_cub *cub);

// PARSING
void		check_arg(int argc, char **argv);
void		parsing(t_cub *cub, char *file);
void		parse_element(t_cub *cub, char *line);
void		handle_colors(t_cub *cub);
void		check_elements(t_cub *cub);

// MAP
void		handle_map(t_cub *cub);
void		check_map_space(t_cub *cub, int i, int j);

// FREE
void		free_cub(t_cub *cub);
void		exit_error(t_cub *cub, char *str);
int			ft_close_all(t_cub *cub);

// UTILS
int			is_space(char c);
void		print_cub(t_cub *cub);
int			isin(char c, char *str);
int			line_is_empty(t_cub *cub, char *line);
int			ft_max(int a, int b);

// INIT MAP
int			ft_init_max(int fd, t_cub *cub, int n);
void		ft_init_map(t_cub *cub, char *file, int n);
void		add_map_line(t_cub *cub, char *line);
void		save_map(t_cub *cub, char *file, char *line, int n);
void		get_textures(t_cub *cub);

// EVENTS HANDLER
int			mouse_hook(int button, int x, int y, t_cub *cub);
int			key_hook(int key, t_cub *cub);

// MINI CARTE
void		pixel_to_img(t_img *img, int x, int y, int color);
void		ft_mini_map(t_cub *cub);
int			isin_img(int x, int y, int width, int height);
int			big_pixel(t_cub *cub, int i, int j, int color);

//bresenham
void	ft_segment(t_cub *cub, int x_a, int y_a, int x_b, int y_b);
void	ft_segment_vertical(t_cub *cub, t_slope *ab);
void	ft_segment_q1(t_cub *cub, t_slope *ab);
void	ft_segment_q2(t_cub *cub, t_slope *ab);
void	ft_segment_q3(t_cub *cub, t_slope *ab);
void	ft_segment_q4(t_cub *cub, t_slope *ab);

//background
void	ft_background(t_cub *cub);

#endif
