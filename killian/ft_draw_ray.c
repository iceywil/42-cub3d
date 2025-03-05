/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_ray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:47:57 by kduroux           #+#    #+#             */
/*   Updated: 2025/03/05 10:29:27 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../cub3d.h"

void	ft_draw_ray(t_game *game, float start_x, int i);
void	ft_set_dir(t_game *game, t_ray *ray);
void	ft_raycast(t_game *game, t_ray *ray, int i);

void	ft_raycast(t_game *game, t_ray *ray, int i)
{
	float	dist;
	float	height;
	int		start_y;
	int		end;
	float	step;
	float	tex_y;
	int		color;
	int		tex_x_coord;

	dist = fixed_dist(ray->ray_x, ray->ray_y, game);
	height = ( BLOCK / dist) * ((float)WINDOWS_WIDTH / 2);
	start_y = (WINDOWS_HEIGHT - height) / 2;
	step = (float)TEXH / height;
	end = start_y + height;
	tex_y = 0;
	while(start_y < end)
	{
		tex_x_coord = tex_x(ray->ray_x, ray->ray_y, game->side);
		color = ft_get_texture(tex_x_coord, (int)tex_y, &game->img_tab[game->dir]);
		ft_put_pixel_on_img(&game->img_tab[0], i, start_y, color);
		tex_y += step;
		start_y++;
	}
}

void	ft_set_dir(t_game *game, t_ray *ray)
{
	if (game->side == 0)
	{
		if (ray->ray_dir_x > 0)
			game->dir = EA;
		else
			game->dir = WE;
	}
	else
	{
		if (ray->ray_dir_y > 0)
			game->dir = SO;
		else
			game->dir = NO;
	}
}

void	ft_draw_ray(t_game *game, float start_x, int i)
{
	t_ray	*ray;

	ray = &game->ray;
	ft_init_ray(ray, game, start_x);
	while (42)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->ray_x += ray->step_x;
			game->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->ray_y += ray->step_y;
			game->side = 1;
		}
		if (ft_touch(ray->ray_x, ray->ray_y, game) == 1)
			break;
	}
	ft_set_dir(game, ray);
	ft_raycast(game, ray, i);
}
