/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 01:49:52 by a                 #+#    #+#             */
/*   Updated: 2025/02/11 19:28:14 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <math.h>

int	main(int argc, char **argv)
{
	t_cub	cub;
	int		n;

	if (argc != 2)
		return (ft_putendl_fd("Error\nIncorrect number of arguments", 2), 1);
	if (ft_strncmp(".cub", &argv[1][ft_strlen(argv[1]) - 4], 4))
		return (ft_printf("Wrong file format: a .cub is expected!\n"), 1);
	init_all(&cub);
	init_mlx(&cub);
//	test_ray(&cub);
	draw_map(&cub);
	mlx_hook((&cub)->win, KEYPRESS_EVENT, 1L << 0, key_hook, (&cub));
	mlx_hook((&cub)->win, BUTTONPRESS_EVENT, 1L << 2, mouse_hook, (&cub));
	mlx_hook((&cub)->win, 17, 1L << 17, close_all, (&cub));
	mlx_loop(cub.mlx);
	return (0);
}

/* void	test_ray(t_cub *cub)
{
	int		hit;
	int		scale;
	double	ray_dir_x;
	double	ray_dir_y;
	double	plane_x;
	double	camera_x;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perpWallDist;
	int		step_x;
	int		step_y;

	cub->pos_x = 22;
	cub->pos_y = 12; // x and y start position
	cub->dir_x = -1;
	cub->dir_y = 0; // initial direction vector
	cub->plane_x = 0;
	cub->plane_y = 0.66; // the 2d raycaster version of camera plane
	cub->x = 0;
	while (cub->x < 1920)
	{
		calculate_ray(cub);
		run_dda(cub);
		run_image(cub);
		cub->x++;
	}
} */
/* void	calculate_ray(t_cub *cub)
{
	// calculate ray position and direction
	cub->camera_x = 2 * cub->x / 1920 - 1; // x-coordinate in camera space
	cub->ray_dir_x = cub->dir_x + cub->plane_x * cub->camera_x;
	cub->ray_dir_y = cub->dir_y + cub->plane_y * cub->camera_x;
	cub->delta_dist_x = abs(1 / cub->ray_dir_x);
	cub->delta_dist_y = abs(1 / cub->ray_dir_y);
	// which box of the map we're in
	cub->map_x = (int)cub->pos_x;
	cub->map_y = (int)cub->pos_y;
	// length of ray from current position to next x or y-side
	// length of ray from one x or y-side to next x or y-side
	if (cub->ray_dir_x == 0)
		cub->delta_dist_x = 1e30;
	else
		cub->delta_dist_x = fabs(1 / cub->ray_dir_x);
	if (cub->ray_dir_y == 0)
		cub->delta_dist_y = 1e30;
	else
		cub->delta_dist_y = fabs(1 / cub->ray_dir_y);
	// what direction to step in x or y-direction (either +1 or -1)
	int hit = 0; // was there a wall hit?
	int side;    // was a NS or a EW wall hit?
					// calculate step and initial sideDist
	if (cub->ray_dir_x < 0)
	{
		cub->step_x = -1;
		cub->side_dist_x = (cub->pos_x - cub->map_x) * cub->delta_dist_x;
	}
	else
	{
		cub->step_x = 1;
		cub->side_dist_x = (cub->map_x + 1.0 - cub->pos_x) * cub->delta_dist_x;
	}
	if (cub->ray_dir_y < 0)
	{
		cub->step_y = -1;
		cub->side_dist_y = (cub->pos_y - cub->map_y) * cub->delta_dist_y;
	}
	else
	{
		cub->step_y = 1;
		cub->side_dist_y = (cub->map_y + 1.0 - cub->pos_y) * cub->delta_dist_y;
	}
} */
/* void	run_dda(t_cub *cub)
{
	hit = 0;
	while (hit == 0)
	{
		// jump to next map square, either in x-direction, or in y-direction
		if (cub->side_dist_x < cub->side_dist_y)
		{
			cub->side_dist_x += cub->delta_dist_x;
			cub->map_x += cub->step_x;
			cub->side = 0;
		}
		else
		{
			cub->side_dist_y += cub->delta_dist_y;
			cub->map_y += cub->step_y;
			cub->side = 1;
		}
		// Check if ray has hit a wall
		if (cub->map[cub->map_x][cub->map_y] > 0)
			hit = 1;
	}
} */
/* void	run_image(t_cub *cub)
{
	// Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
	if (cub->side == 0)
		cub->prep_wall_dist = (cub->side_dist_x - cub->delta_dist_x);
	else
		cub->prep_wall_dist = (cub->side_dist_y - cub->delta_dist_y);
	if (cub->side == WEST || cub->side == EAST)
		cub->wall_x = cub->player_y + cub->prep_wall_dist * cub->ray_dir_y;
	else
		cub->wall_x = cub->player_x + cub->prep_wall_dist * cub->ray_dir_x;
	cub->wall_x -= floor(cub->wall_x); // make it start from 0
	cub->x = cub->ray_x;
	// paint texture if the ray hits a wall
	if (cub->map[cub->map_y][cub->map_x] == '1')
		// assumes that this function paints textures
		paint_texture_line(cub, cub->wall_x);
	// reset line to start at the top pixel
	cub->ray_y_start = 0;
	// reset line to end at the textures beginning pixel
	cub->ray_y_end = cub->draw_start;
	// assumes that this function paints a solid color
	paint_line(cub, cub->crgb); // we paint the ceiling
	// reset line to start at the bottom pixel
	cub->ray_y_start = 1080;
	// reset line to end at the textures end pixel
	cub->ray_y_end = cub->draw_end;
	// assumes that this function paints a solid color
	paint_line(cub, cub->frgb); // we paint the floor
} */
/* void	texture_on_img(t_cub *cub, t_img *texture)
{
	scale = line->y * texture->line_length - (WIN_HEIGHT
			* root->game->player->cam_height) * texture->line_length / 2
		+ ray->line_height * texture->line_length / 2;
	line->tex_y = ((scale * texture->height) / ray->line_height)
		/ texture->line_length;
	root->mlx_img->data[line->y * root->mlx_img->line_length + line->x
		* root->mlx_img->bits_per_pixel / 8] = texture->data[line->tex_y
		* texture->line_length + line->tex_x * (texture->bits_per_pixel / 8)];
	root->mlx_img->data[line->y * root->mlx_img->line_length + line->x
		* (root->mlx_img->bits_per_pixel / 8) + 1] = texture->data[line->tex_y
		* texture->line_length + line->tex_x * (texture->bits_per_pixel / 8)
		+ 1];
	root->mlx_img->data[line->y * root->mlx_img->line_length + line->x
		* (root->mlx_img->bits_per_pixel / 8) + 2] = texture->data[line->tex_y
		* texture->line_length + line->tex_x * (texture->bits_per_pixel / 8)
		+ 2];
} */
/* void	test_ray(t_cub *cub)
{
	plane_x = 0, plane_y;
	double pos_x = 22, pos_y = 12; // x and y start position
	double dir_x = -1, dir_y = 0;  // initial direction vector
	plane_x = 0, plane_y = 0.66;
	// the 2d raycaster version of camera plane
	while (!done())
	{
		for (int x = 0; x < w; x++)
		{
			// calculate ray position and direction
			camera_x = 2 * x / double(w) - 1;
			// x-coordinate in camera space
			ray_dir_x = dir_x + plane_x * camera_x;
			ray_dir_y = dir_y + plane_y * camera_x;
			delta_dist_x = abs(1 / ray_dir_x);
			delta_dist_y = abs(1 / ray_dir_y);
			// which box of the map we're in
			map_x = int(pos_x);
			map_y = int(pos_y);
			// length of ray from current position to next x or y-side
			// length of ray from one x or y-side to next x or y-side
			delta_dist_x = (ray_dir_x == 0) ? 1e30 : std::abs(1 / ray_dir_x);
			delta_dist_y = (ray_dir_y == 0) ? 1e30 : std::abs(1 / ray_dir_y);
			// what direction to step in x or y-direction (either +1 or -1)
			int hit = 0; // was there a wall hit?
			int side;    // was a NS or a EW wall hit?
						// calculate step and initial sideDist
			if (ray_dir_x < 0)
			{
				step_x = -1;
				side_dist_x = (pos_x - map_x) * delta_dist_x;
			}
			else
			{
				step_x = 1;
				side_dist_x = (map_x + 1.0 - pos_x) * delta_dist_x;
			}
			if (ray_dir_y < 0)
			{
				step_y = -1;
				side_dist_y = (pos_y - map_y) * delta_dist_y;
			}
			else
			{
				step_y = 1;
				side_dist_y = (map_y + 1.0 - pos_y) * delta_dist_y;
			}
			// perform DDA
			while (hit == 0)
			{
				// jump to next map square, either in x-direction, or in y
				-direction if (side_dist_x < side_dist_y)
				{
					side_dist_x += delta_dist_x;
					map_x += step_x;
					side = 0;
				}
				else
				{
					side_dist_y += delta_dist_y;
					map_y += step_y;
					side = 1;
				}
				// Check if ray has hit a wall
				if (worldMap[map_x][map_y] > 0)
					hit = 1;
			}
			// Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
			if (side == 0)
				perpWallDist = (side_dist_x - delta_dist_x);
			else
				perpWallDist = (side_dist_y - delta_dist_y);
		}
	}
}

void	draw(t_cub *cub)
{
	double	wall_x;

	if (ray->side == WEST || ray->side == EAST)
		wall_x = player->pos.y + ray->prep_wall_dist * ray->ray_dir_y;
	else
		wall_x = player->pos.x + ray->prep_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x); // make it start from 0
	line->x = ray->curr_x;
	// paint texture if the ray hits a wall
	if (root->game->map[ray->map_y][ray->map_x] == '1')
		// assumes that this function paints textures
		paint_texture_line(root, ray, line, wall_x);
	// reset line to start at the top pixel
	line->y0 = 0;
	// reset line to end at the textures beginning pixel
	line->y1 = ray->draw_start;
	// assumes that this function paints a solid color
	paint_line(cub, line, cub->crgb); // we paint the ceiling
	// reset line to start at the bottom pixel
	line->y0 = WIN_HEIGHT;
	// reset line to end at the textures end pixel
	line->y1 = ray->draw_end;
	// assumes that this function paints a solid color
	paint_line(cub, line, cub->frgb); // we paint the floor
}



*/
