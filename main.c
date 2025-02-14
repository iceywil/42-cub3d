/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 01:49:52 by a                 #+#    #+#             */
/*   Updated: 2025/02/14 13:50:37 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_cub	cub;

	check_arg(argc, argv);
	init_all(&cub);
	parsing(&cub, argv[1]);
	ft_init_mlx(&cub);
	ft_background(&cub);
	ft_game_loop(&cub);
	get_textures(&cub);
	ft_mini_map(&cub);
	mlx_hook((&cub)->win, KEYPRESS_EVENT, 1L << 0, key_hook, (&cub));
	mlx_hook((&cub)->win, BUTTONPRESS_EVENT, 1L << 2, mouse_hook, (&cub));
	mlx_hook((&cub)->win, 17, 1L << 17, ft_close_all, (&cub));
	//mlx_loop_hook(cub.mlx, ft_game_loop, &cub);
	mlx_loop(cub.mlx);
	return (0);
}
