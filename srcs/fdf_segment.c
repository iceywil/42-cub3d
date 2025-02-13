/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_segment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:04:05 by kimnguye          #+#    #+#             */
/*   Updated: 2025/02/13 19:47:34 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*trace the segment between two given points a(x1, y1) and b(x2,y2) */
void	segment(t_cub *cub, int x_a, int y_a, int x_b, int y_b)
{
	t_slope	*ab;

	ab = malloc(sizeof(t_slope));
	ab->dx = (x_b - x_a);
	ab->dy = (y_b - y_a);
	ab->i = x_a;
	ab->j = y_a;
	ab->p = 0;
	ab->x_a = x_a;
	ab->x_b = x_b;
	ab->y_a = y_a;
	ab->y_b = y_b;
	if (ab->dx == 0)
		segment_vertical(cub, ab);
	else if (ab->dy >= 0 && ab->dx > 0)
		segment_q1(cub, ab);
	else if (ab->dy >= 0 && ab->dx < 0)
		segment_q2(cub, ab);
	else if (ab->dy < 0 && ab->dx < 0)
		segment_q3(cub, ab);
	else if (ab->dy < 0 && ab->dx > 0)
		segment_q4(cub, ab);
	free(ab);
}