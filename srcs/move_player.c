/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:11:07 by kimnguye          #+#    #+#             */
/*   Updated: 2025/02/24 05:32:19 by a                ###   ########.fr       */
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

// Define key codes for your environment
#define W_KEY 119
#define S_KEY 115
#define A_KEY 97
#define D_KEY 100
#define LEFT_KEY 65361
#define RIGHT_KEY 65363

int	key_press(int key, t_cub *cub)
{
	ft_printf("Key pressed: %d\n", key);
	if (key == W_KEY)
		cub->key_up = true;
	else if (key == S_KEY)
		cub->key_down = true;
	else if (key == A_KEY)
		cub->key_left = true;
	else if (key == D_KEY)
		cub->key_right = true;
	else if (key == LEFT_KEY)
		cub->left_rotate = true;
	else if (key == RIGHT_KEY)
		cub->right_rotate = true;
	return (0);
}

int	key_release(int key, t_cub *cub)
{
	if (key == W_KEY)
		cub->key_up = false;
	else if (key == S_KEY)
		cub->key_down = false;
	else if (key == A_KEY)
		cub->key_left = false;
	else if (key == D_KEY)
		cub->key_right = false;
	else if (key == LEFT_KEY)
		cub->left_rotate = false;
	else if (key == RIGHT_KEY)
		cub->right_rotate = false;
	ft_printf("Key released: %d\n", cub->key_up);

	return (0);
}

void	move_player(t_cub *cub)
{
	// Debugging output
	//ft_printf("Player position: (%f, %f)\n", cub->pos_x, cub->pos_y);
	ft_printf("Key states: up=%d, down=%d, left=%d, right=%d\n",
		cub->key_up, cub->key_down, cub->key_left, cub->key_right);

	// Handle forward movement
	if (cub->key_up)
	{
		if (cub->map[(int)(cub->pos_x + cub->dir_x * cub->move_speed)][(int)cub->pos_y] == '0')
			cub->pos_x += cub->dir_x * cub->move_speed;
		if (cub->map[(int)cub->pos_x][(int)(cub->pos_y + cub->dir_y * cub->move_speed)] == '0')
			cub->pos_y += cub->dir_y * cub->move_speed;
	}

	// Handle backward movement
	if (cub->key_down)
	{
		if (cub->map[(int)(cub->pos_x - cub->dir_x * cub->move_speed)][(int)cub->pos_y] == '0')
			cub->pos_x -= cub->dir_x * cub->move_speed;
		if (cub->map[(int)cub->pos_x][(int)(cub->pos_y - cub->dir_y * cub->move_speed)] == '0')
			cub->pos_y -= cub->dir_y * cub->move_speed;
	}

	// Handle left strafe
	if (cub->key_left)
	{
		if (cub->map[(int)(cub->pos_x - cub->dir_y * cub->move_speed)][(int)cub->pos_y] == '0')
			cub->pos_x -= cub->dir_y * cub->move_speed;
		if (cub->map[(int)cub->pos_x][(int)(cub->pos_y + cub->dir_x * cub->move_speed)] == '0')
			cub->pos_y += cub->dir_x * cub->move_speed;
	}

	// Handle right strafe
	if (cub->key_right)
	{
		if (cub->map[(int)(cub->pos_x + cub->dir_y * cub->move_speed)][(int)cub->pos_y] == '0')
			cub->pos_x += cub->dir_y * cub->move_speed;
		if (cub->map[(int)cub->pos_x][(int)(cub->pos_y - cub->dir_x * cub->move_speed)] == '0')
			cub->pos_y -= cub->dir_x * cub->move_speed;
	}

	// Handle left rotation
	if (cub->left_rotate)
	{
		cub->old_dir_x = cub->dir_x;
		cub->dir_x = cub->dir_x * cos(-cub->rot_speed) - cub->dir_y * sin(-cub->rot_speed);
		cub->dir_y = cub->old_dir_x * sin(-cub->rot_speed) + cub->dir_y * cos(-cub->rot_speed);
		cub->old_plane_x = cub->plane_x;
		cub->plane_x = cub->plane_x * cos(-cub->rot_speed) - cub->plane_y * sin(-cub->rot_speed);
		cub->plane_y = cub->old_plane_x * sin(-cub->rot_speed) + cub->plane_y * cos(-cub->rot_speed);
	}

	// Handle right rotation
	if (cub->right_rotate)
	{
		cub->old_dir_x = cub->dir_x;
		cub->dir_x = cub->dir_x * cos(cub->rot_speed) - cub->dir_y * sin(cub->rot_speed);
		cub->dir_y = cub->old_dir_x * sin(cub->rot_speed) + cub->dir_y * cos(cub->rot_speed);
		cub->old_plane_x = cub->plane_x;
		cub->plane_x = cub->plane_x * cos(cub->rot_speed) - cub->plane_y * sin(cub->rot_speed);
		cub->plane_y = cub->old_plane_x * sin(cub->rot_speed) + cub->plane_y * cos(cub->rot_speed);
	}
}
