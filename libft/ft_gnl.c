/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:36:40 by wscherre          #+#    #+#             */
/*   Updated: 2025/01/30 20:57:47 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat_custom(char *fourre_merde, char *buff, int res)
{
	int		i;
	int		isrc;
	char	*newstatik;

	i = 0;
	isrc = 0;
	while (fourre_merde[i])
		i++;
	newstatik = malloc((i + res + 1) * sizeof(char));
	if (!newstatik)
		return (NULL);
	i = 0;
	while (fourre_merde[i])
	{
		newstatik[i] = fourre_merde[i];
		i++;
	}
	while (buff[isrc])
		newstatik[i++] = buff[isrc++];
	newstatik[i] = '\0';
	free(fourre_merde);
	return (newstatik);
}

int	ft_readline(int fd, char **fourre_merde)
{
	char	*buff;
	int		result;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (-1);
	result = read(fd, buff, BUFFER_SIZE);
	if (result > 0)
	{
		buff[result] = '\0';
		*fourre_merde = ft_strcat_custom(*fourre_merde, buff, result);
		if (!(*fourre_merde))
			return (free(buff), -1);
	}
	if (result < 0 || *fourre_merde[0] == '\0')
		result = -1;
	free(buff);
	return (result);
}

char	*ft_fill_line(int fd, char **fourre_merde)
{
	int	result;
	int	i;

	while (1)
	{
		i = 0;
		while ((*fourre_merde)[i])
		{
			if ((*fourre_merde)[i] == '\n')
				return (ft_removelinefromstatic(fourre_merde));
			i++;
		}
		result = ft_readline(fd, fourre_merde);
		if (result < 0)
			return (NULL);
		if (result == 0)
			break ;
	}
	return (ft_removelinefromstatic(fourre_merde));
}

char	*ft_removelinefromstatic(char **fourre_merde)
{
	char	*statik;
	int		i;
	int		x;
	char	*res;
	int		z;

	statik = *fourre_merde;
	i = 0;
	while (statik[i] && statik[i] != '\n')
		i++;
	if (statik[i] == '\n')
		i++;
	res = malloc(i + 1);
	if (res == NULL)
		return (NULL);
	ft_memcpy(res, statik, i);
	res[i] = '\0';
	x = 0;
	z = i;
	while (statik[z++])
		x++;
	ft_memmove(statik, statik + i, x);
	statik[x] = '\0';
	*fourre_merde = statik;
	return (res);
}

char	*get_next_line(int fd)
{
	static char	statik[4095][BUFFER_SIZE + 1];
	char		*fourre_merde;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	fourre_merde = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!fourre_merde)
		return (NULL);
	ft_memcpy(fourre_merde, statik[fd], ft_strlen(statik[fd]));
	fourre_merde[ft_strlen(statik[fd])] = '\0';
	if (!statik[fd][0])
		fourre_merde[0] = '\0';
	line = ft_fill_line(fd, &fourre_merde);
	if (!line)
	{
		if (fourre_merde)
			(free(fourre_merde), fourre_merde = NULL);
		return (NULL);
	}
	ft_memcpy(statik[fd], fourre_merde, ft_strlen(fourre_merde));
	statik[fd][ft_strlen(fourre_merde)] = '\0';
	(free(fourre_merde), fourre_merde = NULL);
	return (line);
}

/* #include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*str;
	char	*line;
	int		i;
	int		fd1;
	int		fd2;
	int		fd3;

	fd = open("../aa.txt", O_RDONLY);
	while ((str = get_next_line(fd)))
	{
		printf("gnl : '%s'", str);
		free(str);
	}
	free(str);
} */
/* #include <fcntl.h>
#include <stdio.h>
int	main(void)
{
	fd1 = open("test/test.txt", O_RDONLY);
	fd2 = open("test/text.txt", O_RDONLY);
	fd3 = open("tests/bible.txt", O_RDONLY);
	i = 1;
	while (i < 100183)
	{
		line = get_next_line(fd1);
		printf("line %d :%s", i, line);
		free(line);
		line = get_next_line(fd2);
		printf("line %d :%s", i, line);
		free(line);
		line = get_next_line(fd3);
		printf("line %d :%s", i, line);
		free(line);
		i++;
	}
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}
 */
