/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 15:59:18 by a                 #+#    #+#             */
/*   Updated: 2025/03/05 23:05:49 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	player_update(int key, t_player *player)
{
	if (key == W)
		player->key_up = true;
	if (key == S)
		player->key_down = true;
	if (key == A)
		player->key_left = true;
	if (key == D)
		player->key_right = true;
	if (key == LEFT)
		player->left_rotate = true;
	if (key == RIGHT)
		player->right_rotate = true;
}

int	key_press(int key, t_cub *cub)
{
	if (key == W || key == S || key == A || key == D)
		player_update(key, &cub->player);
	else if (key == LEFT || key == RIGHT)
		player_update(key, &cub->player);
	else if (key == ESC || key == Q || key == KEY_Q_MAC)
		close_all(cub);
	else if (key == M && !cub->map_show)
		cub->map_show = true;
	else if (key == M && cub->map_show)
		cub->map_show = false;
	else if (key == T && !cub->tex_show)
		cub->tex_show = true;
	else if (key == T && cub->tex_show)
		cub->tex_show = false;
	else if (key == O && is_door_forward(cub->map, cub->player))
		door_action(cub->map, cub->player);
	return (0);
}

int	key_release(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = false;
	if (keycode == S)
		player->key_down = false;
	if (keycode == A)
		player->key_left = false;
	if (keycode == D)
		player->key_right = false;
	if (keycode == LEFT)
		player->left_rotate = false;
	if (keycode == RIGHT)
		player->right_rotate = false;
	return (0);
}
