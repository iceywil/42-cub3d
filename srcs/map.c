/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:19:24 by kimnguye          #+#    #+#             */
/*   Updated: 2025/02/17 18:54:27 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

void	draw_player(t_img *img, int x, int y, int color)
{
	int	i;
	int	j;

	j = x;
	while (j < x + PLAYER_SIZ)
	{
		i = y;
		while (i < y + PLAYER_SIZ)
		{
			if (j < MAP_WIDTH && i < MAP_HEIGHT)
				put_pixel(img, j, i, color);
			i++;
		}
		j++;
	}
}

/*draw wall*/
void	draw_square(t_cub *cub, int x, int y, int color)
{
	int	i;

	i = 0;
	while (i < BLOCK && x + i < MAP_WIDTH && x + BLOCK < MAP_WIDTH && y
		+ i < MAP_HEIGHT && y + BLOCK < MAP_HEIGHT)
	{
		put_pixel(&cub->mini_map, x + i, y, color);
		put_pixel(&cub->mini_map, x, y + i, color);
		put_pixel(&cub->mini_map, x + BLOCK, y + i, color);
		put_pixel(&cub->mini_map, x + i, y + BLOCK, color);
		i++;
	}
}

/*first row: determine the first row of the map to display
regarding the position of the player on the map.
if player is in the bottom of the map, we can start i0 higher.
otherwise, i0 is max(0, cub->pos_y - MAX_PIXEL / 2)*/
int	ft_first_row(t_cub *cub)
{
	int	i0;

	i0 = cub->pos_i - MAX_BLOCK / 2;
	if (cub->pos_i + MAX_BLOCK / 2 > cub->map_height)
		i0 = cub->pos_i - MAX_BLOCK / 2 - (cub->pos_i
				+ MAX_BLOCK / 2 - cub->map_height);
	i0 = max(0, i0);
	return (i0);
}

void	draw_map(t_cub *cub)
{
	int	x;
	int	y;
	int	j0;
	int	i0;

	j0 = max(0, (int) (cub->pos_j - MAX_BLOCK / 2));
	ft_printf("j0 = %i\n", (cub->pos_j - MAX_BLOCK / 2));
	i0 = ft_first_row(cub);
	ft_printf("first y: i0= %i, first x: j0= %i;\n", i0, j0);
	y = i0;
	while (cub->map[y])
	{
		x = j0;
		while (cub->map[y][x])
		{
			if (cub->map[y][x] == '1')
			{
				draw_square(cub, (x - j0) * BLOCK, (y - i0) * BLOCK, BLUE);
			}
			x++;
		}
		y++;
	}
}
