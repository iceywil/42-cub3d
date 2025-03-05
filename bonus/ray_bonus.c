/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:30:33 by a                 #+#    #+#             */
/*   Updated: 2025/03/05 11:54:21 by kimnguye         ###   ########.fr       */
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
	return (false);
}

/*update ray_x and ray_y until it hits a wall*/
void	calc_side(t_cub *cub, double start_x, int x)
{
	cub->ray_x = cub->player.x + PLAYER_SIZ / 2;
	cub->ray_y = cub->player.y + PLAYER_SIZ / 2;
	while (1)
	{
		if (x % (WIDTH / 10) == 0)
			put_pixel(&cub->mini_map, cub->ray_x - cub->player.x0,
				cub->ray_y - cub->player.y0, RED);
		cub->ray_x += cos(start_x);
		if (touch(cub, cub->ray_x, cub->ray_y))
		{
			cub->side = 1;
			break ;
		}
		cub->ray_y += sin(start_x);
		if (touch(cub, cub->ray_x, cub->ray_y))
		{
			cub->side = 0;
			break ;
		}
	}
}

/*E ou W: side 1; N ou S: side 0;*/
void	wall_texture(t_cub *cub, double start_x, int x)
{
	if (cub->map[(int)cub->ray_y / BLOCK][(int)cub->ray_x / BLOCK] == 'D')
		cub->wall_texture = &cub->door;
	else if (cub->side == 1)
	{
		if (cos(start_x) >= 0)
			cub->wall_texture = &cub->texture_e;
		else
			cub->wall_texture = &cub->texture_w;
	}
	else
	{
		if (sin(start_x) >= 0)
			cub->wall_texture = &cub->texture_s;
		else
			cub->wall_texture = &cub->texture_n;
	}
}

/*calculate the position X hit by the ray on the texture*/
int	tex_x(t_cub *cub, t_img *texture)
{
	double	wall_x;

	if (cub->side == 0)
		wall_x = cub->ray_x / BLOCK;
	else
		wall_x = cub->ray_y / BLOCK;
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

	height = (WALL_SIZ / fixed_dist(cub->player, cub->ray_x, cub->ray_y))
		* (WIDTH / 2);
	start_y = (HEIGHT - height) / 2;
	end = start_y + height;
	step = texture->height / height;
	tex_y = 0;
	while (start_y < end)
	{
		put_pixel(&cub->img, x, start_y,
			get_pixel(texture, tex_x(cub, texture), tex_y));
		tex_y += step;
		start_y++;
	}
}
