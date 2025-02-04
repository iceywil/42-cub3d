/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 01:49:25 by a                 #+#    #+#             */
/*   Updated: 2025/02/04 16:07:11 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "mlx.h"
# include "cub3d_def.h"
# include <fcntl.h>

typedef struct s_cub
{
	int		i;
	int		start_map_i;
	int		x;
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
	int		map_height;
	int		map_width;
	void	*mlx;
	void	*win;
	void	*img;
	void	*mini_carte;
	char	*img_data;
	char	*mini_carte_data;
}			t_cub;

// MAIN
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

// INIT MAP
int			ft_init_max(int fd, t_cub *cub);
void		ft_init_map(t_cub *cub, char *file);
void		add_map_line(t_cub *cub, char *line);
void		save_map(t_cub *cub, char *file, char *line);

//EVENTS HANDLER
int			mouse_hook(int button, int x, int y, t_cub *cub);
int			key_hook(int key, t_cub *cub);
int			ft_rot_handler(int key, t_cub *cub);

#endif
