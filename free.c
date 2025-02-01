/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 01:33:34 by a                 #+#    #+#             */
/*   Updated: 2025/01/28 18:43:47 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
}

void	exit_error(t_cub *cub, char *str)
{
	ft_putstr_fd(str, 2);
	free_cub(cub);
	exit(1);
}
