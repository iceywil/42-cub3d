/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:01:19 by kimnguye          #+#    #+#             */
/*   Updated: 2025/02/10 21:02:08 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
Pouvoir faire bouger mon personnage avec les flèches dans la minimap (voir les keys à l'étape 4)
Checker si le case sur laquelle je vais me déplacer est un mur ou pas (si == ‘0’) : si oui je peux me déplacer dessus,
	sinon non
*/
void	big_pixel(t_cub *cub, int i, int j, int color)
{
	int	x;
	int	y;

	x = j;
	while (x < j + ZOOM_INIT)
	{
		y = i - 1;
		while (++y < i + ZOOM_INIT)
			if (x < MAP_WIDTH && y < MAP_HEIGHT && x >= 0 && y >= 0)
				pixel_on_img(cub->mini_map, color, x, y);
		x++;
	}
}

/*dessiner la mini-carte
verifier que la carte ne depasse pas la taille max*/
void	draw_map(t_cub *cub)
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
			if (cub->map[i][j] == '0')
				big_pixel(cub, i * ZOOM_INIT, MARGIN + j * ZOOM_INIT, WHITE);
			if (is_in(cub->map[i][j], "NSEW"))
				big_pixel(cub, i * ZOOM_INIT, MARGIN + j * ZOOM_INIT, BLUE);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->mini_map->data, 0, HEIGHT
		/ 5 * 4);
}
