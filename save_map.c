/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 19:22:52 by kimnguye          #+#    #+#             */
/*   Updated: 2025/02/04 17:21:46 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*retrieve the dimension of the map (cub->map_width and cub->map_height)
returns 0 when success
returns -1 if gnl failed*/
int	ft_init_max(int fd, t_cub *cub)
{
	char	*gnl;
	int		line_x;

	cub->map_height = 0;
	gnl = get_next_line(fd);
	if (gnl == NULL)
		return (ft_printf(": GNL failed\n"), -1);
	while (cub->start_map_i-- > 0)
	{
		free(gnl);
		gnl = get_next_line(fd);
	}
	cub->map_width = ft_strlen(gnl) - 1;
	while (gnl)
	{
		cub->map_height++;
		line_x = ft_strlen(gnl);
		if (cub->map_width < line_x)
			cub->map_width = line_x;
		free(gnl);
		gnl = get_next_line(fd);
	}
	free(gnl);
	close(fd);
	return (ft_printf("init max: SUCCESS\n"), 0);
}

/*returns a mallocated map
close the program on errors*/
void	ft_init_map(t_cub *cub, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit_error(cub, "Error: can't open file");
	if (ft_init_max(fd, cub) < 0)
		exit_error(cub, "Error: map initialization failed");
	cub->map = malloc(sizeof(char *) * (cub->map_height + 1));
	if (!cub->map)
		exit_error(cub, "Error: map initialization failed");
	ft_printf("init map: SUCCESS\n");
	cub->map_height = 0;
}

/*map is a mallocated (char **)*/
void	add_map_line(t_cub *cub, char *line)
{
	int	n;

	n = ft_strlen(line) - 1;
	cub->map[cub->map_height] = ft_strdup(line);
	if (cub->map[cub->map_height][n] == '\n')
		cub->map[cub->map_height][n] = '\0';
	if (!cub->map[cub->map_height])
		exit_error(cub, "Error: strdup failed");
	cub->map_height++;
}
	//printf("map[%i]=%i\n", cub->map_height + 1, n);
	//printf("map[%i]=%s;\n", cub->map_height + 1, cub->map[cub->map_height]);

/*read the file and save the map line by line into cub->map*/
void	save_map(t_cub *cub, char *file, char *line)
{
	if (!cub->map)
		ft_init_map(cub, file);
	cub->i = 0;
	while (is_space(line[cub->i]))
		cub->i++;
	if (!line[cub->i] && cub->map[0])
		exit_error(cub, "Error: invalid map");
	else if (line[cub->i])
		add_map_line(cub, line);
}