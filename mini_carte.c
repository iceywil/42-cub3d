/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_carte.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:01:19 by kimnguye          #+#    #+#             */
/*   Updated: 2025/02/06 16:16:30 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*put pixel to img*/
void	pixel_to_img(t_img *img, int x, int y, int color)
{
	int	pixel;

	pixel = (y * img->line) + (x * (img->bpp / 8));
	img->addr[pixel] = color & 0xFF;
	img->addr[pixel + 1] = (color >> 8) & 0xFF;
	img->addr[pixel + 2] = (color >> 16) & 0xFF;
}

/*dessiner la mini-carte*/
void	ft_draw_map(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < cub->map_height)
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (cub->map[i][j] == 1)
				pixel_to_img(&cub->mini_carte,j * ZOOM_INIT, i * ZOOM_INIT, YELLOW);
			if (cub->map[i][j] == 0)
				pixel_to_img(&cub->mini_carte,j * ZOOM_INIT, i * ZOOM_INIT, GREEN);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->mini_carte.mlx, 0, 0);
}
