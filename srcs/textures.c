/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:57:53 by kimnguye          #+#    #+#             */
/*   Updated: 2025/02/24 15:17:26 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	print_texture(t_cub *cub)
{
	mlx_put_image_to_window(cub->mlx, cub->win,
		cub->texture_n.data, cub->texture_n.width, 0);
	mlx_put_image_to_window(cub->mlx, cub->win,
		cub->texture_s.data, cub->texture_n.width, cub->texture_n.height * 2);
	mlx_put_image_to_window(cub->mlx, cub->win,
		cub->texture_e.data, cub->texture_n.width * 2, cub->texture_n.height);
	mlx_put_image_to_window(cub->mlx, cub->win,
		cub->texture_w.data, 0, cub->texture_n.height);
}
