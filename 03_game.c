/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 09:13:04 by kduroux           #+#    #+#             */
/*   Updated: 2025/02/14 17:29:50 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_game_loop(t_cub *cub);
void	ft_draw_ray(t_cub *cub, int start_x, int i);
void	ft_clear(t_cub *cub);

int	ft_game_loop(t_cub *cub)
{
	int	i;
	double	start_x;
	double	fraction;

	i = 0;
	ft_clear(cub);
	ft_background(cub);
	fraction = M_PI / 3 / WIDTH;
	start_x = cub->dir_angle - M_PI / 6;
	while(i < WIDTH)
	{
		ft_draw_ray(cub, start_x, i);
		start_x += fraction;
		i++;
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.mlx, 0, 0);
	ft_mini_map(cub);
	return (0);
}

void	ft_clear(t_cub *cub)
{
	int		x;
	int		y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while( x < WIDTH)
			pixel_to_img(&cub->img, x++, y, BLACK);
		y++;
	}
}

float distance(float x, float y)
{
	return sqrt(x * x + y * y);
}

float fixed_dist(float x1, float y1, float x2, float y2, t_cub *cub)
{
	float delta_x = x2 - x1;
	float delta_y = y2 - y1;
	float angle = atan2(delta_y, delta_x) - cub->dir_angle;
	float fix_dist = distance(delta_x, delta_y) * cos(angle);
	return fix_dist;
}


/**/
void	ft_draw_ray(t_cub *cub, int start_x, int i)
{
	float	ray_x;
	float	ray_y;
	float	dist;
	float	height;
	int		start_y;
	int		end;

	ray_x = cub->pos_x;
	ray_y = cub->pos_y;
	while(!ft_touch(ray_x, ray_y, cub))
	{
		ray_x += cos(start_x);
		ray_y += sin(start_x);
	}
	//printf("i=%i: ray_x=%f, ray_y=%f, cos=%f, sin=%f\n", i, ray_x, ray_y, cos(cub->dir_angle), sin(cub->dir_angle));
	dist = fixed_dist(cub->pos_x, cub->pos_y, ray_x, ray_y, cub);
	printf("dist = %f\n", dist);
	height = ( 1 / dist) * (WIDTH / 2);
	start_y = (HEIGHT - height) / 2;
	end = start_y + height;
	while(start_y < end)
	{
		if (isin_img(i, start_y, WIDTH, HEIGHT))
			pixel_to_img(&cub->img, i, start_y, BLUE);
		start_y++;
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.mlx, 0, 0);
}


