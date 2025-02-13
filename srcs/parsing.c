/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 02:15:48 by a                 #+#    #+#             */
/*   Updated: 2025/02/11 19:25:42 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*si ligne vide et que la carte existe:
erreur (on naccepte pas les sauts de ligne)
si ligne vide et carte n'existe pas: ne rien faire*/

/* A valid map / config file obeys the following rules:
The map must be composed of only 6 possible characters: 0 for an empty space,
1 for a wall, and N,S,E or W for the player's start position and spawning
orientation.
The map must be closed/surrounded by walls
Except for the map content,
	each type of element can be separated by one or more empty line(s).
Except for the map content which always has to be the last,
	each type of element can be set in any order in the file.
Except for the map, each type of information from an element can be separated
by one or more	space(s).
The map must be parsed as it looks in the file. Spaces are a valid part of the
map and are up to you to handle. You must be able to parse any kind of map,
as long as it respects the rules of the map.
 */

void	parsing(t_cub *cub, char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		exit_error(cub, "Error: can't open file");
	line = get_next_line(fd);
	while (line)
	{
		if (!cub->no || !cub->so || !cub->we || !cub->ea || !cub->f || !cub->c)
			handle_element(cub, line);
		else
			save_map(cub, file, line);
		free(line);
		line = get_next_line(fd);
	}
	cub->map[cub->map_height] = NULL;
	close(fd);
	check_elements(cub);
}

void	handle_element(t_cub *cub, char *line)
{
	char	*tmp;

	if (line_is_empty(cub, line))
		return ;
	if (ft_strncmp(line, "NO ", 3) && ft_strncmp(line, "SO ", 3)
		&& ft_strncmp(line, "WE ", 3) && ft_strncmp(line, "EA ", 3)
		&& ft_strncmp(line, "F ", 2) && ft_strncmp(line, "C ", 2))
		exit_error(cub, "Invalid element");
	if (!ft_strncmp(line, "NO ", 3) && !cub->texture_n)
		handle_texture(cub, cub->texture_n, line);
	else if (!ft_strncmp(line, "SO ", 3) && !cub->texture_s)
		handle_texture(cub, cub->texture_s, line);
	else if (!ft_strncmp(line, "WE ", 3) && !cub->texture_w)
		handle_texture(cub, cub->texture_w, line);
	else if (!ft_strncmp(line, "EA ", 3) && !cub->texture_e)
		handle_texture(cub, cub->texture_e, line);
	else
		exit_error(cub, "Duplicate texture");
	if (!ft_strncmp(line, "F ", 2) && !cub->f_rgb)
		handle_colors(cub, &cub->f_rgb, line);
	else if (!ft_strncmp(line, "C ", 2) && !cub->c_rgb)
		handle_colors(cub, &cub->c_rgb, line);
	else
		exit_error(cub, "Duplicate color");
}

void	handle_texture(t_cub *cub, t_img *img, char *line)
{
	if (ft_strncmp(line + ft_strlen(line) - 5, ".xpm", 4))
		exit_error(cub, "Not .xpm extension file");
	line[ft_strlen(line) - 1] = '\0';
	img->data = mlx_xpm_file_to_image(cub->mlx, line + 3, &img->width,
			&img->height);
	if (!img->data)
		exit_error(cub, "Failed XPM to image");
	img->addr = mlx_get_data_addr(img->data, &img->bpp, &img->size_line,
			&img->endian);
	if (!img->addr)
		exit_error(cub, "Failed get address from texture img");
}

void	check_elements(t_cub *cub)
{
	if (!cub->no || !cub->so || !cub->we || !cub->ea)
		exit_error(cub, "Missing texture");
	if (!cub->f || !cub->c)
		exit_error(cub, "Missing color");
	if (!cub->map)
		exit_error(cub, "No map in the file");
	handle_map(cub);
	print_cub(cub);
	ft_printf("check elements: SUCCESS\n");
}

void	handle_colors(t_cub *cub, int *rgb, char *line)
{
	char	**tmp;

	tmp = ft_split(cub->f, ',');
	if (!tmp)
		exit_error(cub, "Malloc failed");
	if (!(tmp[0] && tmp[1] && tmp[2]) || tmp[3])
		exit_error(cub, "Needs exactly 3 rgb colors");
	*rgb = rgb_to_int(ft_atoi(tmp[0]), ft_atoi(tmp[1]), ft_atoi(tmp[2]));
	ft_free_double_tab(&tmp);
	if (*rgb == -1)
		exit_error(cub, "Wrong color");
}
