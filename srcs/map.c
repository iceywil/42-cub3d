/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:19:24 by kimnguye          #+#    #+#             */
/*   Updated: 2025/02/17 12:19:53 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_square(t_cub *cub, int x, int y, int size, int color)
{
	int	i;

	i = 0;
	while (i < size && x + i < MAP_WIDTH && x + size < MAP_WIDTH && y
		+ i < MAP_HEIGHT && y + size < MAP_HEIGHT)
	{
		put_pixel(&cub->mini_map, x + i, y, color);
		put_pixel(&cub->mini_map, x, y + i, color);
		put_pixel(&cub->mini_map, x + size, y + i, color);
		put_pixel(&cub->mini_map, x + i, y + size, color);
		i++;
	}
}

void	draw_map(t_cub *cub)
{
	int	x;
	int	y;

	y = 0;
	while (cub->map[y])
	{
		x = 0;
		while (cub->map[y][x])
		{
			if (cub->map[y][x] == '1')
			{
				draw_square(cub, x * BLOCK, y * BLOCK, BLOCK, BLUE);
			}
			x++;
		}
		y++;
	}
}