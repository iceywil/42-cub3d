/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:28:52 by kimnguye          #+#    #+#             */
/*   Updated: 2025/02/16 18:07:52 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


int	is_in_img(int x, int y, int width, int height)
{
	if (x < width && y < height && x >= 0 && y >= 0)
		return (1);
	return (0);
}

void	pixel_to_img(t_img *img, int x, int y, int color)
{
	int	pixel;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	pixel = (y * img->size_line) + (x * (img->bpp / 8));
	img->addr[pixel] = color & 0xFF;
	img->addr[pixel + 1] = (color >> 8) & 0xFF;
	img->addr[pixel + 2] = (color >> 16) & 0xFF;
}
