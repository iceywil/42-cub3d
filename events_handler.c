/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:56:55 by kimnguye          #+#    #+#             */
/*   Updated: 2025/02/04 17:49:59 by kimnguye         ###   ########.fr       */
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

void	ft_deplacement(int key, t_cub *cub)
{
	if (key == KEY_W)
		ft_printf("player is moving forward\n");
	else if (key == KEY_A)
		ft_printf("player is moving on the left\n");
	else if (key == KEY_S)
		ft_printf("player is moving backward\n");
	else if (key == KEY_D)
		ft_printf("player is moving on the right\n");
}

void	ft_shoot(t_cub *cub)
{
	ft_printf("player is shooting\n");
}

int	key_hook(int key, t_cub *cub)
{
	if (key == ESC || key == KEY_Q || key == KEY_Q_MAC)
		ft_close_all(cub);
	else if (key == KEY_W || key == KEY_A || key == KEY_S || key == KEY_D)
		ft_deplacement(key, cub);
	else if (key == SPACE)
		ft_shoot(cub);
	else
		ft_printf("la touche %i a été utilisée\n", key);
	return (0);
}
