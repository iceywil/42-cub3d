/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:24:02 by kimnguye          #+#    #+#             */
<<<<<<< HEAD:srcs/init.c
/*   Updated: 2025/02/12 20:55:18 by a                ###   ########.fr       */
=======
/*   Updated: 2025/02/12 13:18:27 by kimnguye         ###   ########.fr       */
>>>>>>> kim:init.c
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_mlx(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		exit_error(cub, "Initialisation of mlx failed\n");
	cub->win = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "42 - CUB3D");
	if (!cub->win)
		exit_error(cub, "Initialisation of window failed\n");
	cub->img->data = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->img->data)
		exit_error(cub, "Initialisation of image failed\n");
	cub->img->addr = mlx_get_data_addr(cub->img->data, &cub->img->bpp,
			&cub->img->size_line, &cub->img->endian);
	cub->mini_map->data = mlx_new_image(cub->mlx, MAP_WIDTH, MAP_HEIGHT);
	if (!cub->mini_map->data)
		exit_error(cub, "Initialisation of image failed\n");
	cub->mini_map->addr = mlx_get_data_addr(cub->mini_map->data,
			&cub->mini_map->bpp, &cub->mini_map->size_line,
			&cub->mini_map->endian);
}

void	init_all(t_cub *cub)
{
	t_img	img;
	t_img	mini_map;

	cub->img = &img;
	cub->img->data = NULL;
	cub->mini_map = &mini_map;
	cub->mini_map->data = NULL;
	cub->i = 0;
<<<<<<< HEAD:srcs/init.c
	cub->start_map_i = 0;
	cub->f = NULL;
	cub->c = NULL;
	cub->f_rgb = 0;
	cub->c_rgb = 0;
	cub->map = NULL;
	cub->map_height = 0;
	cub->map_width = 0;
	cub->player_dir = 0;
	cub->player_x = -1;
	cub->player_y = -1;
	init_two(cub);
}

void	init_two(t_cub *cub)
{
	t_img	texture_n;
	t_img	texture_s;
	t_img	texture_w;
	t_img	texture_e;

	cub->texture_n = &texture_n;
	cub->texture_s = &texture_s;
	cub->texture_w = &texture_w;
	cub->texture_e = &texture_e;
=======
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
>>>>>>> kim:init.c
}
