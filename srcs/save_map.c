/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 19:22:52 by kimnguye          #+#    #+#             */
/*   Updated: 2025/03/06 18:57:12 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*retrieve the dimension of the map cub->map_height
returns 0 when success, returns -1 if gnl failed*/
void	init_max(t_cub *cub, int fd, int n)
{
	char	*gnl;

	cub->map_height = 0;
	gnl = get_next_line(fd);
	if (gnl == NULL)
		exit_error(cub, "GNL failed, Map initialization failed");
	while (--n > 0)
	{
		free(gnl);
		gnl = get_next_line(fd);
	}
	while (gnl)
	{
		cub->map_height++;
		free(gnl);
		gnl = get_next_line(fd);
	}
	free(gnl);
	close(fd);
}

/*map is a mallocated (char **)*/
void	add_map_line(t_cub *cub, char *line)
{
	int	n;

	n = ft_strlen(line) - 1;
	cub->map[cub->map_height] = ft_strdup(line);
	if (!cub->map[cub->map_height])
		exit_error(cub, "Strdup failed");
	if (cub->map[cub->map_height][n] == '\n')
		cub->map[cub->map_height][n] = '\0';
	cub->map_height++;
	cub->map[cub->map_height] = NULL;
}

/*returns a mallocated map
close the program on errors*/
void	init_map(t_cub *cub, char *file, int n)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit_error(cub, "Can't open file");
	init_max(cub, fd, n);
	cub->map = malloc(sizeof(char *) * (cub->map_height + 1));
	cub->map_width = malloc(sizeof(int) * (cub->map_height + 1));
	if (!cub->map)
		exit_error(cub, "Map initialization failed");
	cub->map_height = 0;
	cub->map[0] = NULL;
}

/*read the file and save the map line by line into cub->map*/
void	save_map(t_cub *cub, char *file, char *line, int n)
{
	int	i;

	if (!cub->map)
		init_map(cub, file, n);
	i = 0;
	while (is_space(line[i]))
		i++;
	if (!line[i] && cub->map[0])
		exit_error(cub, "Invalid map");
	else if (line[i])
		add_map_line(cub, line);
}
