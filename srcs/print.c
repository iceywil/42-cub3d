/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:07:27 by kimnguye          #+#    #+#             */
/*   Updated: 2025/02/18 14:16:14 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <stdio.h>

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
	printf("player position(%f, %f) angle=%f;\n",
		cub->player.x, cub->player.y, cub->player.angle);
}
