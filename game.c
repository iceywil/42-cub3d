/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 09:13:04 by kduroux           #+#    #+#             */
/*   Updated: 2025/02/14 15:38:29 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube.h"
#include <math.h>

int		ft_game_loop(t_game *game);
void	ft_draw_ray(t_game *game, t_player *player, float start_x, int i);
void	ft_draw_map(t_game *game);
void	ft_clear(t_game *game);

int	ft_game_loop(t_game *game)
{
	t_player	*player;
	float		start_x;
	float		fraction;
	int			i;

	player = &game->player;
	fraction = M_PI / 3 / WINDOWS_WIDTH;
	start_x = player->angle - M_PI / 6;
	i = 0;
	move_player(player);
	ft_clear(game);
	if (DEBUG)
	{
		ft_draw_map(game);
		ft_draw_square(player->x, player->y, 0x00FF00, game);
	}
	while(i < WINDOWS_WIDTH)
	{
		ft_draw_ray(game, player, start_x, i);
		start_x += fraction;
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

void	ft_clear(t_game *game)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (y < WINDOWS_HEIGHT)
	{
		while( x < WINDOWS_WIDTH)
		{
			ft_put_pixel(x, y, 0, game);
			x++;
		}
		x = 0;
		y++;
	}
}

void	ft_draw_map(t_game *game)
{
	char	**map;
	int		color;
	int		x;
	int		y;

	map = game->map;
	color = 0x00FF00;
	x = 0;
	y = 0;
	while (map[y])
	{
		while(map[y][x])
		{
			if (map[y][x] == '1')
				ft_draw_square(x * 64, y * 64, color, game);
			x++;
		}
		x = 0;
		y++;
	}
}

float distance(float x, float y){
    return sqrt(x * x + y * y);
}

float fixed_dist(float x1, float y1, float x2, float y2, t_game *game)
{
    float delta_x = x2 - x1;
    float delta_y = y2 - y1;
    float angle = atan2(delta_y, delta_x) - game->player.angle;
    float fix_dist = distance(delta_x, delta_y) * cos(angle);
    return fix_dist;
}


void	ft_draw_ray(t_game *game, t_player *player, float start_x, int i)
{
	float	ray_x;
	float	ray_y;
	float	sin_angle;
	float	cos_angle;
	float	dist;
	float	height;
	int		start_y;
	int		end;

	sin_angle = sin(start_x);
	cos_angle = cos(start_x);
	ray_x = player->x;
	ray_y = player->y;
	while(!ft_touch(ray_x, ray_y, game))
	{
		if (DEBUG)
			ft_put_pixel(ray_x, ray_y, 0xFF0000, game);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	dist = fixed_dist(player->x, player->y, ray_x, ray_y, game);
	height = ( 64 / dist) * (WINDOWS_WIDTH / 2);
	start_y = (WINDOWS_HEIGHT - height) / 2;
	end = start_y + height;
	while(start_y < end)
	{
		ft_put_pixel(i, start_y, 0x0000FF, game);
		start_y++;
	}
}