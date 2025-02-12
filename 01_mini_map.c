/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_mini_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:01:19 by kimnguye          #+#    #+#             */
/*   Updated: 2025/02/12 12:21:03 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

/*convert one pixel into a big pixel
return 0 if a pixel is out of the image*/
int	big_pixel(t_cub *cub, int i, int j, int color)
{
	int	x;
	int	y;

	x = j;
	while (x < j + BIG_PIXEL)
	{
		y = i - 1;
		while (++y < i + BIG_PIXEL)
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

/* draw the player_big_pixel (floor + player)
return 0 if the player pixel is not on the map*/
int	player_pixel(t_cub *cub, int i, int j, int color)
{
	int	x;
	int	y;
	int	trans;

	big_pixel(cub, i, j, WHITE);
	//on centre + on decale
	trans = (BIG_PIXEL / 2) - (PLAYER_SIZ / 2);
	j += trans; 
	i += trans;
	x = j;
	while (x < j + PLAYER_SIZ)
	{
		y = i - 1;
		while (++y < i + PLAYER_SIZ)
			if (isin_img(x, y, MAP_WIDTH, MAP_HEIGHT))		
				pixel_to_img(&cub->mini_carte, x, y, color);
			else
				return (0);
		x++;
	}
	return (1);
}

/*dessiner la mini-carte
verifier que la carte ne depasse pas la taille max*/
void	ft_mini_map(t_cub *cub)
{
	int	i;
	int	j;
	int	ctr;
	
	ctr = 0;
	i = 0;
	while (i < cub->map_height)
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (cub->map[i][j] == '1')
				big_pixel(cub, i * BIG_PIXEL, MARGIN + j * BIG_PIXEL, RED);
			else if (cub->map[i][j] == '0')
				big_pixel(cub, i * BIG_PIXEL, MARGIN + j * BIG_PIXEL, WHITE);
			if (cub->pos_x == j && cub->pos_y == i)
			{
				if (!player_pixel(cub, i * BIG_PIXEL, MARGIN + j * BIG_PIXEL, BLUE))
				{	
					//refaire la map en centrant sur le player;
					ft_printf("le player nest pas visible sur la map\n");
				}
				else
					ft_printf("le player est visible sur la map\n");
			}
			j++;
		}
		i++;
	}
	
	//ft_printf("%i %i");
	
	//rayon
	//on centre
	j = MARGIN + cub->pos_x * BIG_PIXEL + (BIG_PIXEL / 2);
	i = cub->pos_y * BIG_PIXEL + (BIG_PIXEL / 2);
	//on trace le rayon
	ft_segment(cub, j, i, j + (int)(cub->dir_x * BIG_PIXEL * 1.2),
		i + (int)(cub->dir_y * BIG_PIXEL * 1.2));
	mlx_put_image_to_window(cub->mlx, cub->win,
		cub->mini_carte.mlx, 0, HEIGHT / 5 * 4);
}


/*dessiner la mini-carte
verifier que la carte ne depasse pas la taille max
centrer la minimap sur le personnage*/
void	ft_center_map(t_cub *cub)
{
	int	i;
	int	j;

	/*player position
	cub->pos_x;
	cub->pos_y;*/

	/*first row*/
	i = cub->pos_y - (cub->map_height / 2);
	while (i < cub->pos_y + (cub->map_height / 2))
	{
		/*first column*/
		j = cub->pos_x - (cub->map_width / 2);
		while (cub->map[i][j])
		{
			if (cub->map[i][j] == '1')
				big_pixel(cub, i * BIG_PIXEL, MARGIN + j * BIG_PIXEL, RED);
			else if (cub->map[i][j] == '0')
				big_pixel(cub, i * BIG_PIXEL, MARGIN + j * BIG_PIXEL, WHITE);
			if (cub->pos_x == j && cub->pos_y == i)
				player_pixel(cub, i * BIG_PIXEL, MARGIN + j * BIG_PIXEL, BLUE);
			j++;
		}
		i++;
	}
	//rayon
	//on centre
	j = MARGIN + cub->pos_x * BIG_PIXEL + (BIG_PIXEL / 2);
	i = cub->pos_y * BIG_PIXEL + (BIG_PIXEL / 2);
	//on trace le rayon
	ft_segment(cub, j, i, j + (int)(cub->dir_x * BIG_PIXEL * 1.2),
		i + (int)(cub->dir_y * BIG_PIXEL * 1.2));
	mlx_put_image_to_window(cub->mlx, cub->win,
		cub->mini_carte.mlx, 0, HEIGHT / 5 * 4);
}