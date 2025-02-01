/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 02:15:48 by a                 #+#    #+#             */
/*   Updated: 2025/01/30 23:50:52 by a                ###   ########.fr       */
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
			cub->i = 0;
			while (is_space(line[cub->i]))
				cub->i++;
			if (!line[cub->i] && cub->map)
				exit_error(cub, "Error: invalid map");
			add_map_line(cub, line);
		}
		free(line);
	}
	check_elements(cub);
}

void	add_map_line(t_cub *cub, char *line)
{
	char	**tmp;

	cub->i = 0;
	if (cub->map)
	{
		tmp = malloc(sizeof(char *) * (cub->map_height + 2));
		if (!tmp)
			exit_error(cub, "Error: malloc failed");
		while (cub->map[cub->i])
			tmp[cub->i] = cub->map[cub->i++];
		free(cub->map);
		cub->map = tmp;
	}
	else
		cub->map = malloc(sizeof(char *) * 2);
	if (!cub->map)
		exit_error(cub, "Error: malloc failed");
	cub->map[cub->i + 1] = NULL;
	cub->map[cub->i] = ft_strdup(line);
	if (!cub->map[cub->i])
		(ft_free_double_tab(&tmp), exit_error(cub, "Error: malloc failed"));
	cub->map_height++;
}

void	handle_element(t_cub *cub, char *line)
{
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
	ft_printf("%s\n", cub->no);
	ft_printf("%s\n", cub->so);
	ft_printf("%s\n", cub->we);
	ft_printf("%s\n", cub->ea);
	ft_printf("%d\n", cub->f_r);
	ft_printf("%d\n", cub->f_g);
	ft_printf("%d\n", cub->f_b);
	ft_printf("%d\n", cub->c_r);
	ft_printf("%d\n", cub->c_g);
	ft_printf("%d\n", cub->c_b);
	cub->i = 0;
	while (cub->map[cub->i])
	{
		ft_printf("%s\n", cub->map[cub->i]);
		cub->i++;
	}
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

void	handle_map(t_cub *cub)
{
	cub->i = 0;
	cub->x = 0;
	while (cub->map[cub->i])
	{
		while (cub->map[cub->i][cub->x])
		{
			if ((cub->i == 0 || cub->i == cub->map_height)
				&& (cub->map[cub->i][cub->x] != ' '
					|| cub->map[cub->i][cub->x] != '1'))
				exit_error(cub, "Error: invalid map");
			if ((cub->x == 0 || cub->x == cub->map_width)
				&& (cub->map[cub->i][cub->x] != ' '
					|| cub->map[cub->i][cub->x] != '1'))
				exit_error(cub, "Error: invalid map");
			if (cub->i != 0 && cub->i != cub->map_height && cub->x != 0
				&& cub->x != cub->map_width)
			{
				
			}
			cub->x++;
		}
		cub->i++;
	}
}
