/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 01:49:52 by a                 #+#    #+#             */
/*   Updated: 2025/02/03 20:14:21 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_cub	cub;
	int		n;

	init_all(&cub);
	if (argc != 2)
		exit_error(&cub, "Error: incorrect number of arguments");
	n = ft_strlen(argv[1]);
	if (ft_strncmp(".cub", &argv[1][n - 4], 4))
		return (ft_printf("Wrong file format: a .cub is expected!\n"), 1);
	parsing(&cub, argv[1]);
	free_cub(&cub);
	return (0);
}

void	init_all(t_cub *cub)
{
	cub->i = 0;
	cub->n = 0;
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
