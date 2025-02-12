/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_mini_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:01:19 by kimnguye          #+#    #+#             */
/*   Updated: 2025/02/12 10:40:22 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define PLAYER_SIZ 6

/*
Pouvoir faire bouger mon personnage avec les flèches dans la minimap (voir les keys à l'étape 4)
Checker si le case sur laquelle je vais me déplacer est un mur ou pas (si == ‘0’) : si oui je peux me déplacer dessus, sinon non
*/

int	isin_img(int x, int y, int width, int height)
{
	if (x < width && y < height && x >= 0 && y >= 0)
		return (1);
	return (0);
}

/*put pixel to img*/
void	pixel_to_img(t_img *img, int x, int y, int color)
{
	int	pixel;

	pixel = (y * img->line) + (x * (img->bpp / 8));
	img->addr[pixel] = color & 0xFF;
	img->addr[pixel + 1] = (color >> 8) & 0xFF;
	img->addr[pixel + 2] = (color >> 16) & 0xFF;
}

/*convert one pixel into a big pixel*/
void	big_pixel(t_cub *cub, int i, int j, int color)
{
	int	x;
	int	y;

	x = j;
	while (x < j + ZOOM_INIT)
	{
		y = i - 1;
		while (++y < i + ZOOM_INIT)
			if (isin_img(x, y, MAP_WIDTH, MAP_HEIGHT))		
				pixel_to_img(&cub->mini_carte, x, y, color);
		x++;
	}
}

/*floor + player*/
void	player_pixel(t_cub *cub, int i, int j, int color)
{
	int	x;
	int	y;
	int	trans;
	
	big_pixel(cub, i, j, WHITE);
	//on centre + on decale
	trans = (ZOOM_INIT / 2) - (PLAYER_SIZ / 2);
	j += trans; 
	i += trans;
	x = j;
	while (x < j + PLAYER_SIZ)
	{
		y = i - 1;
		while (++y < i + PLAYER_SIZ)
			if (isin_img(x, y, MAP_WIDTH, MAP_HEIGHT))		
				pixel_to_img(&cub->mini_carte, x, y, color);
		x++;
	}
}

/*dessiner la mini-carte
verifier que la carte ne depasse pas la taille max*/
void	ft_mini_map(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < cub->map_height)
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (cub->map[i][j] == '1')
				big_pixel(cub, i * ZOOM_INIT, MARGIN + j * ZOOM_INIT, RED);
			else if (cub->map[i][j] == '0')
				big_pixel(cub, i * ZOOM_INIT, MARGIN + j * ZOOM_INIT, WHITE);
			if (cub->pos_x == j && cub->pos_y == i)
				player_pixel(cub, i * ZOOM_INIT, MARGIN + j * ZOOM_INIT, BLUE);
			j++;
		}
		i++;
	}
	//rayon
	//on centre
	j = MARGIN + cub->pos_x * ZOOM_INIT + (ZOOM_INIT / 2);
	i = cub->pos_y * ZOOM_INIT + (ZOOM_INIT / 2);
	//on trace le rayon
	ft_segment(cub, j, i, j + (int)(cub->dir_x * ZOOM_INIT * 1.2),
		i + (int)(cub->dir_y * ZOOM_INIT * 1.2));
	mlx_put_image_to_window(cub->mlx, cub->win,
		cub->mini_carte.mlx, 0, HEIGHT / 5 * 4);
}


/*dessiner la mini-carte
verifier que la carte ne depasse pas la taille max
centrer la minimap sur le personnage*/
// void	ft_mini_map(t_cub *cub)
// {
// 	int	i;
// 	int	j;

// 	/*player position*/
// 	cub->pos_x;
// 	cub->pos_y;

// 	/*first row*/
// 	i = cub->pos_y - (cub->map_height / 2);
// 	while (i < cub->pos_y + (cub->map_height / 2))
// 	{
// 		/*first column*/
// 		j = cub->pos_x - (cub->map_width / 2);
// 		while (cub->map[i][j])
// 		{
// 			if (cub->map[i][j] == '1')
// 				big_pixel(cub, i * ZOOM_INIT, MARGIN + j * ZOOM_INIT, RED);
// 			else if (cub->map[i][j] == '0')
// 				big_pixel(cub, i * ZOOM_INIT, MARGIN + j * ZOOM_INIT, WHITE);
// 			if (cub->pos_x == j && cub->pos_y == i)
// 				player_pixel(cub, i * ZOOM_INIT, MARGIN + j * ZOOM_INIT, BLUE);
// 			j++;
// 		}
// 		i++;
// 	}
// 	//rayon
// 	//on centre
// 	j = MARGIN + cub->pos_x * ZOOM_INIT + (ZOOM_INIT / 2);
// 	i = cub->pos_y * ZOOM_INIT + (ZOOM_INIT / 2);
// 	//on trace le rayon
// 	ft_segment(cub, j, i, j + (int)(cub->dir_x * ZOOM_INIT * 1.2),
// 		i + (int)(cub->dir_y * ZOOM_INIT * 1.2));
// 	mlx_put_image_to_window(cub->mlx, cub->win,
// 		cub->mini_carte.mlx, 0, HEIGHT / 5 * 4);
// }