/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 02:15:48 by a                 #+#    #+#             */
/*   Updated: 2025/02/03 21:01:04 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* A valid map / config file obeys the following rules:

The map must be composed of only 6 possible characters: 0 for an empty space,
1 for a wall, and N,S,E or W for the player’s start position and spawning
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
	while ((line = get_next_line(fd)))
	{
		if (!cub->no || !cub->so || !cub->we || !cub->ea || !cub->f || !cub->c)
			handle_element(cub, line);
		else
		{
			if (!cub->map)
				ft_init_map(cub, file);
			cub->i = 0;
			while (is_space(line[cub->i]))
				cub->i++;
			//si cest une ligne vide et que la carte existe: erreur (on naccepte pas les sauts de ligne)
			if (!line[cub->i]  && cub->map[0])
				exit_error(cub, "Error: invalid map");
			//si cest une ligne de la carte : lajouter
			else if (line[cub->i])
				add_map_line(cub, line);
			//ligne vide et carte n'existe pas: ne rien faire
		}
		free(line);
	}
	check_elements(cub);
}

void	handle_element(t_cub *cub, char *line)
{
	cub->n++;
	if (!ft_strncmp(line, "NO ", 3))
		cub->no = ft_strdup(line + 3);
	else if (!ft_strncmp(line, "SO ", 3))
		cub->so = ft_strdup(line + 3);
	else if (!ft_strncmp(line, "EA ", 3))
		cub->ea = ft_strdup(line + 3);
	else if (!ft_strncmp(line, "WE ", 3))
		cub->we = ft_strdup(line + 3);
	else if (!ft_strncmp(line, "F ", 2))
	{
		cub->f = ft_strdup(line + 2);
		if (!cub->f)
			exit_error(cub, "Error: malloc failed");
	}
	else if (!ft_strncmp(line, "C ", 2))
	{
		cub->c = ft_strdup(line + 2);
		if (!cub->c)
			exit_error(cub, "Error: malloc failed");
	}
	else
		exit_error(cub, "Error: invalid map");
}

void	check_elements(t_cub *cub)
{
	if (!cub->no || !cub->so || !cub->we || !cub->ea || !cub->f || !cub->c)
		exit_error(cub, "Error: invalid element");
	handle_colors(cub);
	handle_map(cub);
	//print_cub(cub);
	//replace the ' ' by 1 in the map (arbitrarly)
	printf("check elements: SUCCESS\n");
}

void	handle_colors(t_cub *cub)
{
	char	**tmp;

	tmp = ft_split(cub->f, ',');
	if (!tmp)
		exit_error(cub, "Error: malloc failed");
	if (!(tmp[0] && tmp[1] && tmp[2]) || tmp[3])
		exit_error(cub, "Error: invalid element");
	cub->f_r = ft_atoi(tmp[0]);
	cub->f_g = ft_atoi(tmp[1]);
	cub->f_b = ft_atoi(tmp[2]);
	ft_free_double_tab(&tmp);
	tmp = ft_split(cub->c, ',');
	if (!tmp)
		exit_error(cub, "Error: malloc failed");
	if (!(tmp[0] && tmp[1] && tmp[2]) || tmp[3])
		exit_error(cub, "Error: invalid element");
	cub->c_r = ft_atoi(tmp[0]);
	cub->c_g = ft_atoi(tmp[1]);
	cub->c_b = ft_atoi(tmp[2]);
	ft_free_double_tab(&tmp);
	if (cub->f_r < 0 || cub->f_r > 255 || cub->f_g < 0 || cub->f_g > 255
		|| cub->f_b < 0 || cub->f_b > 255 || cub->c_r < 0 || cub->c_r > 255
		|| cub->c_g < 0 || cub->c_g > 255 || cub->c_b < 0 || cub->c_b > 255)
		exit_error(cub, "Error: invalid element");
}
