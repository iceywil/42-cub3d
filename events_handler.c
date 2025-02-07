/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:56:55 by kimnguye          #+#    #+#             */
/*   Updated: 2025/02/07 16:22:36 by kimnguye         ###   ########.fr       */
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

/*ne pas sortir de lecran et ne pas cogner un mur*/
void	ft_deplacement(int key, t_cub *cub)
{
	if (key == KEY_W || key == TOP)
	{
		if (cub->player_y > 0 && cub->map[cub->player_y - 1][cub->player_x] == '0')
		{
			cub->map[cub->player_y][cub->player_x] = '0';
			cub->player_y--;
			cub->map[cub->player_y][cub->player_x] = cub->player_dir;
			ft_printf("player is moving forward\n");
		}
	}
	else if (key == KEY_A || key == LEFT)
	{
		if (cub->player_x > 0 && cub->map[cub->player_y][cub->player_x - 1] == '0')
		{
			cub->map[cub->player_y][cub->player_x] = '0';
			cub->player_x--;
			cub->map[cub->player_y][cub->player_x] = cub->player_dir;
			ft_printf("player is moving on the left\n");
		}
	}
	else if (key == KEY_S || key == BOTTOM)
	{
		if (cub->map[cub->player_y + 1][cub->player_x] == '0')
		{
			cub->map[cub->player_y][cub->player_x] = '0';
			cub->player_y++;
			cub->map[cub->player_y][cub->player_x] = cub->player_dir;
			ft_printf("player is moving backward\n");
		}
	}
	else if (key == KEY_D || key == RIGHT)
	{
		if (cub->map[cub->player_y][cub->player_x + 1] == '0')
		{
			cub->map[cub->player_y][cub->player_x] = '0';
			cub->player_x++;
			cub->map[cub->player_y][cub->player_x] = cub->player_dir;
			ft_printf("player is moving on the right\n");
		}
	}
	ft_draw_map(cub);
}

void	ft_shoot(t_cub *cub)
{
	ft_printf("player is shooting\n");
}

int	key_hook(int key, t_cub *cub)
{
	if (key == ESC || key == KEY_Q || key == KEY_Q_MAC)
		ft_close_all(cub);
	else if (key == KEY_W || key == KEY_A || key == KEY_S || key == KEY_D
		|| key == LEFT || key == TOP || key == RIGHT || key == BOTTOM)
		ft_deplacement(key, cub);
	else if (key == SPACE)
		ft_shoot(cub);
	else
		ft_printf("la touche %i a été utilisée\n", key);
	return (0);
}
