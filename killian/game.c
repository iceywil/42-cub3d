/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 09:13:04 by kduroux           #+#    #+#             */
/*   Updated: 2025/03/05 10:29:18 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		ft_game_loop(t_game *game);
void	ft_clear(t_game *game);
float	distance(float x, float y);
float	fixed_dist(float x2, float y2, t_game *game);

void	render_background(t_game *data)
{
	ft_memcpy(data->img_tab[0].addr, data->img_tab[1].addr,
		WINDOWS_HEIGHT * WINDOWS_WIDTH * (data->img_tab[1].bits_pp / 8));
}

int	ft_game_loop(t_game *game)
{
	t_player	*player;
	float		start_x;
	float		fraction;
	int			i;

	player = &game->player;
	fraction = M_PI / 3 / WINDOWS_WIDTH;
	start_x = player->angle - M_PI / 6;
	start_x = fmod(start_x, 2 * M_PI);
	if (start_x < 0)
		start_x += 2 * M_PI;
	render_background(game);
	ft_move_player(game);
	i = 0;
	while(i < WINDOWS_WIDTH)
	{
		ft_draw_ray(game, start_x, i);
		start_x += fraction;
		i++;
	}
	if (player->minimap)
		render_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img_tab[0].ptr, 0, 0);
	return (0);
}

float distance(float x, float y)
{
	return sqrt(x * x + y * y);
}

float fixed_dist(float x2, float y2, t_game *game)
{
	float delta_x;
	float delta_y;
	float angle;
	float fix_dist;

	delta_x = x2 - game->player.x;
	delta_y = y2 - game->player.y;
	angle = atan2(delta_y, delta_x) - game->player.angle;
	fix_dist = distance(delta_x, delta_y) * cos(angle);
	return fix_dist;
}
