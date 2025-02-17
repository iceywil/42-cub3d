/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 15:59:18 by a                 #+#    #+#             */
/*   Updated: 2025/02/17 11:40:27 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	player_update(int key, t_player *player)
{
	ft_printf("player is moving\n");
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
	else
		ft_printf("key %i has been pressed\n", key);
	draw_loop(cub);
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
