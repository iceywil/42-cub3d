/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:44:35 by a                 #+#    #+#             */
/*   Updated: 2025/02/12 12:29:12 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	isin(char c, char *str)
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
	ft_printf("%s\n", cub->no);
	ft_printf("%s\n", cub->so);
	ft_printf("%s\n", cub->we);
	ft_printf("%s\n", cub->ea);
	ft_printf("floor: %d, ", cub->f.r);
	ft_printf("%d, ", cub->f.g);
	ft_printf("%d\n", cub->f.b);
	ft_printf("ceiling: %d, ", cub->c.r);
	ft_printf("%d, ", cub->c.g);
	ft_printf("%d\n", cub->c.b);
	cub->i = 0;
	while (cub->map[cub->i])
		ft_printf("%s\n", cub->map[cub->i++]);
	ft_printf("max_y=%i; max_x=%i;\n", cub->map_height, cub->map_width);
	ft_printf("%i pixels = 1 big pixel\n", BIG_PIXEL);
	printf("player_direction(%f, %f); player_position(%f, %f);\n",
		cub->dir_x, cub->dir_y, cub->pos_x, cub->pos_y);
	ft_printf("map width = %i; map height = %i;\n",
		cub->map_width, cub->map_height);
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
