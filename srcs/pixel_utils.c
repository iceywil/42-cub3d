/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:28:52 by kimnguye          #+#    #+#             */
/*   Updated: 2025/02/13 19:54:42 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*convert one pixel into a big pixel
return 0 if a pixel is out of the image*/
int	big_pixel(t_cub *cub, int i, int j, int color)
{
	int	x;
	int	y;

	x = j;
	while (x < j + PIXEL)
	{
		y = i - 1;
		while (++y < i + PIXEL)
		{
			if (is_in_img(x, y, MAP_WIDTH, MAP_HEIGHT))
				pixel_to_img(cub->mini_map, x, y, color);
			else
				return (0);
		}
		x++;
	}
	return (1);
}

int	is_in_img(int x, int y, int width, int height)
{
	if (x < width && y < height && x >= 0 && y >= 0)
		return (1);
	return (0);
}

/*put pixel to img*/
void	pixel_to_img(t_img *img, int x, int y, int color)
{
	int	pixel;

	pixel = (y * img->size_line) + (x * (img->bpp / 8));
	img->addr[pixel] = color & 0xFF;
	img->addr[pixel + 1] = (color >> 8) & 0xFF;
	img->addr[pixel + 2] = (color >> 16) & 0xFF;
}
