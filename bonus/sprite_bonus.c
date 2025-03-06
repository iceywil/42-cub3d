/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:57:53 by kimnguye          #+#    #+#             */
/*   Updated: 2025/03/06 01:10:26 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	sprite_action(char **map, t_player player)
{
	float	x;
	float	y;
	int		i;

	i = 0;
	while (i < MARGIN_DOOR * 2)
	{
		x = player.x + cos(player.angle) * SPEED * i;
		y = player.y + sin(player.angle) * SPEED * i;
		if (map[(int)y / BLOCK][(int)x / BLOCK] == 'S')
		{
			map[(int)y / BLOCK][(int)x / BLOCK] = 'O';
			return ;
		}
		i++;
	}
}

int	is_sprite_forward(char **map, t_player player)
{
	float	x;
	float	y;
	int		i;

	i = 0;
	while (i < MARGIN_DOOR * 2)
	{
		x = player.x + cos(player.angle) * SPEED * i;
		y = player.y + sin(player.angle) * SPEED * i;
		if (map[(int)y / BLOCK][(int)x / BLOCK] == 'S')
			return (1);
		i++;
	}
	return (0);
}

void	init_sprite(t_cub *cub)
{
	t_img	*img;

	img = &cub->sprite;
	img->data = mlx_xpm_file_to_image(cub->mlx,
			"./textures/salon.xpm", &img->width, &img->height);
	if (!img->data)
		exit_error(cub, "Failed XPM to image");
	img->addr = mlx_get_data_addr(img->data, &img->bpp, &img->size_line,
			&img->endian);
	if (!img->addr)
		exit_error(cub, "Failed get address from texture img");
	mlx_put_image_to_window(cub->mlx, cub->win,
		cub->sprite.data, 0, 0);
}
