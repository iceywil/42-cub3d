/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:28:52 by kimnguye          #+#    #+#             */
/*   Updated: 2025/02/21 23:29:08 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	print_rgb_components(int rgb)
{
	int	red;
	int	green;
	int	blue;

	red = (rgb >> 16) & 0xFF;
	green = (rgb >> 8) & 0xFF;
	blue = rgb & 0xFF;
	printf("Red: %d\n", red);
	printf("Green: %d\n", green);
	printf("Blue: %d\n", blue);
}

unsigned long	get_time(void)
{
	struct timespec	ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (unsigned long)(ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}

void	draw_line(t_img *img, int x, int drawStart, int drawEnd, int color)
{
	while (drawStart < drawEnd)
	{
		put_pixel(img, x, drawStart, color);
		drawStart++;
	}
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	int	index;

	if (x >= img->width || y >= img->height || x < 0 || y < 0)
		return ;
	index = y * img->size_line + x * img->bpp / 8;
	img->addr[index] = color & 0xFF;
	img->addr[index + 1] = (color >> 8) & 0xFF;
	img->addr[index + 2] = (color >> 16) & 0xFF;
}
