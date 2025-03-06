/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 01:49:52 by a                 #+#    #+#             */
/*   Updated: 2025/03/06 11:38:35 by kimnguye         ###   ########.fr       */
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
	mlx_hook(cub.win, KEYPRESS_EVENT, 1L << 0, key_press, &cub);
	mlx_hook(cub.win, 3, 1L << 1, key_release, &cub.player);
	mlx_hook(cub.win, 17, 1L << 17, close_all, &cub);
	mlx_loop_hook(cub.mlx, draw_loop, &cub);
	mlx_loop(cub.mlx);
	return (0);
}

void	exit_msg(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	exit(1);
}

void	check_arg(int argc, char **argv)
{
	int		n;
	char	buffer[128];
	int		fd;

	if (argc != 2)
		exit_msg("Incorrect number of arguments\n");
	n = ft_strlen(argv[1]);
	if (ft_strncmp(".cub", &argv[1][n - 4], 4))
		exit_msg("Wrong file format: a .cub is expected!\n");
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		exit_msg("Can't open file\n");
	}
	if (read(fd, buffer, 128) == -1 && errno == EISDIR)
	{
		close(fd);
		exit_msg("Can't read a directory\n");
	}
	close(fd);
}
