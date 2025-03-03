/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 02:15:48 by a                 #+#    #+#             */
/*   Updated: 2025/03/03 15:52:31 by kimnguye         ###   ########.fr       */
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
	int		n;

	n = 0;
	cub->fd = open(file, O_RDONLY);
	if (cub->fd == -1)
		exit_error(cub, "Can't open file");
	cub->line = get_next_line(cub->fd);
	while (cub->line)
	{
		n++;
		if (!cub->texture_n.data || !cub->texture_s.data || !cub->texture_w.data
			|| !cub->texture_e.data || cub->floor.r == -1
			|| cub->ceiling.r == -1)
		{
			cub->line = ft_ignore_spaces(cub->line);
			handle_element(cub, cub->line);
		}
		else
			save_map(cub, file, cub->line, n);
		free(cub->line);
		cub->line = get_next_line(cub->fd);
	}
	close(cub->fd);
	check_elements(cub);
	cub->map[cub->map_height] = NULL;
}

void	handle_element(t_cub *cub, char *line)
{
	char	*tmp;

	if (line_is_empty(cub, line))
		return ;
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
		handle_texture(cub, line);
	else if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
	{
		if (!ft_strncmp(line, "F ", 2) && cub->floor.r == -1)
			handle_colors(cub, &cub->floor, line);
		else if (!ft_strncmp(line, "C ", 2) && cub->ceiling.r == -1)
			handle_colors(cub, &cub->ceiling, line);
		else
			exit_error(cub, "Duplicate color");
	}
	else
		exit_error(cub, "Invalid element");
}

void	handle_texture(t_cub *cub, char *line)
{
	t_img	*img;

	if (!ft_strncmp(line, "NO ", 3) && !cub->texture_n.data)
		img = &cub->texture_n;
	else if (!ft_strncmp(line, "SO ", 3) && !cub->texture_s.data)
		img = &cub->texture_s;
	else if (!ft_strncmp(line, "WE ", 3) && !cub->texture_w.data)
		img = &cub->texture_w;
	else if (!ft_strncmp(line, "EA ", 3) && !cub->texture_e.data)
		img = &cub->texture_e;
	else
		exit_error(cub, "Duplicate texture");
	if (ft_strncmp(line + ft_strlen(line) - 4, ".xpm", 4))
		exit_error(cub, "Not .xpm extension file");
	while (is_space(*(line + 3)))
		line++;
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
	if (!cub->texture_w.data || !cub->texture_s.data || !cub->texture_w.data
		|| !cub->texture_e.data)
		exit_error(cub, "Missing texture");
	if (cub->floor.b == -1 || cub->ceiling.b == -1)
		exit_error(cub, "Missing color");
	if (!cub->map)
		exit_error(cub, "No map in the file");
	handle_map(cub);
}

void	handle_colors(t_cub *cub, t_color *rgb, char *line)
{
	char	**tmp;

	if (coma_ctr(line) != 2)
		exit_error(cub, "Wrong color format: expect (R,G,B) in range [0, 255]");
	tmp = ft_split(line + 2, ',');
	if (!tmp)
		exit_error(cub, "Malloc failed");
	if (!(tmp[0] && tmp[1] && tmp[2]) || tmp[3]
		|| !(isnumeric(tmp[0]) && isnumeric(tmp[1]) && isnumeric(tmp[2])))
	{
		ft_free_double_tab(&tmp);
		exit_error(cub, "Wrong color format: expect (R,G,B) in range [0, 255] (1)");
	}
	rgb->r = ft_atoi(tmp[0]);
	rgb->g = ft_atoi(tmp[1]);
	rgb->b = ft_atoi(tmp[2]);
	ft_free_double_tab(&tmp);
	if (rgb->r < 0 || rgb->r > 255 || rgb->g < 0 || rgb->g > 255 || rgb->b < 0
		|| rgb->b > 255)
		exit_error(cub, "Wrong color format: expect (R,G,B) in range [0, 255] (2)");
}
