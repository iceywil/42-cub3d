/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:57:53 by kimnguye          #+#    #+#             */
/*   Updated: 2025/03/06 16:12:21 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	touch_sprite(t_cub *cub, float px, float py)
{
	int	x;
	int	y;

	x = px / BLOCK;
	y = py / BLOCK;
	if (cub->map[y] && cub->map[y][x] && cub->map[y][x] == 'P')
		return (true);
	if (cub->map[y] && cub->map[y][x] && cub->map[y][x] == '1')
		return (true);
	if (cub->map[y] && cub->map[y][x] && cub->map[y][x] == 'D')
		return (true);
	return (false);
}

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
		if (touch_sprite(cub, ray->x, ray->y))
			break ;
	}
}

/*update ray.x and ray.y until it hits a wall
new method: with step 1*/
void	calc_side_sprite(t_cub *cub, double angle, int x)
{
	while (1)
	{
		if (x % (WIDTH / 10) == 0)
			put_pixel(&cub->mini_map, cub->ray.x - cub->player.x0,
				cub->ray.y - cub->player.y0, RED);
		if (cub->ray.sidedist_x < cub->ray.sidedist_y)
		{
			cub->ray.sidedist_x += cub->ray.deltadist_x;
			cub->ray.x += cub->ray.step_x;
			cub->side = 1;
		}
		else
		{
			cub->ray.sidedist_y += cub->ray.deltadist_y;
			cub->ray.y += cub->ray.step_y;
			cub->side = 0;
		}
		if (touch_sprite(cub, cub->ray.x, cub->ray.y))
			break;
	}
}

void	draw_sprite(t_cub *cub, t_img *tex_spr, int x)
{
	int		start_y;
	int		end;
	double	step;
	double	tex_y;
	float	height;
	int		color;
	
	if (cub->map[(int)cub->ray.y / BLOCK][(int)cub->ray.x / BLOCK] == 'P')
	{
		height = (SPRITE_SIZ / fixed_dist(cub->player, cub->player.ray.x, cub->player.ray.y))
			* (WIDTH/ 2);
		start_y = (HEIGHT + height) / 2;
		end = start_y + height;
		step = cub->sprite.height / height;
		tex_y = 0;
		while (start_y < end)
		{
			if (cub->sprite.num >= 4)
				tex_y = (int)tex_y % cub->sprite.height + cub->sprite.height;
			color = get_pixel(tex_spr, tex_x(cub, tex_spr) % cub->sprite.width
				+ cub->sprite.num % 4 * cub->sprite.width, tex_y);
			if (color != WHITE && color != GREY)
				put_pixel(&cub->img, x, start_y, color);
			tex_y += step;
			start_y++;
		}
	}
}

void	show_sprite(t_cub *cub)
{
	double	ray_angle;
	int		x;
	
	ray_angle = cub->player.angle - FOV / 2;
	x = 0;
	while (x < WIDTH)
	{
		init_ray(&cub->ray, cub, ray_angle);
		calc_side_sprite(cub, ray_angle, x);
		draw_sprite(cub, &cub->texture_sprite, x);
		ray_angle += cub->fraction;
		x++;
	}
}