/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_loop_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:25:12 by kimnguye          #+#    #+#             */
/*   Updated: 2025/03/06 15:52:05 by kimnguye         ###   ########.fr       */
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
	double	ray_angle;
	int		x;

	move_player(&cub->player, cub);
	clear_image(&cub->img, HEIGHT, WIDTH);
	clear_image(&cub->mini_map, MAP_HEIGHT, MAP_WIDTH);
	background(cub);
	ray_angle = cub->player.angle - FOV / 2;
	x = 0;
	while (x < WIDTH)
	{
		init_ray(&cub->ray, cub, ray_angle);
		calc_side(cub, ray_angle, x);
		wall_texture(cub, ray_angle, x);
		draw_wall(cub, cub->wall_texture, x);
		ray_angle += cub->fraction;
		x++;
	}
	show_sprite(cub);
	draw_map(cub);
	put_to_window(cub);
	cub->sprite.num++;
	if (cub->sprite.num == 8)
		cub->sprite.num = 0;
	return (0);
}
