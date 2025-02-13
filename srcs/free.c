/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 01:33:34 by a                 #+#    #+#             */
<<<<<<< HEAD:srcs/free.c
/*   Updated: 2025/02/12 20:25:22 by a                ###   ########.fr       */
=======
/*   Updated: 2025/02/12 14:13:49 by kimnguye         ###   ########.fr       */
>>>>>>> kim:free.c
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_mlx(t_cub *cub)
{
<<<<<<< HEAD:srcs/free.c
	if (cub->img->data)
		mlx_destroy_image(cub->mlx, cub->img->data);
	if (cub->mini_map->data)
		mlx_destroy_image(cub->mlx, cub->mini_map->data);
	if (cub->win)
		mlx_destroy_window(cub->mlx, cub->win);
	if (cub->mlx)
		mlx_destroy_display(cub->mlx);
	if (cub->mlx)
		free(cub->mlx);
=======
	if (cub->img.mlx)
		mlx_destroy_image(cub->mlx, cub->img.mlx);
	if (cub->mini_carte.mlx)
	mlx_destroy_image(cub->mlx, cub->mini_carte.mlx);
	if (cub->text_n)
		mlx_destroy_image(cub->mlx, cub->text_n);
	if (cub->text_s)
		mlx_destroy_image(cub->mlx, cub->text_s);
	if (cub->text_w)
		mlx_destroy_image(cub->mlx, cub->text_w);
	if (cub->text_e)
		mlx_destroy_image(cub->mlx, cub->text_e);
	mlx_destroy_window(cub->mlx, cub->win);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
>>>>>>> kim:free.c
}

void	free_cub(t_cub *cub)
{
<<<<<<< HEAD:srcs/free.c
=======
	if (cub->no)
		free(cub->no);
	if (cub->so)
		free(cub->so);
	if (cub->we)
		free(cub->we);
	if (cub->ea)
		free(cub->ea);
	if (cub->floor)
		free(cub->floor);
	if (cub->ceiling)
		free(cub->ceiling);
>>>>>>> kim:free.c
	if (cub->map)
		ft_free_double_tab(&cub->map);
}

int	close_all(t_cub *cub)
{
	free_cub(cub);
	free_mlx(cub);
	exit(EXIT_SUCCESS);
	return (0);
}

void	exit_error(t_cub *cub, char *str)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(str, 2);
	free_cub(cub);
<<<<<<< HEAD:srcs/free.c
	free_mlx(cub);
=======
	if (cub->mlx)
		free_mlx(cub);
>>>>>>> kim:free.c
	exit(1);
}
