/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_mini_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:01:19 by kimnguye          #+#    #+#             */
/*   Updated: 2025/02/14 13:33:25 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*si le player sort de la carte lors dun mouvement,
il faut recharger la carte en le mettant a gauche*/

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

/*dessiner la mini-carte:
effacer lancienne carte
centrer la carte sur le personnage
verifier que la carte ne depasse pas la taille max*/
void	ft_mini_map(t_cub *cub)
{
	ft_erase_map(cub);
	ft_center_map(cub);
	mlx_put_image_to_window(cub->mlx, cub->win,
		cub->mini_carte.mlx, 0, HEIGHT / 5 * 4);
}

/*first row: determine the first row of the map to display
regarding the position of the player on the map.
if player is in the bottom of the map, we can start i0 higher.
otherwise, i0 is max(0, cub->pos_y - MAX_PIXEL / 2)*/
int	ft_first_row(t_cub *cub)
{
	int	i0;

	i0 = (int)cub->pos_y - MAX_PIXEL / 2;
	if ((int)cub->pos_y + MAX_PIXEL / 2 > cub->map_height)
		i0 = (int)cub->pos_y - MAX_PIXEL / 2 - ((int)cub->pos_y
				+ MAX_PIXEL / 2 - cub->map_height);
	i0 = ft_max(0, i0);
	return (i0);
}

/*put one element by one element of the map*/
void	ft_map_grid(t_cub *cub, int i0, int j0)
{
	int	x;
	int	y;

	x = cub->x - j0;
	y = cub->i - i0;
	if (cub->map[cub->i][cub->x] == '1')
		big_pixel(cub, y * PIXEL, x * PIXEL, RED);
	else
		big_pixel(cub, y * PIXEL, x * PIXEL, BLACK);
	if ((int) cub->pos_x == cub->x && (int) cub->pos_y == cub->i)
		if (!player_pixel(cub, y * PIXEL, x * PIXEL, BLUE))
			ft_printf("le player nest pas visible sur la map\n");
}

/*centrer la carte sur le player*/
void	ft_center_map(t_cub *cub)
{
	int	j0;
	int	i0;

	j0 = ft_max(0, (int)cub->pos_x - MAX_PIXEL / 2);
	i0 = ft_first_row(cub);
	cub->i = 0;
	while (cub->i < cub->map_height)
	{
		cub->x = j0;
		while (cub->map[cub->i][cub->x])
		{
			ft_map_grid(cub, i0, j0);
			cub->x++;
		}
		cub->i++;
	}
	ft_miniray(cub, i0, j0);
}


void	miniray(t_cub *cub, float start_x)
{
	(void)start_x;
	double	ray_x;
	double	ray_y;

	ray_x = cub->pos_x;
	ray_y = cub->pos_y;
	while(!ft_touch(ray_x, ray_y, cub))
	{
		printf("test: (%f,%f)\n", ray_x, ray_y);
		if (isin_img(ray_x, ray_y, MAP_WIDTH, MAP_HEIGHT))
			pixel_to_img(&cub->img, ray_x, ray_y, GREEN);
		ray_x += cos(cub->dir_angle);
		ray_y += sin(cub->dir_angle);
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.mlx, 0, 0);
}
