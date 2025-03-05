/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:45:23 by kduroux           #+#    #+#             */
/*   Updated: 2025/03/05 10:29:24 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_init_ray(t_ray *ray, t_game *game, float angle);
void	ft_init_ray_null(t_ray *ray);
void	ft_init_ray_utils(t_ray *ray, t_player *player);

void	ft_init_ray_null(t_ray *ray)
{
	ray->ray_x = 0;
	ray->ray_y = 0;
	ray->ray_dir_x = 0;
	ray->ray_dir_y = 0;
	ray->delta_dist_x = 0;
	ray->delta_dist_y = 0;
	ray->step_x = 0;
	ray->step_y = 0;
}

void	ft_init_ray(t_ray *ray, t_game *game, float angle)
{
	t_player	*player;

	player = &game->player;
	ray->ray_x = player->x;
	ray->ray_y = player->y;
	ray->ray_dir_x = cos(angle);
	ray->ray_dir_y = sin(angle);
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ft_init_ray_utils(ray, &game->player);
}

void	ft_init_ray_utils(t_ray *ray, t_player *player)
{
	if (ray->ray_dir_x < 0)
		ray->step_x = -1;
	else
		ray->step_x = 1;
	if (ray->ray_dir_y < 0)
		ray->step_y = -1;
	else
		ray->step_y = 1;
	if (ray->ray_dir_x < 0)
		ray->side_dist_x = (player->x - floor(player->x))
			* ray->delta_dist_x;
	else
		ray->side_dist_x = (ceil(player->x) - player->x)
			* ray->delta_dist_x;
	if (ray->ray_dir_y < 0)
		ray->side_dist_y = (player->y - floor(player->y))
			* ray->delta_dist_y;
	else
		ray->side_dist_y = (ceil(player->y) - player->y)
			* ray->delta_dist_y;
}
