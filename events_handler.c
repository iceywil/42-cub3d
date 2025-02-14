/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:56:55 by kimnguye          #+#    #+#             */
/*   Updated: 2025/02/14 13:51:46 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		mouse_hook(int button, int x, int y, t_cub *cub);
int		key_hook(int key, t_cub *cub);

/*mouse events hendler; (x, y) are the coordinates of the click in the window,
and button tells you which mouse button was pressed*/
int	mouse_hook(int button, int x, int y, t_cub *cub)
{
	(void) x;
	(void) y;
	if (button == SCROLL_UP)
		cub->x *= ZOOM_PLUS;
	else if (button == SCROLL_DOWN)
		cub->x *= ZOOM_MINUS;
	return (0);
}

/*change direction*/
void	ft_update_dir(int key, t_cub *cub)
{
	if (key == LEFT)
	{
		printf("player is turning on his left:\nold angle=%f; ", cub->dir_angle);
		cub->dir_angle -= ANGLE_ROT;
		cub->dir_x = cos(cub->dir_angle);
		cub->dir_y = sin(cub->dir_angle);
		printf("new angle=%f;\n", cub->dir_angle);
	}
	else if (key == RIGHT)
	{
		printf("player is turning on his left:\nold angle=%f; ", cub->dir_angle);
		cub->dir_angle += ANGLE_ROT;
		cub->dir_x = cos(cub->dir_angle);
		cub->dir_y = sin(cub->dir_angle);
		printf("new angle=%f;\n", cub->dir_angle);
	}
	ft_game_loop(cub);
}

double	new_y(int key, t_cub *cub)
{
	double y;

	y = cub->pos_y;
	if (key == KEY_UP)
		return (y + sin(cub->dir_angle) * SPEED);
	if (key == KEY_A)
		return (y - cos(cub->dir_angle) * SPEED);
	if (key == KEY_S)
		return (y - sin(cub->dir_angle) * SPEED);
	if (key == KEY_D)
		return (y + cos(cub->dir_angle) * SPEED);
}

double	new_x(int key, t_cub *cub)
{
	double x;

	x = cub->pos_x;
	if (key == KEY_UP)
		return (x + cos(cub->dir_angle) * SPEED);
	if (key == KEY_A)
		return (x + sin(cub->dir_angle) * SPEED);
	if (key == KEY_S)
		return (x - cos(cub->dir_angle) * SPEED);
	if (key == KEY_D)
		return (x - sin(cub->dir_angle) * SPEED);
}

/*ne pas sortir de lecran et ne pas cogner un mur*/
void	ft_deplacement(int key, t_cub *cub)
{
	double	x;
	double	y;

	x = new_x(key, cub);
	y = new_y(key, cub);

	if ((y >= 0 && x >= 0 && cub->map[(int)y][(int)x] != '1'))
	{
		cub->map[(int)cub->pos_y][(int)cub->pos_x] = '0';
		cub->pos_x = x;
		cub->pos_y = y;
	}
	ft_game_loop(cub);
}

void	ft_shoot(t_cub *cub)
{
	ft_printf("player is shooting\n");
}

int	key_hook(int key, t_cub *cub)
{
	if (key == ESC || key == KEY_Q || key == KEY_Q_MAC)
		ft_close_all(cub);
	else if (key == KEY_UP || key == KEY_A || key == KEY_S || key == KEY_D)
		ft_deplacement(key, cub);
	else if (key == RIGHT || key == LEFT)
		ft_update_dir(key, cub);
	else if (key == SPACE)
		ft_shoot(cub);
	else
		ft_printf("la touche %i a été utilisée\n", key);
	return (0);
}
