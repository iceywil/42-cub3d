/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 01:49:52 by a                 #+#    #+#             */
/*   Updated: 2025/02/04 16:30:50 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_cub	cub;
	int		n;

	init_all(&cub);
	if (argc != 2)
		exit_error(&cub, "Error: incorrect number of arguments\n");
	n = ft_strlen(argv[1]);
	if (ft_strncmp(".cub", &argv[1][n - 4], 4))
		return (ft_printf("Wrong file format: a .cub is expected!\n"), 1);
	parsing(&cub, argv[1]);
	mlx_hook((&cub)->win, KEYPRESS_EVENT, 1L << 0, key_hook, (&cub));
	mlx_hook((&cub)->win, BUTTONPRESS_EVENT, 1L << 2, mouse_hook, (&cub));
	mlx_hook((&cub)->win, 17, 1L << 17, ft_close_all, (&cub));
	mlx_loop(cub.mlx);
	free_cub(&cub);
	return (0);
}


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
	// cub->img_data;
	cub->mini_carte = mlx_new_image(cub->mlx, WIDTH / 5, HEIGHT / 5);
	// cub->mini_carte_data;
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
	ft_init_mlx(cub);
}
