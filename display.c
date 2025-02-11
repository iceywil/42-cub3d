/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:34:00 by kimnguye          #+#    #+#             */
/*   Updated: 2025/02/11 11:34:16 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_textures(t_cub *cub)
{
	if (!cub->no || !cub->so || !cub->we || !cub->ea)
		exit_error(cub, "Error : Can't open texture");
	mlx_put_image_to_window(cub->mlx, cub->win, cub->no, 0, 0);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->so, 0, cub->text_y);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->ea, cub->text_x, 0);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->we, cub->text_x, cub->text_y);
}