/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 19:22:52 by kimnguye          #+#    #+#             */
/*   Updated: 2025/02/03 20:45:09 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	add_map_line(t_cub *cub, char *line)
{
	cub->i = 0;
	cub->map[cub->map_height] = ft_strdup(line);
	cub->map[cub->map_height][ft_strlen(line) - 1] = '\0';
	if (!cub->map[cub->map_height])
		exit_error(cub, "Error: strdup failed");
	cub->map_height++;
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
	cub->map = malloc(sizeof(char *) * cub->map_height);
	if (cub->map == NULL)
		exit_error(cub, "Error: map initialization failed");
	printf("init map: SUCCESS\n");
	cub->map_height = 0;
}

/*retrieve the dimension of the map (cub->map_width and cub->map_height)
returns 0 when success
returns -1 if gnl failed
returns -2 if the map is not rectangular*/
int	ft_init_max(int fd, t_cub *cub)
{
	char	*gnl;
	int		line_x;

	cub->map_height = 0;
	gnl = get_next_line(fd);
	if (gnl == NULL)
		return (printf(": GNL failed\n"), -1);
	while (cub->n-- > 0)
	{
		free(gnl);
		gnl = get_next_line(fd);
	}
	cub->map_width = ft_strlen(gnl) - 1;
	while (gnl)
	{
		cub->map_height++;
		line_x = ft_strlen(gnl);
		if (line_x < cub->map_width)
			return (close(fd), free(gnl),
				printf(": a rectangular map is expected!"), -2);
		free(gnl);
		gnl = get_next_line(fd);
	}
	close(fd);
	return (printf("init max: SUCCESS\n"), 0);
}
