/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:30:33 by a                 #+#    #+#             */
/*   Updated: 2025/02/18 15:56:52 by kimnguye         ###   ########.fr       */
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

void	raycasting(t_cub *cub, float ray_x, float ray_y, int i)
{
	float	dist;
	float	height;
	int		start_y;
	int		end;

	dist = fixed_dist(cub->player, ray_x, ray_y);
	height = (BLOCK / dist) * (WIDTH / 2);
	start_y = (HEIGHT - height) / 2;
	end = start_y + height;
	while (start_y < end)
	{
		put_pixel(&cub->img, i, start_y, BLUE);
		start_y++;
	}
	/* 	while(start_y < end)
		{
			texture_on_img(cub, texture)
		} */
}
/*E ou W: side 1; N ou S: side 0;*/
void	draw_line(t_cub *cub, float start_x, int i)
{
	float	ray_x;
	float	ray_y;
	int		side;

	side = 0;
	ray_x = cub->player.x + PLAYER_SIZ / 2;
	ray_y = cub->player.y + PLAYER_SIZ / 2;
	while (1)
	{
		if (i % (WIDTH / 10) == 0)
			put_pixel(&cub->mini_map, ray_x - cub->player.x0, ray_y - cub->player.y0, RED);
		ray_x += cos(start_x);
		if (touch(cub, ray_x, ray_y))
		{
			// printf("YES %f\n", ray_x /*/ BLOCK*/);
			// printf("YES %f\n", cos(start_x));
			side = 1;
			break ;
		}
		ray_y += sin(start_x);
		side = 0;
		if (touch(cub, ray_x, ray_y))
		{
			// printf("NO %f\n", ray_y /*/ BLOCK*/);
			// printf("NO %f\n", sin(start_x));
			side = 0;
			break ;
		}
	}
	raycasting(cub, ray_x, ray_y, i);
}

// Reussir a remplacer le put_pixel ^ par le texture on img

/* void	texture_on_img(t_cub *cub, t_img *texture)
{
	t_player	*player;
	int			scale;
	float		ray_x;
	float		ray_y;
	float		cos_angle;new_y
	float		sin_angle;


	player = &cub->player;
	scale = line->y * texture->size_line - (HEIGHT
			* root->game->player->cam_height) * texture->line_length / 2
		+ ray->line_height * texture->line_length / 2;
	line->tex_y = ((scale * texture->height) / ray->line_height)
		/ texture->line_length;
	cub->img.data[line->y * root->mlx_img->line_length + line->x
		* root->mlx_img->bits_per_pixel / 8] = texture.data[line->tex_y
		* texture->line_length + line->tex_x * (texture->bits_per_pixel / 8)];
	cub->img.data[line->y * root->mlx_img->line_length + line->x
		* (root->mlx_img->bits_per_pixel / 8) + 1] = texture.data[line->tex_y
		* texture->line_length + line->tex_x * (texture->bits_per_pixel / 8)
		+ 1];
	root->img.data[line->y * root->mlx_img->line_length + line->x
		* (root->mlx_img->bits_per_pixel / 8) + 2] = texture.data[line->tex_y
		* texture->line_length + line->tex_x * (texture->bits_per_pixel / 8)
		+ 2];
} */

/*on actualise la position et direction du player
on clear les images
on raycaste, et on draw le player et la map*/
int	draw_loop(t_cub *cub)
{
	float		fraction;
	float		start_x;
	int			i;
	float		fov;
	
	move_player(&cub->player, cub);
	clear_image(&cub->mini_map, MAP_HEIGHT, MAP_WIDTH);
	clear_image(&cub->img, HEIGHT, WIDTH);
	background(cub);
	fov = M_PI / 3;
	fraction = fov / WIDTH;
	start_x = cub->player.angle - fov / 2;
	i = 0;
	while (i < WIDTH)
	{
		draw_line(cub, start_x, i);
		start_x += fraction;
		i++;
	}
	draw_map(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.data, 0, 0);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->mini_map.data, 0, HEIGHT
		- MAP_HEIGHT);
	return (0);
}
