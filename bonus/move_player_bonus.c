/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:11:07 by kimnguye          #+#    #+#             */
/*   Updated: 2025/02/25 11:37:21 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

float	new_y(t_player *player)
{
	float	y;

	y = player->y;
	if (player->key_up)
		return (y + sin(player->angle) * SPEED);
	if (player->key_left)
		return (y - cos(player->angle) * SPEED);
	if (player->key_down)
		return (y - sin(player->angle) * SPEED);
	if (player->key_right)
		return (y + cos(player->angle) * SPEED);
	return (y);
}

float	new_x(t_player *player)
{
	float	x;

	x = player->x;
	if (player->key_up)
		return (x + cos(player->angle) * SPEED);
	if (player->key_left)
		return (x + sin(player->angle) * SPEED);
	if (player->key_down)
		return (x - cos(player->angle) * SPEED);
	if (player->key_right)
		return (x - sin(player->angle) * SPEED);
	return (x);
}

void	update_angle(t_player *player)
{
	if (player->left_rotate)
		player->angle -= ROT_SPEED;
	if (player->right_rotate)
		player->angle += ROT_SPEED;
	if (player->angle > 2 * PI)
		player->angle -= 2 * PI;
	else if (player->angle < -2 * PI)
		player->angle += 2 * PI;
}

int	is_wall(char **map, float x, float y)
{
	if (x < 0 || y < 0)
		return (1);
	if (is_door_closed(map, x, y))
		return (1);
	if (map[(int)y / BLOCK][(int)x / BLOCK] == '1')
		return (1);
	if (map[(int)(y - PLAYER_SIZ) / BLOCK]
		[(int)(x - PLAYER_SIZ) / BLOCK] == '1')
		return (1);
	if (map[(int)(y - PLAYER_SIZ) / BLOCK]
		[(int)(x + PLAYER_SIZ) / BLOCK] == '1')
		return (1);
	if (map[(int)(y + PLAYER_SIZ) / BLOCK]
		[(int)(x + PLAYER_SIZ) / BLOCK] == '1')
		return (1);
	if (map[(int)(y + PLAYER_SIZ) / BLOCK]
		[(int)(x - PLAYER_SIZ) / BLOCK] == '1')
		return (1);
	return (0);
}

void	move_player(t_player *player, t_cub *cub)
{
	float	x;
	float	y;

	update_angle(player);
	x = new_x(player);
	y = new_y(player);
	if (is_wall(cub->map, x, y))
		return ;
	player->x = x;
	player->y = y;
	player->x0 = max(0, (int)(x - FIX_MAP_X));
	player->y0 = max(0, (int)(y - FIX_MAP_Y));
}
