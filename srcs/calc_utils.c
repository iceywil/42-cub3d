/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:43:58 by kimnguye          #+#    #+#             */
/*   Updated: 2025/03/03 16:43:44 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_null(char **map, int i, int j)
{
	int	k;

	k = 0;
	while (map[i] && map[i][k])
		k++;
	if (k <= j)
		return (1);
	return (0);
}

float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

float	fixed_dist(t_player player, float x, float y)
{
	float	delta_x;
	float	delta_y;
	float	angle;
	float	fix_dist;

	delta_x = x - (player.x);
	delta_y = y - (player.y);
	angle = atan2(delta_y, delta_x) - player.angle;
	fix_dist = distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}
