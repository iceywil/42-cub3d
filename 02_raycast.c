/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 12:11:31 by kimnguye          #+#    #+#             */
/*   Updated: 2025/02/14 13:32:05 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_touch(double px, double py, t_cub *cub);

void ft_draw_square(t_img *img, int x, int y, int color)
{
	int	i;

	i = 1;
	while (i < PIXEL)
	{
		pixel_to_img(img, x + i, y, color);
		pixel_to_img(img, x, y + i, color);
		pixel_to_img(img, x + PIXEL, y + i, color);
		pixel_to_img(img, x + i, y + PIXEL, color);
		i++;
	}
}

int	ft_touch(double px, double py, t_cub *cub)
{
	int x = px;
	int y = py;
	if(cub->map[y][x] == '1')
		return 1;
	return 0;
}
