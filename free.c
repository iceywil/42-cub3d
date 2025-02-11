/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 01:33:34 by a                 #+#    #+#             */
/*   Updated: 2025/02/11 11:51:56 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_map(char **map, int n)
{
	int	i;

	i = 0;
	while (i < n)
		free(map[i++]);
	free(map);
}

void	free_mlx(t_cub *cub)
{
	mlx_destroy_image(cub->mlx, cub->img.mlx);
	mlx_destroy_image(cub->mlx, cub->mini_carte.mlx);
	mlx_destroy_image(cub->mlx, cub->text_n);
	mlx_destroy_image(cub->mlx, cub->text_s);
	mlx_destroy_image(cub->mlx, cub->text_w);
	mlx_destroy_image(cub->mlx, cub->text_e);
	mlx_destroy_window(cub->mlx, cub->win);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
}

void	free_cub(t_cub *cub)
{
	if (cub->no)
		free(cub->no);
	if (cub->so)
		free(cub->so);
	if (cub->we)
		free(cub->we);
	if (cub->ea)
		free(cub->ea);
	if (cub->f)
		free(cub->f);
	if (cub->c)
		free(cub->c);
	if (cub->map)
		ft_free_map(cub->map, cub->map_height);
}

/*closes the program and free everything*/
int	ft_close_all(t_cub *cub)
{
	free_cub(cub);
	free_mlx(cub);
	exit(EXIT_SUCCESS);
	return (0);
}

void	exit_error(t_cub *cub, char *str)
{
	ft_putstr_fd(str, 2);
	free_cub(cub);
	exit(1);
}
