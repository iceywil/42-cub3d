/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 12:11:31 by kimnguye          #+#    #+#             */
/*   Updated: 2025/02/14 12:57:22 by kimnguye         ###   ########.fr       */
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
	int x = px / PIXEL;
	int y = py / PIXEL;
	if(cub->map[y][x] == '1')
		return 1;
	return 0;
}

void	ft_draw_ray(t_cub *cub, float start_x)
{
	(void)start_x;
	double	ray_x;
	double	ray_y;

	ray_x = cub->pos_x;
	ray_y = cub->pos_y;
	while(!ft_touch(ray_x, ray_y, cub))
	{
		if (isin_img(ray_x, ray_y, MAP_WIDTH, MAP_HEIGHT))
			pixel_to_img(&cub->img, ray_x, ray_y, GREEN);
		ray_x += cos(cub->dir_angle);
		ray_y += sin(cub->dir_angle);
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.mlx, 0, 0);
}
