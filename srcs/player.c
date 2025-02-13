/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:25:32 by kimnguye          #+#    #+#             */
/*   Updated: 2025/02/13 20:30:04 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*return the first significant column j*/
int	col(t_cub *cub)
{
	int	i;
	int	j;

	j = 0;
	while (j < cub->map_width)
	{
		i = 0;
		while (i < cub->map_height)
		{
			if (cub->map[i][j] != ' ')
				return (j);
			i++;
		}
		j++;
	}
	return (j);
}

/*on centre i et j sur le player;
on affiche les differents rayons avec un pas de 0.1*/
void	miniray(t_cub *cub, int i0, int j0)
{
	int		i;
	int		j;
	double	angle;
	double	k;

	j = (cub->pos_x - j0) * PIXEL + (PIXEL / 2);
	i = (cub->pos_y - i0) * PIXEL + (PIXEL / 2);
	k = MARGIN * PIXEL * 1.2;
	angle = cub->dir_angle - M_PI / 4;
	while (angle <= cub->dir_angle + M_PI / 4)
	{
		segment(cub, j, i, j + (int)(cos(angle) * k), i + (int)(sin(angle)
				* k));
		angle += 0.1;
	}
}

/*on centre i et j sur le player;
on affiche les differents rayons avec un pas de 0.1*/
// void	ft_miniray(t_cub *cub, int i0, int j0)
// {
// 	int		i;
// 	int		j;
// 	double	angle;
// 	double	dir_x;
// 	double	dir_y;
// 	double 	k;

// 	j = (cub->pos_x - j0) * PIXEL + (PIXEL / 2);
// 	i = (cub->pos_y - i0) * PIXEL + (PIXEL / 2);
// 	k = MARGIN * PIXEL * 1.2;
// 	angle = cub->dir_angle - M_PI / 4;
// 	while (angle <= cub->dir_angle + M_PI / 4)
// 	{
// 		//dir_x = cos(angle) * k;
// 		//dir_y = sin(angle) * k;
// 		ft_segment(cub, j, i,
//			j + (int)(cos(angle) * k), i + (int)(sin(angle) * k));
// 		angle += 0.1;
// 	}
// }

// translation: on centre + on decale
/* draw the player_big_pixel (floor + player)
return 0 if the player pixel is not on the map*/
int	player_pixel(t_cub *cub, int i, int j, int color)
{
	int	x;
	int	y;
	int	trans;

	big_pixel(cub, i, j, WHITE);
	trans = (PIXEL / 2) - (PLAYER_SIZ / 2);
	j += trans;
	i += trans;
	x = j;
	while (x < j + PLAYER_SIZ)
	{
		y = i - 1;
		while (++y < i + PLAYER_SIZ)
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
