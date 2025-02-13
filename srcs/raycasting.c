/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:17:36 by kimnguye          #+#    #+#             */
/*   Updated: 2025/02/13 19:54:48 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*ray direction*/
void	ray_direction(t_cub *cub)
{
	int		x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	camera_x;
	
	x = 0;
	while (x < WIDTH)
	{
		camera_x = 2 * x / (double) WIDTH - 1;
		ray_dir_x = cub->dir_x + cub->plane_x * camera_x;
		ray_dir_y = cub->dir_y + cub->plane_y * camera_x;
	}
// }

// /*delta distance*/
// void	delta_distance(t_cub *cub, double ray_dir_x, double ray_dir_y)
// {
	double delta_dist_x; 
	double delta_dist_y;
	
	delta_dist_x = fabs(1 / ray_dir_x);
	delta_dist_y = fabs(1 / ray_dir_y);

	int step_x;
	int step_y;

	double side_dist_x;
	double side_dist_y;
	double map_x;
	double map_y;

	//the current square of the map the ray is in
	map_x = cub->pos_x; 
	map_y = cub->pos_y;
	//next_grid_distance
	if (ray_dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (cub->pos_x - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - cub->pos_x) * delta_dist_x;
	}
	if (ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (cub->pos_y - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - cub->pos_y) * delta_dist_y;
	}

	/*DDA*/
	int side;

	while (42)
	{
		if (side_dist_x < side_dist_y)
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
		if (cub->map[(int)map_x][(int)map_y] == '1')
			break;
	}

	/*wall height*/
	double wall_dist;

	if (side == 0)
		wall_dist = (map_x - cub->pos_x + (1 - step_x) / 2) / ray_dir_x;
	else
		wall_dist = (map_y - cub->pos_y + (1 - step_y) / 2) / ray_dir_y;

	int line_height = (int)(HEIGHT / wall_dist);

	int draw_start = -line_height / 2 + HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;

	int draw_end = line_height / 2 + HEIGHT / 2;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;

	// if (side == 0)
	// 	wall_x = cub->pos_y + wall_dist * ray->dy;
	// else
	// 	wall_x = cub->pos_x + wall_dist * ray->dx;
	// wall_x -= floor(wall_x);
}
