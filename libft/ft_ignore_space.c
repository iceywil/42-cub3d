/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ignore_space.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:19:00 by kimnguye          #+#    #+#             */
/*   Updated: 2025/03/03 15:34:43 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_ignore_spaces(char *str)
{
	int		i;
	char	*new;

	i = ft_strlen(str) - 2;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i--;
	str[i + 1] = '\0';
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	new = ft_strdup(&str[i]);
	free(str);
	if (!new)
		return (NULL);
	return (new);
}