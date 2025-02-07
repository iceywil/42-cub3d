/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:44:35 by a                 #+#    #+#             */
/*   Updated: 2025/02/07 13:29:28 by kimnguye         ###   ########.fr       */
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
	ft_printf("%d\n", cub->f_r);
	ft_printf("%d\n", cub->f_g);
	ft_printf("%d\n", cub->f_b);
	ft_printf("%d\n", cub->c_r);
	ft_printf("%d\n", cub->c_g);
	ft_printf("%d\n", cub->c_b);
	cub->i = 0;
	while (cub->map[cub->i])
	{
		ft_printf("%s\n", cub->map[cub->i]);
		cub->i++;
	}
}