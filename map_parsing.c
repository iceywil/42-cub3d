/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 19:02:10 by kimnguye          #+#    #+#             */
/*   Updated: 2025/02/03 23:01:43 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*les espaces doivent etre entoures de 1 ou d'autres espaces*/
void	check_map_space(t_cub *cub)
{
	cub->i = 0;
	while (cub->map[cub->i])
	{
		cub->x = 0;
		while (cub->map[cub->i][cub->x])
		{
			if (cub->map[cub->i][cub->x] == ' ')
			{
				if (cub->i < cub->map_height - 1 && cub->map[cub->i + 1][cub->x]
					&& cub->map[cub->i + 1][cub->x] != ' '
					&& cub->map[cub->i + 1][cub->x] != '1')
					exit_error(cub, "Error: the map is not closed");
				if (cub->i > 0 && cub->map[cub->i - 1][cub->x]
					&& cub->map[cub->i - 1][cub->x] != ' '
					&& cub->map[cub->i - 1][cub->x] != '1')
					exit_error(cub, "Error: the map is not closed");
				if (cub->x > 0 && cub->map[cub->i][cub->x - 1]
					&& cub->map[cub->i][cub->x - 1] != ' '
					&& cub->map[cub->i][cub->x - 1] != '1')
					exit_error(cub, "Error: the map is not closed");
				if (cub->map[cub->i][cub->x + 1]
					&& cub->map[cub->i][cub->x + 1] != ' '
					&& cub->map[cub->i][cub->x + 1] != '1')
					exit_error(cub, "Error: the map is not closed");
			}
			cub->x++;
		}
		cub->i++;
	}
	printf("check map spaces: SUCCESS\n");
}

 /*the map should only contain one N, S, E or W
the map should only contain 0 and 1 except for the player position*/
void	check_map_element(t_cub *cub, char elem)
{
	if (elem == 'N' || elem == 'S' || elem == 'E' || elem == 'W')
	{
		if (!cub->player_pos)
			cub->player_pos = elem;
		else
			exit_error(cub, "Error: there should be only one player");
	}
	else if (elem != '0' && elem != '1' && !is_space(elem))
		exit_error(cub, "Error: unknown element in map");
}




/*check if the first and last line only contains 1
check if the first and last element of each line is a 1*/
void	handle_map(t_cub *cub)
{
	cub->i = 0;
	while (cub->map[cub->i])
	{
		cub->x = 0;
		while (cub->map[cub->i][cub->x])
		{
			if ((cub->i == 0 || cub->i == cub->map_height)
				&& cub->map[cub->i][cub->x] != '1'
				&& cub->map[cub->i][cub->x] != ' ')
				exit_error(cub, "Error: the map is not closed");
			if ((cub->x == 0 || cub->x == cub->map_width)
				&& cub->map[cub->i][cub->x] != '1'
				&& cub->map[cub->i][cub->x] != ' ')
				exit_error(cub, "Error: the map is not closed");
			if (cub->i > 0 && cub->i < cub->map_height && cub->x > 0
				&& cub->x < cub->map_width)
				check_map_element(cub, cub->map[cub->i][cub->x]);
			cub->x++;
		}
		cub->i++;
	}
}
