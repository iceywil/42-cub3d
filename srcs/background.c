/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:06:32 by kimnguye          #+#    #+#             */
/*   Updated: 2025/02/14 16:51:56 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*put rgb pixel to img*/
void	rgb_pixel(t_img *img, int x, int y, t_color *rgb)
{
	int	pixel;

	pixel = (y * img->size_line) + (x * (img->bpp / 8));
	img->addr[pixel] = rgb->b;
	img->addr[pixel + 1] = rgb->g;
	img->addr[pixel + 2] = rgb->r;
}

void	ceiling_fill(t_cub *cub, int height)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < WIDTH)
			rgb_pixel(&cub->img, j++, i, &cub->ceiling);
		i++;
	}
	mlx_put_image_to_window(cub->mlx, cub->win,
		cub->img.data, 0, 0);
}

/*fill the whole background with the floor color*/
void	floor_fill(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
			rgb_pixel(&cub->img, j++, i, &cub->floor);
		i++;
	}
	mlx_put_image_to_window(cub->mlx, cub->win,
		cub->img.data, 0, 0);
}

void	background(t_cub *cub)
{
	floor_fill(cub);
	ceiling_fill(cub, HEIGHT / 2);
}
