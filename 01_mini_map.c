/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_mini_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:01:19 by kimnguye          #+#    #+#             */
/*   Updated: 2025/02/13 14:56:35 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*si le player sort de la carte lors dun mouvement,
il faut recharger la carte en le mettant a gauche*/

//translation: on centre + on decale
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
			if (isin_img(x, y, MAP_WIDTH, MAP_HEIGHT))
				pixel_to_img(&cub->mini_carte, x, y, color);
			else
				return (0);
		}
		x++;
	}
	return (1);
}

/*return the first significant column j*/
int	ft_col(t_cub *cub)
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
void	ft_miniray(t_cub *cub, int j0)
{
	int		i;
	int		j;
	double	angle;
	double	dir_x;
	double	dir_y;

	j = (cub->pos_x - j0) * PIXEL + (PIXEL / 2);
	i = (cub->pos_y) * PIXEL + (PIXEL / 2);
	angle = cub->dir_angle - M_PI / 4;
	while (angle <= cub->dir_angle + M_PI / 4)
	{
		dir_x = cos(angle) * MARGIN;
		dir_y = sin(angle) * MARGIN;
		ft_segment(cub, j, i, j + (int)(dir_x * PIXEL * 1.2),
			i + (int)(dir_y * PIXEL * 1.2));
		angle += 0.1;
	}
}
/*put one element by one element of the map*/
void	ft_map_grid(t_cub *cub, int i, int j, int j0)
{
	if (cub->map[i][j] == '1')
		big_pixel(cub, (i) * PIXEL, (j - j0) * PIXEL, RED);
	else if (cub->map[i][j] == '0')
		big_pixel(cub, (i) * PIXEL, (j - j0) * PIXEL, WHITE);
	else if (cub->map[i][j] == ' ')
		big_pixel(cub, (i) * PIXEL, (j - j0) * PIXEL, BLACK);
	if (cub->pos_x == j && cub->pos_y == i)
		if (!player_pixel(cub, i * PIXEL, (j - j0) * PIXEL, BLUE))
			ft_printf("le player nest pas visible sur la map\n");
}
	/*on trace le rayon principal*/
	// ft_segment(cub, j, i, j + (int)(cub->dir_x * BIG_PIXEL * 1.2),
	// 	i + (int)(cub->dir_y * BIG_PIXEL * 1.2));

/*puts the res map in black*/
void	ft_erase_map(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;

	while (i < MAP_HEIGHT)
	{
		j = 0;
		while (j < MAP_WIDTH)
			pixel_to_img(&cub->mini_carte, j++, i, BLACK);
		i++;
	}
	mlx_put_image_to_window(cub->mlx, cub->win,
		cub->mini_carte.mlx, 0, HEIGHT / 5 * 4);
}

/*dessiner la mini-carte
verifier que la carte ne depasse pas la taille max*/
void	ft_mini_map(t_cub *cub)
{
	int	i;
	int	j;
	int	j0;

	i = 0;
	j0 = ft_max(ft_col(cub) - 1, 0);
	while (i < cub->map_height)
	{
		j = j0;
		while (cub->map[i][j])
			ft_map_grid(cub, i, j++, j0);
		i++;
	}
	ft_miniray(cub, j0);
	mlx_put_image_to_window(cub->mlx, cub->win,
		cub->mini_carte.mlx, 0, HEIGHT / 5 * 4);
	ft_erase_map(cub);
	ft_center_map(cub);
}

/*first row: determine the first row of the map to display
regarding the position of the player on the map.
if player is in the bottom of the map, we can start i0 higher.
otherwise, i0 is max(0, cub->pos_y - MAX_PIXEL / 2)*/
int	ft_first_row(t_cub *cub)
{
	int	i0;

	if ((int)cub->pos_y + MAX_PIXEL / 2 > cub->map_height)
		i0 = (int)cub->pos_y - MAX_PIXEL / 2 - ((int)cub->pos_y
			+ MAX_PIXEL / 2 - cub->map_height);
	else
		i0 = (int)cub->pos_y - MAX_PIXEL / 2;
	i0 = ft_max(0, i0);
	return (i0);
}

/*dessiner la mini-carte
verifier que la carte ne depasse pas la taille max
centrer la minimap sur le personnage*/
void	ft_center_map(t_cub *cub)
{
	int	i;
	int	j;
	int	j0;

	/*first col*/
	j0 = ft_max(0, (int)cub->pos_x - MAX_PIXEL / 2);
	/*first row*/
	i = ft_first_row(cub);
	ft_printf("i0=%i;j0=%i;\n", i, j0);
	while (i < cub->map_height)
	{
		/*first column*/
		j = j0;
		while (cub->map[i][j])
			ft_map_grid(cub, i, j++, j0);
		i++;
	}
	ft_miniray(cub, j0);
	mlx_put_image_to_window(cub->mlx, cub->win,
		cub->mini_carte.mlx, 0, HEIGHT / 5 * 4);
}
