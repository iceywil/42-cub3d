/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:30:33 by a                 #+#    #+#             */
/*   Updated: 2025/02/18 19:04:45 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*E ou W: side 1; N ou S: side 0;*/
void	draw_line(t_cub *cub, float start_x, int x)
{
}

void	raycasting(t_cub *cub, float ray_x, float ray_y, int x)
{
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
	double	planeX;
	double	planeY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	int		color;
	double	rayDirX;
	double	rayDirY;
	int		mapX;
	int		mapY;
	double	perpWallDist;
	int		stepX;
	int		stepY;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	int		texX;
	int		texNum;
	double	step;
	double	texPos;
	int		texY;
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	cameraX;

	posX = 22.0;
	posY = 11.5; // x and y start position
	dirX = -1.0;
	dirY = 0.0; // initial direction vector
	planeX = 0.0;
	planeY = 0.66;
	// the 2d raycaster version of camera plane
	// the 2d raycaster version of camera plane
	move_player(&cub->player, cub);
	clear_image(&cub->mini_map, MAP_HEIGHT, MAP_WIDTH);
	clear_image(&cub->img, HEIGHT, WIDTH);
	background(cub);
	x = 0;
	while (x < WIDTH)
	{
		// calculate ray position and direction
		cameraX = 2 * x / (double)WIDTH - 1;
		// x-coordinate in camera space
		rayDirX = dirX + planeX * cameraX;
		rayDirY = dirY + planeY * cameraX;
		// which box of the map we're in
		mapX = (int)posX;
		mapY = (int)posY;
		// length of ray from current position to next x or y-side
		// length of ray from one x or y-side to next x or y-side
		deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
		deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
		// what direction to step in x or y-direction (either +1 or -1)
		int hit = 0; // was there a wall hit?
		int side;    // was a NS or a EW wall hit?
		// calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}
		// perform DDA
		while (hit == 0)
		{
			// jump to next map square, either in x-direction, or in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			// Check if ray has hit a wall
			if (cub->map && cub->map[mapX] && cub->map[mapX][mapY] > 0)
				hit = 1;
		}
		// Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect!)
		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);
		// Calculate height of line to draw on screen
		lineHeight = (int)(HEIGHT / perpWallDist);
		// calculate lowest and highest pixel to fill in current stripe
		drawStart = -lineHeight / 2 + HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + HEIGHT / 2;
		if (drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;
		// texturing calculations
		if (cub->map && cub->map[mapX] && cub->map[mapX][mapY])
			texNum = cub->map[mapX][mapY] - 1;
		// 1 subtracted from it so that texture 0 can be used!
		// calculate value of wallX
		double wallX; // where exactly the wall was hit
		if (side == 0)
			wallX = posY + perpWallDist * rayDirY;
		else
			wallX = posX + perpWallDist * rayDirX;
		wallX -= floor((wallX));
		// x coordinate on the texture
		texX = (int)(wallX * (double)cub->wall_texture->width);
		if (side == 0 && rayDirX > 0)
			texX = cub->wall_texture->width - texX - 1;
		if (side == 1 && rayDirY < 0)
			texX = cub->wall_texture->width - texX - 1;
		// How much to increase the texture coordinate per screen pixel
		step = 1.0 * cub->wall_texture->height / lineHeight;
		// Starting texture coordinate
		texPos = (drawStart - HEIGHT / 2 + lineHeight / 2) * step;
		while (drawStart < drawEnd)
		{
			// Cast the texture coordinate to integer
			// and mask with (texHeight - 1) in case of overflow
			texY = (int)texPos & (cub->wall_texture->height - 1);
			texPos += step;
			color = cub->wall_texture->addr[cub->wall_texture->height * texY
				+ texX];
			// make color darker for y-sides: R,
			// G and B byte each divided through two with a "shift" and an "and"
			if (side == 1)
				color = (color >> 1) & 8355711;
			put_pixel(&cub->img, x, drawStart, color);
			drawStart++;
		}
		x++;
	}
	draw_map(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.data, 0, 0);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->mini_map.data, 0, HEIGHT
		- MAP_HEIGHT);
	return (0);
}
