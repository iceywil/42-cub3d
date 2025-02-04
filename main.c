/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 01:49:52 by a                 #+#    #+#             */
/*   Updated: 2025/02/04 18:11:59 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_cub	cub;
	int		n;

	if (argc != 2)
		exit_error(&cub, "Error: incorrect number of arguments\n");
	n = ft_strlen(argv[1]);
	if (ft_strncmp(".cub", &argv[1][n - 4], 4))
		return (ft_printf("Wrong file format: a .cub is expected!\n"), 1);
	init_all(&cub);
	parsing(&cub, argv[1]);
	ft_init_mlx(&cub);
	ft_draw_map(&cub);
	mlx_hook((&cub)->win, KEYPRESS_EVENT, 1L << 0, key_hook, (&cub));
	mlx_hook((&cub)->win, BUTTONPRESS_EVENT, 1L << 2, mouse_hook, (&cub));
	mlx_hook((&cub)->win, 17, 1L << 17, ft_close_all, (&cub));
	mlx_loop(cub.mlx);
	return (0);
}
