/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:34:00 by kimnguye          #+#    #+#             */
/*   Updated: 2025/02/12 12:20:30 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_textures(t_cub *cub)
{
	cub->text_n = mlx_xpm_file_to_image
		(cub->mlx, cub->no, &cub->text_x, &cub->text_y);
	cub->text_s = mlx_xpm_file_to_image
		(cub->mlx, cub->so, &cub->text_x, &cub->text_y);
	cub->text_w = mlx_xpm_file_to_image
		(cub->mlx, cub->we, &cub->text_x, &cub->text_y);
	cub->text_e = mlx_xpm_file_to_image
		(cub->mlx, cub->ea, &cub->text_x, &cub->text_y);
	if (!cub->text_n || !cub->text_s || !cub->text_w || !cub->text_e)
		exit_error(cub, "Error : Can't open texture");
	mlx_put_image_to_window(cub->mlx, cub->win, cub->text_n, 0, 0);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->text_s, 0, cub->text_y);
	mlx_put_image_to_window
		(cub->mlx, cub->win, cub->text_e, cub->text_x, 0);
	mlx_put_image_to_window
		(cub->mlx, cub->win, cub->text_w, cub->text_x, cub->text_y);
}
