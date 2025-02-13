/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 01:33:34 by a                 #+#    #+#             */
/*   Updated: 2025/02/12 20:25:22 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_mlx(t_cub *cub)
{
	if (cub->img->data)
		mlx_destroy_image(cub->mlx, cub->img->data);
	if (cub->mini_map->data)
		mlx_destroy_image(cub->mlx, cub->mini_map->data);
	if (cub->win)
		mlx_destroy_window(cub->mlx, cub->win);
	if (cub->mlx)
		mlx_destroy_display(cub->mlx);
	if (cub->mlx)
		free(cub->mlx);
}

void	free_cub(t_cub *cub)
{
	if (cub->map)
		ft_free_double_tab(&cub->map);
}

int	close_all(t_cub *cub)
{
	free_cub(cub);
	free_mlx(cub);
	exit(EXIT_SUCCESS);
	return (0);
}

void	exit_error(t_cub *cub, char *str)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(str, 2);
	free_cub(cub);
	free_mlx(cub);
	exit(1);
}
