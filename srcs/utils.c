/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:44:35 by a                 #+#    #+#             */
/*   Updated: 2025/02/17 15:17:54 by kimnguye         ###   ########.fr       */
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
void	print_mlx(t_cub *cub)
{
	ft_printf("img.data = %p\n", cub->img.data);
	ft_printf("mini_map.data = %p\n", cub->mini_map.data);
	ft_printf("img.addr = %p\n", cub->img.addr);
	ft_printf("mini_map.addr = %p\n", cub->mini_map.addr);
}

void	print_cub(t_cub *cub)
{
	ft_printf("%d, ", (cub->floor.r));
	ft_printf("%d, ", (cub->floor.g));
	ft_printf("%d\n", (cub->floor.b));
	ft_printf("%d, ", (cub->ceiling.r));
	ft_printf("%d, ", (cub->ceiling.g));
	ft_printf("%d\n", (cub->ceiling.b));
	cub->i = 0;
	while (cub->map[cub->i])
		ft_printf("%s\n", cub->map[cub->i++]);
	ft_printf("max_y=%i; max_x=%i;\n", cub->map_height, cub->map_width);
	printf("player map position(%i, %i);\n", cub->pos_j, cub->pos_i);
	ft_printf("%i pixels = 1 big pixel\n", BLOCK);
	printf("player position(%f, %f) angle=%f;\n", cub->player.x, cub->player.y, cub->player.angle);
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
