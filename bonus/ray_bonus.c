/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:30:33 by a                 #+#    #+#             */
/*   Updated: 2025/03/06 12:24:52 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*return true if wall*/
bool	touch(t_cub *cub, float px, float py)
{
	int	x;
	int	y;

	x = px / BLOCK;
	y = py / BLOCK;
	if (cub->map[y] && cub->map[y][x] && cub->map[y][x] == '1')
		return (true);
	if (cub->map[y] && cub->map[y][x] && cub->map[y][x] == 'D')
		return (true);
	if (cub->map[y] && cub->map[y][x] && cub->map[y][x] == 'P')
		return (true);
	return (false);
}

/*update ray.x and ray.y until it hits a wall
new method: with step 1*/
void	calc_side(t_cub *cub, double angle, int x)
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
		if (touch(cub, cub->ray.x, cub->ray.y))
			break;
	}
}

/*E ou W: side 1; N ou S: side 0; BONUS: texture door*/
void	wall_texture(t_cub *cub, double ray_angle, int x)
{
	if (cub->map[(int)cub->ray.y / BLOCK][(int)cub->ray.x / BLOCK] == 'D')
		cub->wall_texture = &cub->door;
	else if (cub->map[(int)cub->ray.y / BLOCK][(int)cub->ray.x / BLOCK] == 'P')
	{
		cub->wall_texture = &cub->sprite;
		cub->side = 2;
	}
	else if (cub->side == 1)
	{
		if (cos(ray_angle) >= 0)
			cub->wall_texture = &cub->texture_e;
		else
			cub->wall_texture = &cub->texture_w;
	}
	else
	{
		if (sin(ray_angle) >= 0)
			cub->wall_texture = &cub->texture_s;
		else
			cub->wall_texture = &cub->texture_n;
	}
}

/*calculate the position X hit by the ray on the texture*/
int	tex_x(t_cub *cub, t_img *texture)
{
	double	wall_x;

	if (cub->side == 2)
		wall_x = cub->player.ray.x / BLOCK;
	else if (cub->side == 0)
		wall_x = cub->ray.x / BLOCK;
	else
		wall_x = cub->ray.y / BLOCK;
	wall_x -= floor((wall_x));
	return ((int)(wall_x * (double)(texture->width)));
}

void	draw_wall(t_cub *cub, t_img *texture, int x)
{
	int		start_y;
	int		end;
	double	step;
	double	tex_y;
	float	height;

	height = (WALL_SIZ / fixed_dist(cub->player, cub->ray.x, cub->ray.y))
		* (WIDTH / 2);
	start_y = (HEIGHT - height) / 2;
	end = start_y + height;
	step = texture->height / height;
	tex_y = 0;
	while (start_y < end)
	{
		put_pixel(&cub->img, x, start_y,
			get_pixel(texture, tex_x(cub, texture), (int)tex_y));
		tex_y += step;
		start_y++;
	}
}
