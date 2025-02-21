/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 23:30:41 by a                 #+#    #+#             */
/*   Updated: 2025/02/21 23:35:42 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ray_loop(t_cub *cub)
{
	double	cameraX;
	double	ray_dir_x;
	double	ray_dir_y;
	int		mapX;
	int		mapY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;
	int		stepX;
	int		stepY;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	int		color;
	double	frameTime;
	double	time;
	int		texNum;
	int		tex_x;
	double	step;
	double	tex_pos;
	int		tex_y;
	int		tex_index;

	move_player(cub);
	clear_image(&cub->img);
	for (int x = 0; x < WIDTH; x++)
	{
		// calculate ray position and direction
		cameraX = 2 * x / (double)WIDTH - 1;
		// x-coordinate in camera space
		cub->ray_dir_x = cub->dir_x + cub->plane_x * cameraX;
		cub->ray_dir_y = cub->dir_y + cub->plane_y * cameraX;
		// which box of the map we're in
		mapX = (int)cub->pos_x;
		mapY = (int)cub->pos_y;
		// length of ray from current position to next x or y-side
		// length of ray from one x or y-side to next x or y-side
		deltaDistX = (cub->ray_dir_x == 0) ? 1e30 : fabs(1 / cub->ray_dir_x);
		deltaDistY = (cub->ray_dir_y == 0) ? 1e30 : fabs(1 / cub->ray_dir_y);
		// what direction to step in x or y-direction (either +1 or -1)
		int hit = 0; // was there a wall hit?
		int side;    // was a NS or a EW wall hit?
					// calculate step and initial sideDist
		if (cub->ray_dir_x < 0)
		{
			stepX = -1;
			sideDistX = (cub->pos_x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - cub->pos_x) * deltaDistX;
		}
		if (cub->ray_dir_y < 0)
		{
			stepY = -1;
			sideDistY = (cub->pos_y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - cub->pos_y) * deltaDistY;
		}
		// perform DDA
		while (hit == 0)
		{
			// jump to next map square, either in x-direction,
			// or in y - direction
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
			if (cub->map[mapX][mapY] == '1')
				hit = 1;
			// exit(1);
		}
		// Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
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
		// texNum = cub->map[mapX][mapY] - 1;
			// This line is not needed if using a single texture
		// calculate value of wallX
		double wallX; // where exactly the wall was hit
		if (side == 0)
			wallX = cub->pos_y + perpWallDist * cub->ray_dir_y;
		else
			wallX = cub->pos_x + perpWallDist * cub->ray_dir_x;
		wallX -= floor((wallX));
		// x coordinate on the texture
		tex_x = (int)(wallX * (double)cub->texture_n.width);
		if (side == 0 && cub->ray_dir_x > 0)
			tex_x = cub->texture_n.width - tex_x - 1;
		if (side == 1 && cub->ray_dir_y < 0)
			tex_x = cub->texture_n.width - tex_x - 1;
		// How much to increase the texture coordinate per screen pixel
		step = 1.0 * cub->texture_n.height / lineHeight;
		// Starting texture coordinate
		tex_pos = (drawStart - HEIGHT / 2 + lineHeight / 2) * step;
		for (int y = drawStart; y < drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with
			// (texHeight - 1) in case of overflow
			tex_y = (int)tex_pos & (cub->texture_n.height - 1);
			tex_pos += step;
			// Fetch the color from the texture
			tex_index = tex_y * cub->texture_n.size_line + tex_x
				* (cub->texture_n.bpp / 8);
			color = *(int *)(cub->texture_n.addr + tex_index);
			// make color darker for y-sides:
			if (side == 1)
				color = (color >> 1) & 8355711;
			put_pixel(&cub->img, x, y, color);
		}
	}
	// timing for input and FPS counter
	time = get_time();
	frameTime = (time - cub->oldTime) / 1000.0;
	cub->oldTime = time;
	// frameTime is the time this frame has taken, in seconds
	// print(1.0 / frameTime); // FPS counter
	// redraw();
	// cls();
	// speed modifiers
	cub->move_speed = frameTime * 5.0;
	// the constant value is in squares/second
	cub->rot_speed = frameTime * 3.0;
	// the constant value is in radians/second
	// readKeys();
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.data, 0, 0);
	return (0);
}
