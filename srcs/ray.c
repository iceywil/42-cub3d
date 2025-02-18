/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:30:33 by a                 #+#    #+#             */
/*   Updated: 2025/02/18 04:04:32 by a                ###   ########.fr       */
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
	return (false);
}

/*E ou W: side 1; N ou S: side 0;*/
void	draw_line(t_cub *cub, float start_x, int x)
{
	int	side;

	cub->ray_x = cub->player.x + PLAYER_SIZ / 2;
	cub->ray_y = cub->player.y + PLAYER_SIZ / 2;
	while (1)
	{
		put_pixel(&cub->mini_map, cub->ray_x, cub->ray_y, RED);
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
	if (cub->side == 1)
	{
		if (cub->player.angle >= -PI / 2 && cub->player.angle <= PI / 2)
			cub->wall_texture = &cub->texture_e;
		else
			cub->wall_texture = &cub->texture_w;
	}
	else
	{
		if (cub->player.angle >= 0 && cub->player.angle <= PI)
			cub->wall_texture = &cub->texture_n;
		else
			cub->wall_texture = &cub->texture_s;
	}
	raycasting(cub, cub->ray_x, cub->ray_y, x);
}

void	raycasting(t_cub *cub, float ray_x, float ray_y, int x)
{
	float	dist;
	float	height;
	int		start_y;
	int		end;
	int		texX;
	double	step;
	double	texPos;
	int		texY;
	int		color;

	dist = fixed_dist(cub->player, ray_x, ray_y);
	height = (BLOCK / dist) * (WIDTH / 2);
	start_y = (HEIGHT - height) / 2;
	end = start_y + height;
	// get WallX
	double wallX; // where exactly the wall was hit
	if (cub->side == 0)
		wallX = cub->player.y + dist * cub->ray_y;
	else
		wallX = cub->player.x + dist * cub->ray_x;
	wallX -= floor((wallX));
	// x coordinate on the texture
	texX = (int)(wallX * (double)(cub->wall_texture->width));
	if (cub->side == 0 && cub->ray_x > 0)
		texX = cub->wall_texture->width - texX - 1;
	if (cub->side == 1 && cub->ray_y < 0)
		texX = cub->wall_texture->width - texX - 1;
	// How much to increase the texture coordinate per screen pixel
	step = 1.0 * cub->wall_texture->height / height;
	// Starting texture coordinate
	texPos = (start_y - HEIGHT / 2 + height / 2) * step;
	while (start_y < end)
	{
		// Cast the texture coordinate to integer
		// and mask with (texHeight- 1) in case of overflow
		texY = (int)texPos & (cub->wall_texture->height - 1);
		texPos += step;
		color = cub->wall_texture->addr[cub->wall_texture->height * texY
			+ texX];
		// make color darker for y-sides: R,
		// G and B byte each divided through two with a "shift" and an "and"
		if (cub->side == 1)
			color = (color >> 1) & 8355711;
		put_pixel(&cub->img, x, start_y, color);
		start_y++;
	}
	/* 	while (start_y < end)
		{
			put_pixel(&cub->img, x, start_y, BLUE);
			start_y++;
		} */
}

/*on actualise la position et direction du player
on clear les images
on raycaste, et on draw le player et la map*/
int	draw_loop(t_cub *cub)
{
	float	fraction;
	float	start_x;
	int		i;
	float	fov;
	int x;
	move_player(&cub->player, cub);
	clear_image(&cub->mini_map, MAP_HEIGHT, MAP_WIDTH);
	clear_image(&cub->img, HEIGHT, WIDTH);
	background(cub);
	fov = PI / 3;
	fraction = fov / WIDTH;
	start_x = cub->player.angle - fov / 2;
	x = 0;
	while (x < WIDTH)
	{
		draw_line(cub, start_x, x);
		start_x += fraction;
		x++;
	}
	draw_player(&cub->mini_map, cub->player.x, cub->player.y, GREEN);
	draw_map(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.data, 0, 0);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->mini_map.data, 0, HEIGHT
		- MAP_HEIGHT);
	return (0);
}
