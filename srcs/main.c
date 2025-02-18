/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 01:49:52 by a                 #+#    #+#             */
/*   Updated: 2025/02/18 01:31:52 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <math.h>

int	main(int argc, char **argv)
{
	t_cub	cub;

	check_arg(argc, argv);
	init_all(&cub);
	init_player(&cub);
	parsing(&cub, argv[1]);
	init_mlx(&cub);
	print_mlx(&cub);
	//draw_loop(&cub);
	mlx_hook(cub.win, KEYPRESS_EVENT, 1L << 0, key_press, &cub);
	mlx_hook(cub.win, 3, 1L << 1, key_release, &cub.player);
	mlx_hook(cub.win, 17, 1L << 17, close_all, &cub);
	mlx_loop_hook(cub.mlx, draw_loop, &cub);
	mlx_loop(cub.mlx);
	return (0);
}

void	check_arg(int argc, char **argv)
{
	int	n;

	if (argc != 2)
	{
		ft_putstr_fd("Error: incorrect number of arguments\n", 2);
		exit(1);
	}
	n = ft_strlen(argv[1]);
	if (ft_strncmp(".cub", &argv[1][n - 4], 4))
	{
		ft_putstr_fd("Wrong file format: a .cub is expected!\n", 2);
		exit(1);
	}
}
