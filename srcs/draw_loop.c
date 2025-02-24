/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:25:12 by kimnguye          #+#    #+#             */
/*   Updated: 2025/02/24 15:25:20 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*on actualise la position et direction du player
on clear les images
on raycaste, et on draw le player et la map*/
int	draw_loop(t_cub *cub)
{
	float	fraction;
	float	start_x;
	int		i;
	int		x;

	move_player(&cub->player, cub);
	clear_image(&cub->img, HEIGHT, WIDTH);
	clear_image(&cub->mini_map, MAP_HEIGHT, MAP_WIDTH);
	background(cub);
	draw_map(cub);
	fraction = FOV / WIDTH;
	start_x = cub->player.angle - FOV / 2;
	x = 0;
	while (x < WIDTH)
	{
		calc_side(cub, start_x, x);
		wall_texture(cub, start_x, x);
		draw_wall(cub, cub->wall_texture, x);
		start_x += fraction;
		x++;
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.data, 0, 0);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->mini_map.data, 0, HEIGHT
		- MAP_HEIGHT);
	return (0);
}