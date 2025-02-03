/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 19:02:10 by kimnguye          #+#    #+#             */
/*   Updated: 2025/02/03 21:15:58 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



void	check_map_elements(t_cub *cub, char elem)
{
	if (elem == 'N' || elem == 'S' || elem == 'E' || elem == 'W')
	{
		if (!cub->player_pos)
			cub->player_pos = elem;
		else
			exit_error(cub, "Error: there should be only one player");
	}
	else if (elem != 0 && elem != 1 && elem != ' ')
		exit_error(cub, "Error: unknown element in map");
}

/*check if the first and last line only contains 1
check if the first and last element of each line is a 1
the map should only contain one N, S, E or W
the map should not contain any other character*/
void	handle_map(t_cub *cub)
{
	cub->i = 0;
	cub->x = 0;
	while (cub->map[cub->i])
	{
		while (cub->map[cub->i][cub->x])
		{
			if ((cub->i == 0 || cub->i == cub->map_height)
				&& (cub->map[cub->i][cub->x] != ' '
					&& cub->map[cub->i][cub->x] != '1'))
				exit_error(cub, "Error: the map is not closed");
			if ((cub->x == 0 || cub->x == cub->map_width)
				&& (cub->map[cub->i][cub->x] != ' '
					&& cub->map[cub->i][cub->x] != '1'))
				exit_error(cub, "Error: the map is not closed");
			if (cub->i > 0 && cub->i < cub->map_height && cub->x > 0
				&& cub->x < cub->map_width) //contain only 0 1 N S E or W
				check_map_elements(cub, cub->map[cub->i][cub->x]);
			cub->x++;
		}
		cub->i++;
	}
}
