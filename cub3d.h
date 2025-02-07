/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 01:49:25 by a                 #+#    #+#             */
/*   Updated: 2025/02/07 15:10:22 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include <fcntl.h>

typedef struct s_cub
{
	int		i;
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
	int		map_height;
}			t_cub;

// MAIN
void		init_all(t_cub *cub);

// PARSING
void		parsing(t_cub *cub, char *file);
void		parse(t_cub *cub, int fd);
void		add_map_line(t_cub *cub, char *line);
void		handle_element(t_cub *cub, char *line);

void		handle_colors(t_cub *cub);
void		check_elements(t_cub *cub);

// MAP
void		handle_map(t_cub *cub);
int			check_tokens(t_cub *cub);
void		check_closed(t_cub *cub);

// FREE
void		free_cub(t_cub *cub);
void		exit_error(t_cub *cub, char *str);

// UTILS
int			is_space(char c);
int	line_is_empty(t_cub *cub, char *line);

#endif
