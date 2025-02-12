/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_check_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:02:57 by kimnguye          #+#    #+#             */
/*   Updated: 2025/02/12 14:08:28 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_arg(int argc, char **argv)
{
	int		n;
	
	if (argc != 2)
	{
		ft_putstr_fd("Error: incorrect number of arguments\n", 2);
		exit (1);
	}
	n = ft_strlen(argv[1]);
	if (ft_strncmp(".cub", &argv[1][n - 4], 4))
	{
		ft_putstr_fd("Wrong file format: a .cub is expected!\n", 2);
		exit (1);
	}
}