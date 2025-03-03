/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 19:02:10 by kimnguye          #+#    #+#             */
/*   Updated: 2025/03/03 16:43:26 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*les espaces doivent etre entoures de 1 ou d'autres espaces*/
void	check_map_space(t_cub *cub, int i, int j)
{
	if (cub->map[i][j] == ' ')
	{
		if (i < cub->map_height - 1 && !is_null(cub->map, i + 1, j)
			&& cub->map[i + 1][j] != ' ' && cub->map[i + 1][j] != '1')
			exit_error(cub, "The map is not closed (1)");
		if (i > 0 && !is_null(cub->map, i - 1, j) && cub->map[i - 1][j] != ' '
			&& cub->map[i - 1][j] != '1')
			exit_error(cub, "The map is not closed (2)");
		if (j > 0 && !is_null(cub->map, i, j - 1) && cub->map[i][j - 1] != ' '
			&& cub->map[i][j - 1] != '1')
			exit_error(cub, "The map is not closed (3)");
		if (!is_null(cub->map, i, j + 1) && cub->map[i][j + 1] != ' '
			&& cub->map[i][j + 1] != '1')
			exit_error(cub, "The map is not closed (4)");
	}
}

/*player direction*/
void	set_direction(t_cub *cub, char elem)
{
	double	plane_angle;

	if (elem == 'N')
		cub->player.angle = -PI / 2;
	else if (elem == 'S')
		cub->player.angle = PI / 2;
	else if (elem == 'E')
		cub->player.angle = 0;
	else if (elem == 'W')
		cub->player.angle = PI;
}

/*init the player position and direction
the map should only contain one N, S, E or W (player position)
the map should only contain 0, 1 and D (for doors)*/
void	check_map_elem(t_cub *cub, char elem, int i, int j)
{
	if (is_in(elem, "NSEW"))
	{
		if (cub->player.x == -1 || cub->player.y == -1)
		{
			cub->player.x = j * BLOCK + BLOCK / 2 - PLAYER_SIZ / 2;
			cub->player.y = i * BLOCK + BLOCK / 2 - PLAYER_SIZ / 2;
			cub->player.x0 = max(0, (int)(cub->player.x - FIX_MAP_X));
			cub->player.y0 = max(0, (int)(cub->player.y - FIX_MAP_Y));
			set_direction(cub, elem);
		}
		else
			exit_error(cub, "There should be only one player\n");
	}
	else if (elem != '0' && elem != '1' && elem != 'D' && !is_space(elem))
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
		cub->j = 0;
		while (cub->map[cub->i][cub->j])
		{
			if (cub->map[cub->i][cub->j] == ' ')
				check_map_space(cub, cub->i, cub->j);
			if ((cub->i == 0 || cub->i == cub->map_height - 1)
				&& cub->map[cub->i][cub->j] != '1'
				&& cub->map[cub->i][cub->j] != ' ')
				exit_error(cub, "The map is not closed");
			if ((cub->j == 0 || !cub->map[cub->i][cub->j + 1])
				&& cub->map[cub->i][cub->j] != '1'
				&& cub->map[cub->i][cub->j] != ' ')
				exit_error(cub, "The map is not closed");
			if (cub->i > 0 && cub->i < cub->map_height - 1 && cub->j > 0)
				check_map_elem(cub, cub->map[cub->i][cub->j], cub->i, cub->j);
			cub->j++;
		}
		cub->i++;
	}
	if (cub->player.x == -1 || cub->player.y == -1)
		exit_error(cub, "There is no player\n");
}
