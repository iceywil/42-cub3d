/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:24:02 by kimnguye          #+#    #+#             */
/*   Updated: 2025/02/12 12:16:21 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_mlx(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		exit_error(cub, "Initialisation of mlx failed\n");
	cub->win = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "42 - CUB3D");
	if (!cub->win)
		exit_error(cub, "Initialisation of window failed\n");
	cub->img.mlx = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->img.mlx)
		exit_error(cub, "Initialisation of image failed\n");
	cub->img.addr = mlx_get_data_addr(cub->img.mlx,
			&cub->img.bpp, &cub->img.line, &cub->img.endian);
	cub->mini_carte.mlx = mlx_new_image(cub->mlx, MAP_WIDTH, MAP_HEIGHT);
	if (!cub->mini_carte.mlx)
		exit_error(cub, "Initialisation of image failed\n");
	cub->mini_carte.addr = mlx_get_data_addr(cub->mini_carte.mlx,
			&cub->mini_carte.bpp, &cub->mini_carte.line,
			&cub->mini_carte.endian);
}

void	init_all(t_cub *cub)
{
	cub->i = 0;
	cub->no = NULL;
	cub->so = NULL;
	cub->we = NULL;
	cub->ea = NULL;
	cub->floor = NULL;
	cub->ceiling = NULL;
	cub->f.r = -1;
	cub->f.g = -1;
	cub->f.b = -1;
	cub->c.r = -1;
	cub->c.g = -1;
	cub->c.b = -1;
	cub->map = NULL;
	cub->map_height = 0;
	cub->map_width = 0;
	cub->dir_x = UNSET_DOUBLE;
	cub->dir_y = UNSET_DOUBLE;
	cub->dir_angle = UNSET_DOUBLE; 
	cub->pos_x = -1; 
	cub->pos_y = -1;
}
