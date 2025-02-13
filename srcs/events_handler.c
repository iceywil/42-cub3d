/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:56:55 by kimnguye          #+#    #+#             */
<<<<<<< HEAD:srcs/events_handler.c
/*   Updated: 2025/02/11 03:28:09 by a                ###   ########.fr       */
=======
/*   Updated: 2025/02/12 13:28:48 by kimnguye         ###   ########.fr       */
>>>>>>> kim:events_handler.c
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
	ft_mini_map(cub);
}

/*ne pas sortir de lecran et ne pas cogner un mur*/
void	movements(int key, t_cub *cub)
{
	if (key == KEY_W)
	{
<<<<<<< HEAD:srcs/events_handler.c
		if (cub->player_y > 0 && cub->map[cub->player_y
			- 1][cub->player_x] == '0')
=======
		if (cub->pos_y > 0 && cub->map[(int)cub->pos_y - 1][(int)cub->pos_x] == '0')
>>>>>>> kim:events_handler.c
		{
			cub->map[(int)cub->pos_y--][(int)cub->pos_x] = '0';
			ft_printf("player is moving forward\n");
		}
	}
	else if (key == KEY_A)
	{
<<<<<<< HEAD:srcs/events_handler.c
		if (cub->player_x > 0 && cub->map[cub->player_y][cub->player_x
			- 1] == '0')
=======
		if (cub->pos_x > 0 && cub->map[(int)cub->pos_y][(int)cub->pos_x - 1] == '0')
>>>>>>> kim:events_handler.c
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
<<<<<<< HEAD:srcs/events_handler.c
	draw_map(cub);
=======
	ft_mini_map(cub);
>>>>>>> kim:events_handler.c
}

void	shoot(t_cub *cub)
{
	ft_printf("player is shooting\n");
}

int	key_hook(t_cub *cub, int key)
{
	if (key == ESC || key == KEY_Q || key == KEY_Q_MAC)
<<<<<<< HEAD:srcs/events_handler.c
		close_all(cub);
	else if (key == KEY_W || key == KEY_A || key == KEY_S || key == KEY_D
		|| key == LEFT || key == TOP || key == RIGHT || key == BOTTOM)
		movements(key, cub);
=======
		ft_close_all(cub);
	else if (key == KEY_W || key == KEY_A || key == KEY_S || key == KEY_D)
		ft_deplacement(key, cub);
	else if (key == RIGHT || key == LEFT)
		ft_update_dir(key, cub);
>>>>>>> kim:events_handler.c
	else if (key == SPACE)
		shoot(cub);
	else
		ft_printf("la touche %i a été utilisée\n", key);
	return (0);
}
