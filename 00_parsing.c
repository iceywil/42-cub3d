/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 02:15:48 by a                 #+#    #+#             */
/*   Updated: 2025/02/12 10:27:24 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
			parse_element(cub, line);
		else
			save_map(cub, file, line);
		free(line);
		line = get_next_line(fd);
	}
	cub->map[cub->map_height] = NULL;
	close(fd);
	check_elements(cub);
}
void	set_element(t_cub *cub, char *line, char *tmp)
{
	if (!ft_strncmp(line, "NO ", 3))
		cub->no = tmp;
	else if (!ft_strncmp(line, "SO ", 3))
		cub->so = tmp;
	else if (!ft_strncmp(line, "EA ", 3))
		cub->ea = tmp;
	else if (!ft_strncmp(line, "WE ", 3))
		cub->we = tmp;
	else if (!ft_strncmp(line, "F ", 2))
		cub->f = tmp;
	else if (!ft_strncmp(line, "C ", 2))
		cub->c = tmp;
}

void	parse_element(t_cub *cub, char *line)
{
	char	*tmp;

	if (line_is_empty(cub, line))
		return ;
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "EA ", 3) || !ft_strncmp(line, "WE ", 3))
		tmp = ft_strdup(line + 3);
	else if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
		tmp = ft_strdup(line + 2);
	else
		exit_error(cub, "Error: invalid element");
	if (!tmp)
		exit_error(cub, "Error : malloc failed");
	tmp[ft_strlen(tmp) - 1] = 0;
	set_element(cub, line, tmp);
}

void	check_elements(t_cub *cub)
{
	if (!cub->no || !cub->so || !cub->we || !cub->ea || !cub->f || !cub->c)
		exit_error(cub, "Error: invalid element");
	if (!cub->map)
		exit_error(cub, "Error: No map in the file");
	handle_colors(cub);
	handle_map(cub);
	print_cub(cub);
	ft_printf("check elements: SUCCESS\n");
	printf("player_direction(%f, %f); player_position(%i, %i);\n", cub->dir_x, cub->dir_y, cub->pos_x, cub->pos_y);
}

void	handle_colors(t_cub *cub)
{
	char	**tmp;

	tmp = ft_split(cub->f, ',');
	if (!tmp)
		exit_error(cub, "Error: malloc failed");
	if (!(tmp[0] && tmp[1] && tmp[2]) || tmp[3])
		exit_error(cub, "Error: invalid element");
	cub->floor.r = ft_atoi(tmp[0]);
	cub->floor.g = ft_atoi(tmp[1]);
	cub->floor.b = ft_atoi(tmp[2]);
	ft_free_double_tab(&tmp);
	tmp = ft_split(cub->c, ',');
	if (!tmp)
		exit_error(cub, "Error: malloc failed");
	if (!(tmp[0] && tmp[1] && tmp[2]) || tmp[3])
		exit_error(cub, "Error: invalid element");
	cub->ceiling.r = ft_atoi(tmp[0]);
	cub->ceiling.g = ft_atoi(tmp[1]);
	cub->ceiling.b = ft_atoi(tmp[2]);
	ft_free_double_tab(&tmp);
	if (cub->floor.r < 0 || cub->floor.r > 255 || cub->floor.g < 0 || cub->floor.g > 255
		|| cub->floor.b < 0 || cub->floor.b > 255 || cub->ceiling.r < 0 || cub->ceiling.r > 255
		|| cub->ceiling.g < 0 || cub->ceiling.g > 255 || cub->ceiling.b < 0 || cub->ceiling.b > 255)
		exit_error(cub, "Error: invalid element");
}
