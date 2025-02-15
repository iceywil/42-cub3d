/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:56:55 by kimnguye          #+#    #+#             */
/*   Updated: 2025/02/14 17:11:19 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*mouse events hendler; (x, y) are the coordinates of the click in the window,
and button tells you which mouse button was pressed*/
int	mouse_hook(t_cub *cub, int button, int x, int y)
{
	(void)x;
	(void)y;
	if (button == SCROLL_UP)
		cub->x *= ZOOM_PLUS;
	else if (button == SCROLL_DOWN)
		cub->x *= ZOOM_MINUS;
	return (0);
}

/*change direction*/
void	update_dir(int key, t_cub *cub)
{
	if (key == LEFT)
	{
		printf("player is turning on his left:\nold angle=%f; ",
			cub->dir_angle);
		cub->dir_angle -= ANGLE_ROT;
		cub->dir_x = cos(cub->dir_angle);
		cub->dir_y = sin(cub->dir_angle);
		printf("new angle=%f;\n", cub->dir_angle);
	}
	else if (key == RIGHT)
	{
		printf("player is turning on his left:\nold angle=%f; ",
			cub->dir_angle);
		cub->dir_angle += ANGLE_ROT;
		cub->dir_x = cos(cub->dir_angle);
		cub->dir_y = sin(cub->dir_angle);
		printf("new angle=%f;\n", cub->dir_angle);
	}
	mini_map(cub);
}

/*ne pas sortir de lecran et ne pas cogner un mur*/
void	movements(int key, t_cub *cub)
{
	if (key == KEY_W)
	{
		if (cub->pos_y > 0 && cub->map[(int)cub->pos_y
			- 1][(int)cub->pos_x] == '0')
		{
			cub->map[(int)cub->pos_y--][(int)cub->pos_x] = '0';
			ft_printf("player is moving forward\n");
		}
	}
	else if (key == KEY_A)
	{
		if (cub->pos_x > 0 && cub->map[(int)cub->pos_y][(int)cub->pos_x
			- 1] == '0')
		{
			cub->map[(int)cub->pos_y][(int)cub->pos_x--] = '0';
			ft_printf("player is moving on the left\n");
		}
	}
	else if (key == KEY_S)
	{
		if (cub->map[(int)cub->pos_y + 1][(int)cub->pos_x] == '0')
		{
			cub->map[(int)cub->pos_y++][(int)cub->pos_x] = '0';
			ft_printf("player is moving backward\n");
		}
	}
	else if (key == KEY_D)
	{
		if (cub->map[(int)cub->pos_y][(int)cub->pos_x + 1] == '0')
		{
			cub->map[(int)cub->pos_y][(int)cub->pos_x++] = '0';
			ft_printf("player is moving on the right\n");
		}
	}
	mini_map(cub);
}

void	shoot(t_cub *cub)
{
	ft_printf("player is shooting\n");
}

int	key_hook(t_cub *cub, int key)
{
	ft_printf("la touche %i a été utilisée\n", key);
	if (key == ESC || key == KEY_Q || key == KEY_Q_MAC)
		close_all(cub);
	else if (key == KEY_W || key == KEY_A || key == KEY_S || key == KEY_D)
		movements(key, cub);
	else if (key == RIGHT || key == LEFT)
		update_dir(key, cub);
	else if (key == SPACE)
		shoot(cub);
	else
		ft_printf("la touche %i a été utilisée\n", key);
	return (0);
}
