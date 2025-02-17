/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:24:02 by kimnguye          #+#    #+#             */
/*   Updated: 2025/02/17 06:05:04 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_mlx(t_cub *cub)
{
	cub->win = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "42 - CUB3D");
	if (!cub->win)
		exit_error(cub, "Initialisation of window failed\n");
	cub->img.data = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->img.data)
		exit_error(cub, "Initialisation of image failed\n");
	cub->img.addr = mlx_get_data_addr(cub->img.data, &cub->img.bpp,
			&cub->img.size_line, &cub->img.endian);
	if (!cub->img.addr)
		exit_error(cub, "Initialisation of image address failed\n");
	cub->mini_map.data = mlx_new_image(cub->mlx, MAP_WIDTH, MAP_HEIGHT);
	if (!cub->mini_map.data)
		exit_error(cub, "Initialisation of image failed\n");
	cub->mini_map.addr = mlx_get_data_addr(cub->mini_map.data,
			&cub->mini_map.bpp, &cub->mini_map.size_line,
			&cub->mini_map.endian);
	if (!cub->mini_map.addr)
		exit_error(cub, "Initialisation of image address failed\n");
	ft_printf("%p\n", cub->img.data);
	ft_printf("%p\n", cub->mini_map.data);
	ft_printf("%p\n", cub->img.addr);
	ft_printf("%p\n", cub->mini_map.addr);
}

void	init_all(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		exit_error(cub, "Initialisation of mlx failed\n");
	cub->win = NULL;
	cub->img.data = NULL;
	cub->img.addr = NULL;
	cub->mini_map.data = NULL;
	cub->mini_map.addr = NULL;
	cub->i = 0;
	cub->floor.r = -1;
	cub->floor.g = -1;
	cub->floor.b = -1;
	cub->ceiling.r = -1;
	cub->ceiling.g = -1;
	cub->ceiling.b = -1;
	cub->map = NULL;
	cub->map_height = 0;
	cub->map_width = 0;
	init_two(cub);
}

void	init_two(t_cub *cub)
{
	cub->texture_n.data = NULL;
	cub->texture_s.data = NULL;
	cub->texture_w.data = NULL;
	cub->texture_e.data = NULL;
	cub->pos_x = -1;
	cub->pos_y = -1;
}

void	init_player(t_cub *cub)
{
	cub->player.x = MAP_WIDTH / 2;
	cub->player.y = MAP_HEIGHT / 2;
	cub->player.angle = PI / 2;
	cub->player.key_up = false;
	cub->player.key_down = false;
	cub->player.key_right = false;
	cub->player.key_left = false;
	cub->player.left_rotate = false;
	cub->player.right_rotate = false;
}
