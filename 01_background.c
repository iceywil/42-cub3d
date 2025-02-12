/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_background.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:06:32 by kimnguye          #+#    #+#             */
/*   Updated: 2025/02/12 12:19:00 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*put rgb pixel to img*/
void	rgb_pixel(t_img *img, int x, int y, t_rgb rgb)
{
	int	pixel;

	pixel = (y * img->line) + (x * (img->bpp / 8));
	img->addr[pixel] = rgb.b;
	img->addr[pixel + 1] = rgb.g;
	img->addr[pixel + 2] = rgb.r;
}

void	ft_ceiling(t_cub *cub, int height)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < WIDTH)
			rgb_pixel(&cub->img, j++, i, cub->c);
		i++;
	}
	mlx_put_image_to_window(cub->mlx, cub->win,
		cub->img.mlx, 0, 0);
}

/*fill the whole background with the floor color*/
void	ft_floor(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
			rgb_pixel(&cub->img, j++, i, cub->f);
		i++;
	}
	mlx_put_image_to_window(cub->mlx, cub->win,
		cub->img.mlx, 0, 0);
}

void	ft_background(t_cub *cub)
{
	ft_floor(cub);
	ft_ceiling(cub, HEIGHT / 2);
}
