/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:30:33 by a                 #+#    #+#             */
/*   Updated: 2025/02/11 19:26:30 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	test_ray(t_cub *cub)
{
	cub->ray_y_start = 0;
	cub->ray_y_end = 100;
	paint_line(cub, 0xFF0000);
	//mlx_put_image_to_window(cub->mlx, cub->win, cub->img->data, 0, 0);
}

void	paint_line(t_cub *cub, int rgb)
{
	int	y;
	int	y_max;

	if (cub->ray_y_start < cub->ray_y_end)
	{
		y = cub->ray_y_start;
		y_max = cub->ray_y_end;
	}
	else
	{
		y = cub->ray_y_end;
		y_max = cub->ray_y_start;
	}
	if (y >= 0)
	{
		while (y < y_max)
		{
			pixel_on_img(cub->img, rgb, cub->ray_x, y);
			y++;
		}
	}
}

void	pixel_on_img(t_img *img, int rgb, int x, int y)
{
	int	pixel;

	pixel = (y * img->size_line) + (x * (img->bpp / 8));
	img->addr[pixel] = rgb & 0xFF;
	img->addr[pixel + 1] = (rgb >> 8) & 0xFF;
	img->addr[pixel + 2] = (rgb >> 16) & 0xFF;
}

/* static void	texture_on_img(t_cub *cub, t_cub *ray, t_line *line,
		t_img *texture)
{
	int	scale;

	scale = line->y * texture->line_length - (WIN_HEIGHT
			* root->game->player->cam_height) * texture->line_length / 2
		+ ray->line_height * texture->line_length / 2;
	line->tex_y = ((scale * texture->height) / ray->line_height)
		/ texture->line_length;
	cub->img->data[line->y * root->mlx_img->line_length + line->x
		* root->mlx_img->bits_per_pixel / 8] = texture->data[line->tex_y
		* texture->line_length + line->tex_x * (texture->bits_per_pixel / 8)];
	cub->img->data[line->y * root->mlx_img->line_length + line->x
		* (root->mlx_img->bits_per_pixel / 8) + 1] = texture->data[line->tex_y
		* texture->line_length + line->tex_x * (texture->bits_per_pixel / 8)
		+ 1];
	root->img->data[line->y * root->mlx_img->line_length + line->x
		* (root->mlx_img->bits_per_pixel / 8) + 2] = texture->data[line->tex_y
		* texture->line_length + line->tex_x * (texture->bits_per_pixel / 8)
		+ 2];
} */
