/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 01:49:52 by a                 #+#    #+#             */
/*   Updated: 2025/02/07 17:23:30 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_cub	cub;
	int		n;

	init_all(&cub);
	if (argc != 2)
		exit_error(&cub, "Error: incorrect number of arguments\n");
	n = ft_strlen(argv[1]);
	if (ft_strncmp(".cub", &argv[1][n - 4], 4))
		return (ft_printf("Wrong file format: a .cub is expected!\n"), 1);
	parsing(&cub, argv[1]);
	ft_init_mlx(&cub);
	get_textures(&cub);
	ft_draw_map(&cub);
	mlx_put_image_to_window(&cub.mlx, &cub.win, &cub.mini_carte.mlx, 0, HEIGHT
		/ 5 * 4);
	mlx_hook(&cub.win, KEYPRESS_EVENT, 1L << 0, key_hook, &cub);
	mlx_hook(&cub.win, BUTTONPRESS_EVENT, 1L << 2, mouse_hook, &cub);
	mlx_hook(&cub.win, 17, 1L << 17, ft_close_all, &cub);
	mlx_loop(&cub.mlx);
	return (0);
}

void	get_textures(t_cub *cub)
{
	int	x;
	int	y;

	cub->text_n = mlx_xpm_file_to_image(cub->mlx, cub->no, &x, &y);
	cub->text_s = mlx_xpm_file_to_image(cub->mlx, cub->no, &x, &y);
	cub->text_w = mlx_xpm_file_to_image(cub->mlx, cub->no, &x, &y);
	cub->text_e = mlx_xpm_file_to_image(cub->mlx, cub->no, &x, &y);
	if (!cub->text_n || !cub->text_s || !cub->text_w || !cub->text_e)
		exit_error(cub, "Error : Can't open texture");
}
