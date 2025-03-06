/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:57:53 by kimnguye          #+#    #+#             */
/*   Updated: 2025/03/06 12:24:00 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*update ray.x and ray.y until it hits a wall
new method: with step 1*/
void	calc_short_dist(t_cub *cub, t_ray *ray)
{
	while (1)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->deltadist_x;
			ray->x += ray->step_x;
		}
		else
		{
			ray->sidedist_y += ray->deltadist_y;
			ray->y += ray->step_y;
		}
		if (touch(cub, ray->x, ray->y))
			break;
	}
}

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
		if (map[(int)y / BLOCK][(int)x / BLOCK] == 'P')
		{
			map[(int)y / BLOCK][(int)x / BLOCK] = 'O';
			return ;
		}
		i++;
	}
}

int	is_sprite_forward(char **map, double x, double y)
{
	int		i;

	i = 0;
	while (i < MARGIN_DOOR * 2)
	{
		//x = player.x + cos(player.angle) * SPEED * i;
		//y = player.y + sin(player.angle) * SPEED * i;
		if (map[(int)y / BLOCK][(int)x / BLOCK] == 'P')
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
			"./textures/sprite.xpm", &img->width, &img->height);
	if (!img->data)
		exit_error(cub, "Failed XPM to image");
	img->addr = mlx_get_data_addr(img->data, &img->bpp, &img->size_line,
			&img->endian);
	if (!img->addr)
		exit_error(cub, "Failed get address from texture img");
}
