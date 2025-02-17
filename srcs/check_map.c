/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 19:02:10 by kimnguye          #+#    #+#             */
/*   Updated: 2025/02/17 17:21:45 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*les espaces doivent etre entoures de 1 ou d'autres espaces*/

void	check_map_space(t_cub *cub, int i, int j)
{
	if (cub->map[i][j] == ' ')
	{
		if (i < cub->map_height - 1 && cub->map[i + 1][j] && cub->map[i
			+ 1][j] != ' ' && cub->map[i + 1][j] != '1')
			exit_error(cub, "The map is not closed");
		if (i > 0 && cub->map[i - 1][j] && cub->map[i - 1][j] != ' '
			&& cub->map[i - 1][j] != '1')
			exit_error(cub, "The map is not closed");
		if (j > 0 && cub->map[i][j - 1] && cub->map[i][j - 1] != ' '
			&& cub->map[i][j - 1] != '1')
			exit_error(cub, "The map is not closed");
		if (cub->map[i][j + 1] && cub->map[i][j + 1] != ' ' && cub->map[i][j
			+ 1] != '1')
			exit_error(cub, "The map is not closed");
	}
}

/*player direction*/
void	set_direction(t_cub *cub, char elem)
{
	double	plane_angle;

	if (elem == 'N')
		cub->player.angle = -M_PI / 2;
	else if (elem == 'S')
		cub->player.angle = M_PI / 2;
	else if (elem == 'E')
		cub->player.angle = 0;
	else if (elem == 'W')
		cub->player.angle = M_PI;
}

/*init the player position and direction
the map should only contain one N, S, E or W
the map should only contain 0 and 1 except for the player position*/
void	check_map_elem(t_cub *cub, char elem, int i, int j)
{
	if (is_in(elem, "NSEW"))
	{
		if (cub->player.x == -1 || cub->player.y == -1)
		{
			cub->player.x = j * BLOCK + BLOCK / 2 - PLAYER_SIZ / 2;
			cub->player.y = i * BLOCK + BLOCK / 2 - PLAYER_SIZ / 2;
			cub->pos_j = j;
			cub->pos_i = i;
			set_direction(cub, elem);
		}
		else
			exit_error(cub, "There should be only one player\n");
	}
	else if (elem != '0' && elem != '1' && !is_space(elem))
		exit_error(cub, "Unknown element in map");
}

/*check if the first and last line only contains 1
check if the first and last element of each line is a 1
check that there is exactly one player*/
void	handle_map(t_cub *cub)
{
	cub->i = 0;
	while (cub->map[cub->i])
	{
		cub->x = 0;
		while (cub->map[cub->i][cub->x])
		{
			if (cub->map[cub->i][cub->x] == ' ')
				check_map_space(cub, cub->i, cub->x);
			if ((cub->i == 0 || cub->i == cub->map_height - 1)
				&& cub->map[cub->i][cub->x] != '1'
				&& cub->map[cub->i][cub->x] != ' ')
				exit_error(cub, "The map is not closed");
			if ((cub->x == 0 || !cub->map[cub->i][cub->x + 1])
				&& cub->map[cub->i][cub->x] != '1'
				&& cub->map[cub->i][cub->x] != ' ')
				exit_error(cub, "The map is not closed");
			if (cub->i > 0 && cub->i < cub->map_height - 1 && cub->x > 0)
				check_map_elem(cub, cub->map[cub->i][cub->x], cub->i, cub->x);
			cub->x++;
		}
		cub->i++;
	}
	if (cub->player.x == -1 || cub->player.y == -1)
		exit_error(cub, "There is no player\n");
}
