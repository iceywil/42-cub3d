/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_carte.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:01:19 by kimnguye          #+#    #+#             */
/*   Updated: 2025/02/04 18:18:14 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*put pixel to map*/
void	pixel_to_map(t_cub *vars, int x, int y, int color)
{
	int	pixel;

	pixel = (y * vars->carte_line) + (x * (vars->carte_pixel / 8));
	vars->carte_data[pixel] = color & 0xFF;
	vars->carte_data[pixel + 1] = (color >> 8) & 0xFF;
	vars->carte_data[pixel + 2] = (color >> 16) & 0xFF;
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
				pixel_to_map(cub,j * ZOOM_INIT, i * ZOOM_INIT, YELLOW);
			if (cub->map[i][j] == 0)
				pixel_to_map(cub,j * ZOOM_INIT, i * ZOOM_INIT, GREEN);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->mini_carte, WIDTH * 4 / 5, HEIGHT * 4 / 5);
}