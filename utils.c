/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:44:35 by a                 #+#    #+#             */
/*   Updated: 2025/02/12 10:27:09 by kimnguye         ###   ########.fr       */
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
	ft_printf("floor: %d, ", cub->floor.r);
	ft_printf("%d, ", cub->floor.g);
	ft_printf("%d\n", cub->floor.b);
	ft_printf("ceiling: %d, ", cub->ceiling.r);
	ft_printf("%d, ", cub->ceiling.g);
	ft_printf("%d\n", cub->ceiling.b);
	cub->i = 0;
	while (cub->map[cub->i])
	{
		ft_printf("%s\n", cub->map[cub->i]);
		cub->i++;
	}
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
