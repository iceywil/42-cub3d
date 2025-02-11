/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_check_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 19:02:10 by kimnguye          #+#    #+#             */
/*   Updated: 2025/02/11 15:47:59 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*les espaces doivent etre entoures de 1 ou d'autres espaces*/
void	check_map_space(t_cub *cub, int i, int j)
{
	if (cub->map[i][j] == ' ')
	{
		if (i < cub->map_height - 1 && cub->map[i + 1][j]
			&& cub->map[i + 1][j] != ' '
			&& cub->map[i + 1][j] != '1')
			exit_error(cub, "Error: the map is not closed");
		if (i > 0 && cub->map[i - 1][j]
			&& cub->map[i - 1][j] != ' '
			&& cub->map[i - 1][j] != '1')
			exit_error(cub, "Error: the map is not closed");
		if (j > 0 && cub->map[i][j - 1]
			&& cub->map[i][j - 1] != ' '
			&& cub->map[i][j - 1] != '1')
			exit_error(cub, "Error: the map is not closed");
		if (cub->map[i][j + 1]
			&& cub->map[i][j + 1] != ' '
			&& cub->map[i][j + 1] != '1')
			exit_error(cub, "Error: the map is not closed");
	}
}

void	set_direction(t_cub *cub, char elem)
{
	double	plane_angle;
	
	if (elem == 'N')
		cub->dir_angle = - M_PI / 2;
	else if (elem == 'S')
		cub->dir_angle = M_PI / 2;
	else if (elem == 'E')
		cub->dir_angle = 0;
	else if (elem == 'W')
		cub->dir_angle = M_PI;
	cub->dir_x = cos(cub->dir_angle);
	cub->dir_y = sin(cub->dir_angle);
	plane_angle = cub->dir_angle + M_PI / 2;
	cub->plane_x = cos(plane_angle); 
	cub->plane_y = sin(plane_angle);
}

/*the map should only contain one N, S, E or W
the map should only contain 0 and 1 except for the player position*/
void	check_map_element(t_cub *cub, char elem, int i, int j)
{
	if (isin(elem, "NSEW"))
	{
		if (cub->dir_x == UNSET_DOUBLE || cub->dir_y == UNSET_DOUBLE)
		{
			cub->pos_x = j;
			cub->pos_y = i;
			set_direction(cub, elem);
		}
		else
			exit_error(cub, "Error: there should be only one player");
	}
	else if (elem != '0' && elem != '1' && !is_space(elem))
		exit_error(cub, "Error: unknown element in map");
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
				exit_error(cub, "Error: the map is not closed");
			if ((cub->x == 0 || !cub->map[cub->i][cub->x + 1])
				&& cub->map[cub->i][cub->x] != '1'
				&& cub->map[cub->i][cub->x] != ' ')
				exit_error(cub, "Error: the map is not closed");
			if (cub->i > 0 && cub->i < cub->map_height - 1 && cub->x > 0)
				check_map_element(cub, cub->map[cub->i][cub->x], cub->i, cub->x);
			cub->x++;
		}
		cub->i++;
	}
	if (cub->dir_x == UNSET_DOUBLE || cub->dir_x == UNSET_DOUBLE)
		exit_error(cub, "Error: there is no player\n");
}
