/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 23:30:41 by a                 #+#    #+#             */
/*   Updated: 2025/02/24 05:43:02 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	calc_side_dist(t_cub *cub)
{
	cub->camera_x = 2 * cub->x / (double)WIDTH - 1;
	cub->ray_dir_x = cub->dir_x + cub->plane_x * cub->camera_x;
	cub->ray_dir_y = cub->dir_y + cub->plane_y * cub->camera_x;
	cub->delta_dist_x = (cub->ray_dir_x == 0) ? 1e30 : fabs(1 / cub->ray_dir_x);
	cub->delta_dist_y = (cub->ray_dir_y == 0) ? 1e30 : fabs(1 / cub->ray_dir_y);
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
}

void	calc_side(t_cub *cub)
{
	cub->hit = 0;
	while (cub->hit == 0)
	{
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
		if (cub->map[cub->map_x][cub->map_y] == '1')
			cub->hit = 1;
	}
}

void	calc_perp_wall(t_cub *cub)
{
	if (cub->side == 0)
		cub->perp_wall_dist = (cub->side_dist_x - cub->delta_dist_x);
	else
		cub->perp_wall_dist = (cub->side_dist_y - cub->delta_dist_y);
	cub->line_height = (int)(HEIGHT / cub->perp_wall_dist);
	cub->draw_start = -cub->line_height / 2 + HEIGHT / 2;
	if (cub->draw_start < 0)
		cub->draw_start = 0;
	cub->draw_end = cub->line_height / 2 + HEIGHT / 2;
	if (cub->draw_end >= HEIGHT)
		cub->draw_end = HEIGHT - 1;
	if (cub->side == 0)
		cub->wall_x = cub->pos_y + cub->perp_wall_dist * cub->ray_dir_y;
	else
		cub->wall_x = cub->pos_x + cub->perp_wall_dist * cub->ray_dir_x;
	cub->wall_x -= floor((cub->wall_x));
	cub->tex_x = (int)(cub->wall_x * (double)cub->texture_n.width);
	if (cub->side == 0 && cub->ray_dir_x > 0)
		cub->tex_x = cub->texture_n.width - cub->tex_x - 1;
	if (cub->side == 1 && cub->ray_dir_y < 0)
		cub->tex_x = cub->texture_n.width - cub->tex_x - 1;
}

void	draw_tex(t_cub *cub)
{
	int		tex_x;
	double	step;
	double	tex_pos;
	int		tex_y;
	int		tex_index;
	int		color;

	step = 1.0 * cub->texture_n.height / cub->line_height;
	tex_pos = (cub->draw_start - HEIGHT / 2 + cub->line_height / 2) * step;
	while (cub->draw_start < cub->draw_end)
	{
		tex_y = (int)tex_pos & (cub->texture_n.height - 1);
		tex_pos += step;
		tex_index = tex_y * cub->texture_n.size_line + cub->tex_x
			* (cub->texture_n.bpp / 8);
		color = *(int *)(cub->texture_n.addr + tex_index);
		/* 	if (side == 1)
				color = (color >> 1) & 8355711; */
		put_pixel(&cub->img, cub->x, cub->draw_start, color);
		cub->draw_start++;

	}
}

int	ray_loop(t_cub *cub)
{
	int	time;
	int	frame_time;

	move_player(cub);
	clear_image(&cub->img);
	background(cub);
	cub->x = 0;
	while (cub->x < WIDTH)
	{
		cub->map_x = (int)cub->pos_x;
		cub->map_y = (int)cub->pos_y;
		calc_side_dist(cub);
		calc_side(cub);
		calc_perp_wall(cub);
		draw_tex(cub);
		cub->x++;
	}
	time = get_time();
	frame_time = (time - cub->oldTime) / 1000.0;
	cub->oldTime = time;
	cub->move_speed = frame_time * 5.0;
	cub->rot_speed = frame_time * 3.0;
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.data, 0, 0);
	return (0);
}
