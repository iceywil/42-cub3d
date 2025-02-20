/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:43:58 by kimnguye          #+#    #+#             */
/*   Updated: 2025/02/20 11:23:07 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
	
	delta_x = x - (player.x + 0); //PLAYER_SIZ / 2
	delta_y = y - (player.y + 0);
	angle = atan2(delta_y, delta_x) - player.angle;
	fix_dist = distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}
