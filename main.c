/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 01:49:52 by a                 #+#    #+#             */
/*   Updated: 2025/02/05 16:19:42 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_cub	cub;

	init_all(&cub);
	if (argc != 2)
		exit_error(&cub, "Error: no map");
	parsing(&cub, argv[1]);
	free_cub(&cub);
	return (0);
}

void	init_all(t_cub *cub)
{
	cub->i = 0;
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
	cub->line = NULL;
	cub->map = NULL;
	cub->map_height = 0;
	cub->map_width = 0;
	cub->player_pos = 0;
}
