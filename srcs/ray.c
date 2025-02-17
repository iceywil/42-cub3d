/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:30:33 by a                 #+#    #+#             */
/*   Updated: 2025/02/17 14:18:19 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * img->size_line + x * img->bpp / 8;
	img->addr[index] = color & 0xFF;
	img->addr[index + 1] = (color >> 8) & 0xFF;
	img->addr[index + 2] = (color >> 16) & 0xFF;
}

void	clear_image(t_img *img, int height, int width)
{
	int	x;
	int	y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			put_pixel(img, x, y, 0);
			x++;
		}
		y++;
	}
}

float	new_y(t_player *player)
{
	float y;

	y = player->y;
	if (player->key_up)
		return (y + sin(player->angle) * SPEED);
	if (player->key_left)
		return (y - cos(player->angle) * SPEED);
	if (player->key_down)
		return (y - sin(player->angle) * SPEED);
	if (player->key_right)
		return (y + cos(player->angle) * SPEED);
	return (player->y);
}

float	new_x(t_player *player)
{
	float x;

	x = player->x;
	if (player->key_up)
		return (x + cos(player->angle) * SPEED);
	if (player->key_left)
		return (x + sin(player->angle) * SPEED);
	if (player->key_down)
		return (x - cos(player->angle) * SPEED);
	if (player->key_right)
		return (x - sin(player->angle) * SPEED);
	return (player->x);
}
// implement walls blocking movements ? Check if Pos == '1',
// if true set pos to wall pos

void	move_player(t_player *player, t_cub *cub)
{
	if (player->left_rotate)
		player->angle -= ROT_SPEED;
	if (player->right_rotate)
		player->angle += ROT_SPEED;
	if (player->angle > 2 * PI)
		player->angle -= 2 * PI;
	else if (player->angle < - 2 * PI)
		player->angle += 2 * PI;
	// fix N Player
	/* 	if (player->angle < 0)
			player->angle = 2 * PI; */
	float	x;
	float	y;

	x = new_x(player);
	y = new_y(player);
	printf("player old pos: (%f,%f)\n", player->x, player->y);
	//formule a changer
	if ((y >= 0 && x >= 0 && cub->map[(int)(y + BLOCK * cub->pos_y) / BLOCK][(int)(x + BLOCK * cub->pos_x) / BLOCK] != '1'))
	{
		cub->map[(int)(player->y + BLOCK * cub->pos_y) / BLOCK][(int)(player->x + BLOCK * cub->pos_x) / BLOCK] = '0';
		player->x = x;
		player->y = y;
	}
	printf("player new pos: (%f,%f)\n", player->x, player->y);
}

/*return true if wall*/
bool	touch(t_cub *cub, float px, float py)
{
	int	x;
	int	y;

	x = px;// / BLOCK;
	y = py;// / BLOCK;
	if (cub->map[y] && cub->map[y][x] && cub->map[y][x] == '1')
		return (true);
	return (false);
}

float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

float	fixed_dist(t_cub *cub, float x1, float y1, float x2, float y2)
{
	float	delta_x;
	float	delta_y;
	float	angle;
	float	fix_dist;

	delta_x = x2 - x1;
	delta_y = y2 - y1;
	angle = atan2(delta_y, delta_x) - cub->player.angle;
	fix_dist = distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}

void	draw_line(t_cub *cub, float start_x, int i)
{
	float	ray_x;
	float	ray_y;
	float	dist;
	float	height;
	int		start_y;
	int		end;
	int		side;
	
	side = 0;
	ray_x = cub->player.x;
	ray_y = cub->player.y;
	while (1)
	{
		put_pixel(&cub->mini_map, ray_x + cub->pos_x * BLOCK, ray_y + cub->pos_y * BLOCK, RED);
		ray_x += cos(start_x);
		/*E ou W*/
		printf("ray_x = %f, ray_y = %f;\n", ray_x, ray_y);
		if (touch(cub, ray_x, ray_y))
		{
			// printf("YES %f\n", ray_x /*/ BLOCK*/);
			// printf("YES %f\n", cos(start_x));
			side = 1;
			break ;
		}
		ray_y += sin(start_x);
		side = 0;
		/*N ou S*/
		if (touch(cub, ray_x, ray_y))
		{
			// printf("NO %f\n", ray_y /*/ BLOCK*/);
			// printf("NO %f\n", sin(start_x));
			side = 0;
			break ;
		}
	}
	dist = fixed_dist(cub, cub->player.x, cub->player.y, ray_x, ray_y);
	height = (/*BLOCK*/1 / dist) * (WIDTH / 2);
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
on dessine le player
on dessine la map
*/
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
	fov = PI / 3;
	fraction =  fov / WIDTH;
	start_x = cub->player.angle - fov / 2;
	printf("player.angle = %f\n", cub->player.angle);
	printf("player.pos = (%f,%f)\n", cub->player.x, cub->player.y);
	/*raycasting*/
	i = 0;
	while (i < WIDTH)
	{
		draw_line(cub, start_x, i);
		start_x += fraction;
		i++;
	}
	/*map*/
	float	new_x;
	float	new_y;
	new_x = cub->pos_x * BLOCK + cub->player.x;
	new_y = cub->pos_y * BLOCK + cub->player.y;
	draw_square(cub, new_x, new_y, PLAYER_SIZ, GREEN);
	draw_map(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.data, 0, 0);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->mini_map.data, 0, HEIGHT
		- MAP_HEIGHT);
	return (0);
}
