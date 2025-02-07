/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 01:49:25 by a                 #+#    #+#             */
/*   Updated: 2025/02/07 17:18:38 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "cub3d_def.h"
# include "libft/libft.h"
# include "mlx.h"
# include <fcntl.h>

typedef struct s_img
{
	void	*mlx;
	char	*addr;
	int		bpp;
	int		line;
	int		endian;
}			t_img;

typedef struct s_cub
{
	int		i;
	int		start_map_i;
	int		x;
	char	*line;
	char	**map;
	char	player_pos;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*f;
	char	*c;
	int		f_r;
	int		f_g;
	int		f_b;
	int		c_r;
	int		c_g;
	int		c_b;
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
void		parsing(t_cub *cub, char *file);
void		handle_element(t_cub *cub, char *line);
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

// INIT MAP
int			ft_init_max(int fd, t_cub *cub);
void		ft_init_map(t_cub *cub, char *file);
void		add_map_line(t_cub *cub, char *line);
void		save_map(t_cub *cub, char *file, char *line);
void		get_textures(t_cub *cub);

// EVENTS HANDLER
int			mouse_hook(int button, int x, int y, t_cub *cub);
int			key_hook(int key, t_cub *cub);

// MINI CARTE
void		ft_draw_map(t_cub *cub);
void		pixel_to_map(t_cub *vars, int x, int y, int color);

#endif
