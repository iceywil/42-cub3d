/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:11:07 by kimnguye          #+#    #+#             */
/*   Updated: 2025/02/21 23:38:24 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* float	new_y(t_player *player)
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


 */

#include "../cub3d.h"

int	key_press(int key, t_cub *cub)
{
	if (key == W)
		cub->player.key_up = true;
	if (key == S)
		cub->player.key_down = true;
	if (key == A)
		cub->player.key_left = true;
	if (key == D)
		cub->player.key_right = true;
	if (key == LEFT)
		cub->player.left_rotate = true;
	if (key == RIGHT)
		cub->player.right_rotate = true;
	else
		ft_printf("key %i has been pressed\n", key);
	return (0);
}

int	key_release(int key, t_cub *cub)
{
	if (key == W)
		cub->player.key_up = false;
	if (key == S)
		cub->player.key_down = false;
	if (key == A)
		cub->player.key_left = false;
	if (key == D)
		cub->player.key_right = false;
	if (key == LEFT)
		cub->player.left_rotate = false;
	if (key == RIGHT)
		cub->player.right_rotate = false;
	return (0);
}

void	move_player(t_cub *cub)
{
	// move forward if no wall in front of you
	if (cub->player.key_up)
	{
		if (cub->map[(int)(cub->pos_x + cub->dir_x
				* cub->move_speed)][(int)cub->pos_y] == 0)
			cub->pos_x += cub->dir_x * cub->move_speed;
		if (cub->map[(int)cub->pos_x][(int)(cub->pos_y + cub->dir_y
				* cub->move_speed)] == 0)
			cub->pos_y += cub->dir_y * cub->move_speed;
		printf("pos_x %f\n", cub->pos_x);
	}
	// move backwards if no wall behind you
	if (cub->player.key_down)
	{
		if (cub->map[(int)(cub->pos_x - cub->dir_x
				* cub->move_speed)][(int)cub->pos_y] == 0)
			cub->pos_x -= cub->dir_x * cub->move_speed;
		if (cub->map[(int)cub->pos_x][(int)(cub->pos_y - cub->dir_y
				* cub->move_speed)] == 0)
			cub->pos_y -= cub->dir_y * cub->move_speed;
	}
	// rotate to the right
	if (cub->player.key_right)
	{
		// both camera direction and camera plane must be rotated
		cub->old_dir_x = cub->dir_x;
		cub->dir_x = cub->dir_x * cos(-cub->rot_speed) - cub->dir_y
			* sin(-cub->rot_speed);
		cub->dir_y = cub->old_dir_x * sin(-cub->rot_speed) + cub->dir_y
			* cos(-cub->rot_speed);
		cub->old_plane_x = cub->plane_x;
		cub->plane_x = cub->plane_x * cos(-cub->rot_speed) - cub->plane_y
			* sin(-cub->rot_speed);
		cub->plane_y = cub->old_plane_x * sin(-cub->rot_speed) + cub->plane_y
			* cos(-cub->rot_speed);
	}
	// rotate to the left
	if (cub->player.key_left)
	{
		// both camera direction and camera plane must be rotated
		cub->old_dir_x = cub->dir_x;
		cub->dir_x = cub->dir_x * cos(cub->rot_speed) - cub->dir_y
			* sin(cub->rot_speed);
		cub->dir_y = cub->old_dir_x * sin(cub->rot_speed) + cub->dir_y
			* cos(cub->rot_speed);
		cub->old_plane_x = cub->plane_x;
		cub->plane_x = cub->plane_x * cos(cub->rot_speed) - cub->plane_y
			* sin(cub->rot_speed);
		cub->plane_y = cub->old_plane_x * sin(cub->rot_speed) + cub->plane_y
			* cos(cub->rot_speed);
	}
}
