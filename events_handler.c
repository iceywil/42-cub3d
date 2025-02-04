/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:56:55 by kimnguye          #+#    #+#             */
/*   Updated: 2025/02/04 16:11:21 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		mouse_hook(int button, int x, int y, t_cub *cub);
int		key_hook(int key, t_cub *cub);
int		ft_rot_handler(int key, t_cub *cub);

/*mouse events hendler; (x, y) are the coordinates of the click in the window,
and button tells you which mouse button was pressed*/
int	mouse_hook(int button, int x, int y, t_cub *cub)
{
	(void) x;
	(void) y;
	if (button == SCROLL_UP)
		cub->mlx = cub->mlx;
	// else if (button == SCROLL_DOWN)
	// 	param->zoom *= ZOOM_MINUS;
	// else if (button == RIGHT_CLICK)
	// 		param->rot_iso -= ANGLE_ROT;
	// else if (button == LEFT_CLICK)
	// 		param->rot_iso += ANGLE_ROT;
	return (0);
}

//fct called by mlx_key_hook
int	key_hook(int key, t_cub *cub)
{
	if (key == ESC || key == KEY_Q || key == KEY_Q_MAC)
		ft_close_all(cub);
	// else if (key == ENTER)
	// 	ft_iso_view(param);
	// else if (key == SPACE)
	// 	ft_above_view(param);
	//else if ((key >= LEFT && key <= BOTTOM) || (key >= NUM_7 && key <= NUM_1))
	// {
	// 	ft_rot_handler(key, param);
	// 	if (key == NUM_8)
	// 		param->altitude *= ZOOM_PLUS;
	// 	else if (key == NUM_2)
	// 		param->altitude *= ZOOM_MINUS;
	// 	ft_calc_view(param);
	// }
	else
		ft_printf("la touche %i a été utilisée\n", key);
	return (0);
}

/*returns rotation code*/
int	ft_rot_handler(int key, t_cub *param)
{
	if (key == NUM_7)
		param->mlx = param->mlx;
	// else if (key == NUM_9)
	// 	param->rot_z += ANGLE_ROT;
	// else if (key == NUM_4)
	// 	param->rot_y += ANGLE_ROT;
	// else if (key == NUM_6)
	// 	param->rot_y -= ANGLE_ROT;
	// else if (key == NUM_1)
	// 	param->rot_x -= ANGLE_ROT;
	// else if (key == NUM_3)
	// 	param->rot_x += ANGLE_ROT;
	else
		return (0);
	return (ROT_CODE);
}