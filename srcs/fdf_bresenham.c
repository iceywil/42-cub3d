/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bresenham.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 14:53:47 by kimnguye          #+#    #+#             */
/*   Updated: 2025/02/14 16:53:27 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	segment_vertical(t_cub *cub, t_slope *ab)
{
	int	y;
	int	y_max;

	if (ab->dy >= 0)
	{
		y = ab->j;
		y_max = ab->j + ab->dy; 
	}
	else
	{
		y = ab->j + ab->dy;
		y_max = ab->j;
	}
	while (y <= y_max)
	{
		if (is_in_img(ab->i, y, MAP_WIDTH, MAP_HEIGHT))
			pixel_to_img(&cub->mini_map, ab->i, y, GREEN);
		y++;
	}
}

void	segment_q1(t_cub *cub, t_slope *ab)
{
	ab->p = 2 * ab->dy - ab->dx;
	while (ab->dx >= ab->dy && ab->i <= ab->x_b)
	{
		if (is_in_img(ab->i, ab->j, MAP_WIDTH, MAP_HEIGHT))
			pixel_to_img(&cub->mini_map, ab->i, ab->j, GREEN);
		ab->p += 2 * ab->dy;
		if (ab->p >= 0)
		{
			ab->j++;
			ab->p -= 2 * ab->dx;
		}
		ab->i++;
	}
	while (ab->dy > ab->dx && ab->j <= ab->y_b)
	{
		if (is_in_img(ab->i, ab->j, MAP_WIDTH, MAP_HEIGHT))
			pixel_to_img(&cub->mini_map, ab->i, ab->j, GREEN);
		ab->p += 2 * ab->dx;
		if (ab->p >= 0)
		{
			ab->i++;
			ab->p -= 2 * ab->dy;
		}
		ab->j++;
	}
}

void	segment_q2(t_cub *cub, t_slope *ab)
{
	ab->p = 2 * ab->dx - ab->dy;
	while (ab->i >= ab->x_b && fabs(ab->dy) <= fabs(ab->dx))
	{
		if (is_in_img(ab->i, ab->j, MAP_WIDTH, MAP_HEIGHT))
			pixel_to_img(&cub->mini_map, ab->i, ab->j, GREEN);
		ab->p += 2 * ab->dy;
		if (ab->p >= 0)
		{
			ab->j++;
			ab->p += 2 * ab->dx;
		}
		ab->i--;
	}
	while (ab->j <= ab->y_b && fabs(ab->dy) > fabs(ab->dx))
	{
		if (is_in_img(ab->i, ab->j, MAP_WIDTH, MAP_HEIGHT))
			pixel_to_img(&cub->mini_map, ab->i, ab->j, GREEN);
		ab->p -= 2 * ab->dx;
		if (ab->p >= 0)
		{
			ab->i--;
			ab->p -= 2 * ab->dy;
		}
		ab->j++;
	}
}

void	segment_q3(t_cub *cub, t_slope *ab)
{
	ab->p = 2 * ab->dx - ab->dy;
	while (ab->i >= ab->x_b && fabs(ab->dy) <= fabs(ab->dx))
	{
		if (is_in_img(ab->i, ab->j, MAP_WIDTH, MAP_HEIGHT))
			pixel_to_img(&cub->mini_map, ab->i, ab->j, GREEN);
		ab->p -= 2 * ab->dy;
		if (ab->p >= 0)
		{
			ab->j--;
			ab->p += 2 * ab->dx;
		}
		ab->i--;
	}
	while (ab->j >= ab->y_b && fabs(ab->dy) > fabs(ab->dx))
	{
		if (is_in_img(ab->i, ab->j, MAP_WIDTH, MAP_HEIGHT))
			pixel_to_img(&cub->mini_map, ab->i, ab->j, GREEN);
		ab->p -= 2 * ab->dx;
		if (ab->p >= 0)
		{
			ab->i--;
			ab->p += 2 * ab->dy;
		}
		ab->j--;
	}
}

void	segment_q4(t_cub *cub, t_slope *ab)
{
	ab->p = 2 * ab->dy - ab->dx;
	while (ab->i <= ab->x_b && fabs(ab->dy) <= fabs(ab->dx))
	{
		if (is_in_img(ab->i, ab->j, MAP_WIDTH, MAP_HEIGHT))
			pixel_to_img(&cub->mini_map, ab->i, ab->j, GREEN);
		ab->p -= 2 * ab->dy;
		if (ab->p >= 0)
		{
			ab->j--;
			ab->p -= 2 * ab->dx;
		}
		ab->i++;
	}
	while (ab->j >= ab->y_b && fabs(ab->dy) > fabs(ab->dx))
	{
		if (is_in_img(ab->i, ab->j, MAP_WIDTH, MAP_HEIGHT))
			pixel_to_img(&cub->mini_map, ab->i, ab->j, GREEN);
		ab->p += 2 * ab->dx;
		if (ab->p >= 0)
		{
			ab->i++;
			ab->p += 2 * ab->dy;
		}
		ab->j--;
	}
}
