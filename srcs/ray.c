/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:30:33 by a                 #+#    #+#             */
/*   Updated: 2025/02/20 15:49:20 by kimnguye         ###   ########.fr       */
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
		if (x % (WIDTH / 10) == 0)
			put_pixel(&cub->mini_map, cub->ray_x - cub->player.x0, cub->ray_y - cub->player.y0, RED);
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
		if (start_x >= -PI / 2 && start_x < PI / 2)
			cub->wall_texture = &cub->texture_e;
		else
			cub->wall_texture = &cub->texture_w;
	}
	else
	{
		if (start_x >= 0 && start_x < PI)
			cub->wall_texture = &cub->texture_s;
		else
			cub->wall_texture = &cub->texture_n;
	}
	raycasting(cub, cub->wall_texture, x);
}

/*il nous faut la position (dans la map) du mur qui a ete touche : cub->ray_x / BLOCK et cub->ray_y / BLOCK*/
void	raycasting(t_cub *cub, t_img *texture, int x)
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
	double	fin_du_mur_touche;

	dist = fixed_dist(cub->player, cub->ray_x, cub->ray_y);
	height = (WALL_SIZ / dist) * (WIDTH / 2);
	start_y = (HEIGHT - height) / 2;
	end = start_y + height;
	/* find the X coordinate*/
	double wallX; // where exactly the wall was hit
	if (cub->side == 0) /*nord ou sud*/
		wallX = (cub->ray_y) / BLOCK;
		else /*east ou west*/
		wallX = (cub->ray_x) / BLOCK;
	/*on fait en sort que wall X soit entre 0 et 1 exclu*/
	wallX -= floor((wallX));
	// x coordinate on the texture
	texX = (int)(wallX * (double)(texture->width));
	// How much to increase the texture coordinate per screen pixel
	step = texture->height / height;
	// Starting texture coordinate
	while (start_y < end)
	{
		//on fait correpondre au pixel de la texture en Y (en retirant start_y0) puis en X (en multipliant par step)
		texPos = (start_y - (HEIGHT - height) / 2) * step;
		texY = texPos; //position dans limage
		color = get_pixel(texture, texX, texY);
		put_pixel(&cub->img, x, start_y, color);
		texPos += step;
		start_y++;
	}
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
	clear_image(&cub->img, HEIGHT, WIDTH);
	clear_image(&cub->mini_map, MAP_HEIGHT, MAP_WIDTH);
	background(cub);
	draw_map(cub);
	fov = M_PI / 3;
	fraction = fov / WIDTH;
	start_x = cub->player.angle - fov / 2;
	x = 0;
	while (x < WIDTH)
	{
		draw_line(cub, start_x, x);
		start_x += fraction;
		x++;
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.data, 0, 0);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->mini_map.data, 0, HEIGHT
		- MAP_HEIGHT);
	get_texture(cub);
	return (0);
}
