/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:57:53 by kimnguye          #+#    #+#             */
/*   Updated: 2025/02/27 18:45:19 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	show_texture(t_cub *cub)
{
	int	width;
	int	height;

	width = max(cub->texture_n.width, cub->texture_s.width);
	height = max(cub->texture_e.height, cub->texture_w.height);
	mlx_put_image_to_window(cub->mlx, cub->win,
		cub->texture_n.data, cub->texture_w.width, 0);
	mlx_put_image_to_window(cub->mlx, cub->win,
		cub->texture_s.data, cub->texture_w.width,
		height + cub->texture_n.height);
	mlx_put_image_to_window(cub->mlx, cub->win,
		cub->texture_e.data, width + cub->texture_w.width,
		cub->texture_n.height);
	mlx_put_image_to_window(cub->mlx, cub->win,
		cub->texture_w.data, 0, cub->texture_n.height);
}
