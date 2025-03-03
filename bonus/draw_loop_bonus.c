/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_loop_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:25:12 by kimnguye          #+#    #+#             */
/*   Updated: 2025/02/27 18:43:03 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	put_to_window(t_cub *cub)
{
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.data, 0, 0);
	if (cub->map_show)
		mlx_put_image_to_window(cub->mlx, cub->win, cub->mini_map.data, 0,
			HEIGHT - MAP_HEIGHT);
	if (cub->tex_show)
		show_texture(cub);
}

/*on actualise la position et direction du player
on clear les images
on raycaste, et on draw le player et la map*/
int	draw_loop(t_cub *cub)
{
	float	start_x;
	int		x;

	move_player(&cub->player, cub);
	clear_image(&cub->img, HEIGHT, WIDTH);
	clear_image(&cub->mini_map, MAP_HEIGHT, MAP_WIDTH);
	background(cub);
	draw_map(cub);
	start_x = cub->player.angle - FOV / 2;
	x = 0;
	while (x < WIDTH)
	{
		calc_side(cub, start_x, x);
		wall_texture(cub, start_x, x);
		draw_wall(cub, cub->wall_texture, x);
		start_x += cub->fraction;
		x++;
	}
	put_to_window(cub);
	return (0);
}
