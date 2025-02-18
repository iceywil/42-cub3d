/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:19:24 by kimnguye          #+#    #+#             */
/*   Updated: 2025/02/18 13:58:58 by kimnguye         ###   ########.fr       */
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
if player is in the bottom of the map, we can start y0 higher.
otherwise, y0 is max(0, cub->pos_y - MAX_PIXEL / 2)*/
int	fix_y(t_cub *cub)
{
	int	y0;

	y0 = cub->player.y - FIX_MAP_Y;
	y0 = max(0, y0);
	return (y0);
}

/*first row: determine the first row of the map to display
regarding the position of the player on the map.
if player is in the bottom of the map, we can start i0 higher.
otherwise, i0 is max(0, cub->pos_y - MAX_PIXEL / 2)*/
/* int	ft_fix_row_i(t_cub *cub)
{
	int	i0;

	i0 = cub->pos_i - FIX_MAP_I;
	if (cub->pos_i + FIX_MAP_I > cub->map_height)
		i0 = cub->pos_i - FIX_MAP_I - (cub->pos_i
				+ FIX_MAP_I - cub->map_height);
	i0 = max(0, i0);
	return (i0);
}
int	fix_i;
int	fix_j;

fix_j = max(0, (int) (cub->pos_j - FIX_MAP_I));
fix_i = ft_fix_row_i(cub);
ft_printf("fix_j = %i, fix_i = %i;\n", fix_j, fix_i);
ft_printf("player.j = %i, player.i = %i;\n", cub->pos_j, cub->pos_i);
*/

void	draw_map(t_cub *cub)
{
	int	j;
	int	i;
	int	x0;
	int	y0;

	x0 = max(0, (int) (cub->player.x - FIX_MAP_X));
	y0 = fix_y(cub);
	printf("player.x = %f, player.y = %f;\n", cub->player.x, cub->player.y);
	ft_printf("x0 = %i, y0 = %i;\n", x0, y0);
	printf("corr: player.x = %f / %i, player.y = %f / %i;\n",
		cub->player.x - x0, MAP_WIDTH, cub->player.y - y0, MAP_HEIGHT);
	draw_player(&cub->mini_map, cub->player.x - x0, cub->player.y - y0, GREEN);
	i = y0 / BLOCK;
	while (cub->map[i])
	{
		j = x0 / BLOCK;
		while (cub->map[i][j])
		{
			if (cub->map[i][j] == '1')
			{
				draw_square(cub, (j * BLOCK - x0), (i * BLOCK - y0), BLUE);
			}
			j++;
		}
		i++;
	}
}
