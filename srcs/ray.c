/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:30:33 by a                 #+#    #+#             */
/*   Updated: 2025/02/24 14:59:17 by kimnguye         ###   ########.fr       */
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

/*on avance le rayon jusqua ce que le rayon touche un mur*/
void	calc_side(t_cub *cub, float start_x, int x)
{
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
}

/*E ou W: side 1; N ou S: side 0;*/
void	hit_texture(t_cub *cub, float start_x, int x)
{
	if (cub->side == 1)
	{
		if (cos(start_x) >= 0)
			cub->wall_texture = &cub->texture_e;
		else
			cub->wall_texture = &cub->texture_w;
	}
	else //side == 0 (N ou S)
	{
		if (sin(start_x) >= 0)
			cub->wall_texture = &cub->texture_s;
		else
			cub->wall_texture = &cub->texture_n;
	}
}

/*il nous faut la position (dans la map) du mur qui a ete touche : cub->ray_x / BLOCK et cub->ray_y / BLOCK*/
void	draw_line(t_cub *cub, t_img *texture, int x)
{
	double	step;
	int		color;
	float	height;
	int		start_y;
	int		end;
	int		texX;
	double	texY;
	float	dist;
	
	dist = fixed_dist(cub->player, cub->ray_x, cub->ray_y);
	height = (WALL_SIZ / dist) * (WIDTH / 2);
	start_y = (HEIGHT - height) / 2;
	end = start_y + height;
	/* find the X coordinate*/
	double wallX; // where exactly the wall was hit
	if (cub->side == 0) /*nord ou sud*/
		wallX = cub->ray_x / BLOCK;
	else /*east ou west*/
		wallX = cub->ray_y / BLOCK;
	/*on fait en sort que wall X soit entre 0 et 1 exclu*/
	wallX -= floor((wallX));
	// x coordinate on the texture
	texX = (int)(wallX * (double)(texture->width));
	// How much to increase the texture coordinate per screen pixel
	step = texture->height / height;
	texY = 0;
	/*on dessine le mur*/
	while (start_y < end)
	{
		color = get_pixel(texture, texX, texY);
		put_pixel(&cub->img, x, start_y, color);
		texY += step;
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
	int		x;

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
		calc_side(cub, start_x, x);
		hit_texture(cub, start_x, x);
		draw_line(cub, cub->wall_texture, x);
		start_x += fraction;
		x++;
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.data, 0, 0);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->mini_map.data, 0, HEIGHT
		- MAP_HEIGHT);
	return (0);
}

	/*
	if (cub->side == 0) //horizontal : nord ou sud
		frac = (cub->ray_x - (double)cub->player.x0) / BLOCK - (int)((cub->ray_x - cub->player.x0) / BLOCK);
	else //vertical : est ou ouest
		frac = (cub->ray_y - (double)cub->player.y0) / BLOCK - (int)((cub->ray_y - cub->player.y0) / BLOCK);
	texX = (int)(frac * (double)cub->wall_texture->width);
	ft_printf("tex_x OK\n");
	*/
