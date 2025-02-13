/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:44:35 by a                 #+#    #+#             */
/*   Updated: 2025/02/13 18:54:13 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <stdio.h>

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	is_in(char c, char *str)
{
	while (*str)
	{
		if (c == *str)
			return (1);
		str++;
	}
	return (0);
}

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

void	print_cub(t_cub *cub)
{
	ft_printf("%d\n", (cub->f_rgb >> 16) & 0xFF);
	ft_printf("%d\n", (cub->f_rgb >> 8) & 0xFF);
	ft_printf("%d\n", cub->f_rgb & 0xFF);
	ft_printf("%d\n", (cub->c_rgb >> 16) & 0xFF);
	ft_printf("%d\n", (cub->c_rgb >> 8) & 0xFF);
	ft_printf("%d\n", cub->c_rgb & 0xFF);
	cub->i = 0;
	while (cub->map[cub->i])
		ft_printf("%s\n", cub->map[cub->i++]);
	ft_printf("max_y=%i; max_x=%i;\n", cub->map_height, cub->map_width);
	ft_printf("%i pixels = 1 big pixel\n", PIXEL);
	printf("player_direction(%f, %f); player_position(%f, %f);\n", cub->dir_x,
		cub->dir_y, cub->pos_x, cub->pos_y);
	ft_printf("map width = %i; map height = %i;\n", cub->map_width,
		cub->map_height);
}

int	line_is_empty(t_cub *cub, char *line)
{
	cub->i = 0;
	while (is_space(line[cub->i]))
		cub->i++;
	if (!line[cub->i])
		return (1);
	return (0);
}

void	print_rgb_components(int rgb)
{
	int	red;
	int	green;
	int	blue;

	red = (rgb >> 16) & 0xFF;
	green = (rgb >> 8) & 0xFF;
	blue = rgb & 0xFF;
	printf("Red: %d\n", red);
	printf("Green: %d\n", green);
	printf("Blue: %d\n", blue);
}

int	rgb_to_int(int red, int green, int blue)
{
	if (red < 0 || red > 255 || green < 0 || green > 255 || blue < 0
		|| blue > 255)
		return (-1);
	return ((red << 16) | (green << 8) | blue);
}
