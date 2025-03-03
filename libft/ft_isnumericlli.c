/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumericlli.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 16:58:33 by kimnguye          #+#    #+#             */
/*   Updated: 2025/02/27 11:15:16 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		islli(const char *str);
int		isnumeric(const char *str);
int		isnumericlli(const char *str);

typedef struct s_lli{
	char	*min_lli;
	char	*max_lli;
}	t_lli;

int	islli(const char *str)
{
	t_lli	lli;

	lli.min_lli = "-9223372036854775808";
	lli.max_lli = "9223372036854775807";
	if (ft_strlen(str) > ft_strlen(lli.min_lli))
		return (0);
	if (ft_strlen(str) == ft_strlen(lli.min_lli))
	{
		if (*str != '-' && *str != '+')
			return (0);
		if (*str == '+')
			return (islli(str + 1));
		while (*(++str) && *(++lli.min_lli))
			if (*str > *lli.min_lli)
				return (0);
	}
	else if (ft_strlen(str) == ft_strlen(lli.max_lli))
		while (*str)
			if (*str++ > *lli.max_lli++)
				return (0);
	return (1);
}

int	isnumeric(const char *str)
{
	if (!*str)
		return (0);
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (!islli(str))
		return (0);
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	isnumericlli(const char *str)
{
	if (!isnumeric(str))
		return (0);
	if (!islli(str))
		return (0);
	return (1);
}
