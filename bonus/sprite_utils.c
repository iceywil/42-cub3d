/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:57:53 by kimnguye          #+#    #+#             */
/*   Updated: 2025/03/06 16:12:59 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


void	init_ray_player(t_cub *cub, t_ray *ray, t_player *player)
{
	ray->x = player->x + PLAYER_SIZ / 2;
	ray->y = player->y + PLAYER_SIZ / 2;
	ray->dir_x = cos(player->angle);
	ray->dir_y = sin(player->angle);
	ray->deltadist_x = fabs(BLOCK / ray->dir_x);
	ray->deltadist_y = fabs(BLOCK / ray->dir_y);
	calc_ray(ray, player);
	calc_short_dist(cub, ray);
}


int	is_sprite_forward(char **map, double x, double y)
{
	int		i;

	i = 0;
	while (i < MARGIN_DOOR)
	{
		if (map[(int)y / BLOCK][(int)x / BLOCK] == 'P')
			return (1);
		i++;
	}
	return (0);
}

void	init_sprite(t_cub *cub)
{
	t_img	*img;

	img = &cub->texture_sprite;
	img->data = mlx_xpm_file_to_image(cub->mlx,
			"./textures/sprites-cat-running.xpm", &img->width, &img->height);
	if (!img->data)
		exit_error(cub, "Failed XPM to image");
	img->addr = mlx_get_data_addr(img->data, &img->bpp, &img->size_line,
			&img->endian);
	if (!img->addr)
		exit_error(cub, "Failed get address from texture img");
	cub->sprite.height = 256;
	cub->sprite.width = 512;
	cub->sprite.num_frames = 8;
}

