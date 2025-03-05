/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:57:53 by kimnguye          #+#    #+#             */
/*   Updated: 2025/03/05 23:05:55 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	door_action(char **map, t_player player)
{
	float	x;
	float	y;
	int		i;

	i = 0;
	while (i < MARGIN_DOOR)
	{
		x = player.x + cos(player.angle) * SPEED * i;
		y = player.y + sin(player.angle) * SPEED * i;
		if (map[(int)y / BLOCK][(int)x / BLOCK] == 'D')
		{
			map[(int)y / BLOCK][(int)x / BLOCK] = 'O';
			return ;
		}
		if (map[(int)y / BLOCK][(int)x / BLOCK] == 'O')
		{
			map[(int)y / BLOCK][(int)x / BLOCK] = 'D';
			return ;
		}
		i++;
	}
}

int	is_door_open(char **map, float x, float y)
{
	if (map[(int)y / BLOCK][(int)x / BLOCK] == 'O')
		return (1);
	if (map[(int)(y - PLAYER_SIZ) / BLOCK]
		[(int)(x - PLAYER_SIZ) / BLOCK] == 'O')
		return (1);
	if (map[(int)(y - PLAYER_SIZ) / BLOCK]
		[(int)(x + PLAYER_SIZ) / BLOCK] == 'O')
		return (1);
	if (map[(int)(y + PLAYER_SIZ) / BLOCK]
		[(int)(x + PLAYER_SIZ) / BLOCK] == 'O')
		return (1);
	if (map[(int)(y + PLAYER_SIZ) / BLOCK]
		[(int)(x - PLAYER_SIZ) / BLOCK] == 'O')
		return (1);
	return (0);
}

int	is_door_closed(char **map, float x, float y)
{
	if (map[(int)y / BLOCK][(int)x / BLOCK] == 'D')
		return (1);
	if (map[(int)(y - PLAYER_SIZ) / BLOCK]
		[(int)(x - PLAYER_SIZ) / BLOCK] == 'D')
		return (1);
	if (map[(int)(y - PLAYER_SIZ) / BLOCK]
		[(int)(x + PLAYER_SIZ) / BLOCK] == 'D')
		return (1);
	if (map[(int)(y + PLAYER_SIZ) / BLOCK]
		[(int)(x + PLAYER_SIZ) / BLOCK] == 'D')
		return (1);
	if (map[(int)(y + PLAYER_SIZ) / BLOCK]
		[(int)(x - PLAYER_SIZ) / BLOCK] == 'D')
		return (1);
	return (0);
}

/*return 0 if not door
return 1 if door is closed
return 2 if door is open*/
int	is_door_forward(char **map, t_player player)
{
	float	x;
	float	y;
	int		i;

	i = 0;
	while (i < MARGIN_DOOR)
	{
		x = player.x + cos(player.angle) * SPEED * i;
		y = player.y + sin(player.angle) * SPEED * i;
		if (is_door_open(map, x, y))
			return (2);
		if (is_door_closed(map, x, y))
			return (1);
		i++;
	}
	return (0);
}

void	init_door(t_cub *cub)
{
	t_img	*img;

	img = &cub->door;
	img->data = mlx_xpm_file_to_image(cub->mlx,
			"./textures/door2.xpm", &img->width, &img->height);
	if (!img->data)
		exit_error(cub, "Failed XPM to image");
	img->addr = mlx_get_data_addr(img->data, &img->bpp, &img->size_line,
			&img->endian);
	if (!img->addr)
		exit_error(cub, "Failed get address from texture img");
}
