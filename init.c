/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:24:02 by kimnguye          #+#    #+#             */
/*   Updated: 2025/02/04 18:17:13 by kimnguye         ###   ########.fr       */
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
	cub->img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->img)
		exit_error(cub, "Initialisation of image failed\n");
	cub->img_data = mlx_get_data_addr(cub->img,
			&cub->img_pixel, &cub->img_line, &cub->img_endian);
	cub->mini_carte = mlx_new_image(cub->mlx, WIDTH / 5, HEIGHT / 5);
	if (!cub->mini_carte)
		exit_error(cub, "Initialisation of image failed\n");
	cub->carte_data = mlx_get_data_addr(cub->mini_carte,
			&cub->carte_pixel, &cub->carte_line, &cub->carte_endian);
}

void	init_all(t_cub *cub)
{
	cub->i = 0;
	cub->start_map_i = 0;
	cub->no = NULL;
	cub->so = NULL;
	cub->we = NULL;
	cub->ea = NULL;
	cub->f = NULL;
	cub->c = NULL;
	cub->f_r = -1;
	cub->f_g = -1;
	cub->f_b = -1;
	cub->c_r = -1;
	cub->c_g = -1;
	cub->c_b = -1;
	cub->map = NULL;
	cub->map_height = 0;
	cub->map_width = 0;
	cub->player_pos = 0;
}
