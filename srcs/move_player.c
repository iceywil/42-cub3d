/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:11:07 by kimnguye          #+#    #+#             */
/*   Updated: 2025/02/17 16:35:03 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

float	new_y(t_player *player)
{
	float y;

	y = player->y;
	if (player->key_up)
		return (y + sin(player->angle) * SPEED);
	if (player->key_left)
		return (y - cos(player->angle) * SPEED);
	if (player->key_down)
		return (y - sin(player->angle) * SPEED);
	if (player->key_right)
		return (y + cos(player->angle) * SPEED);
	return (player->y);
}

float	new_x(t_player *player)
{
	float x;

	x = player->x;
	if (player->key_up)
		return (x + cos(player->angle) * SPEED);
	if (player->key_left)
		return (x + sin(player->angle) * SPEED);
	if (player->key_down)
		return (x - cos(player->angle) * SPEED);
	if (player->key_right)
		return (x - sin(player->angle) * SPEED);
	return (player->x);
}
// implement walls blocking movements ? Check if Pos == '1',
// if true set pos to wall pos

void	move_player(t_player *player, t_cub *cub)
{
	if (player->left_rotate)
		player->angle -= ROT_SPEED;
	if (player->right_rotate)
		player->angle += ROT_SPEED;
	if (player->angle > 2 * PI)
		player->angle -= 2 * PI;
	else if (player->angle < - 2 * PI)
		player->angle += 2 * PI;
	// fix N Player
	/* 	if (player->angle < 0)
			player->angle = 2 * PI; */
	float	x;
	float	y;

	x = new_x(player);
	y = new_y(player);
	ft_printf("old map[%i][%i]=%c\n", (int) player->y / BLOCK, (int)player->x / BLOCK, cub->map[(int) player->y / BLOCK][(int)player->x / BLOCK]);
	ft_printf("new map[%i][%i]=%c\n", (int) y / BLOCK, (int)x / BLOCK, cub->map[(int)y / BLOCK][(int)x / BLOCK]);
	// if ((y >= 0 && x >= 0 && cub->map[(int)y / BLOCK][(int)x / BLOCK] != '1'))
	// {
	// 	player->x = x;
	// 	player->y = y;
	// }
	if (y < 0 || x < 0)
		return ;
	if (x > player->x || y > player->y)
	{	
		if (cub->map[(int)(y + PLAYER_SIZ)/ BLOCK][(int)(x + PLAYER_SIZ)/ BLOCK] == '1')
			return ;
	}
	else 
	{
		if (cub->map[(int)y / BLOCK][(int)x / BLOCK] == '1')
			return ;
	}
	player->x = x;
	player->y = y;
	printf("player new pos: (%f,%f)\n", player->x, player->y);
}
