/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shape_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:43:00 by ethan             #+#    #+#             */
/*   Updated: 2023/03/14 12:43:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "draw.h"

int	is_valid_pixel(t_vector point)
{
	return (point.x >= 0 && point.x < WIN_WIDTH
		&& point.y >= 0 && point.y < WIN_HEIGHT);
}

t_rectangle	set_rectangle(t_vector start, t_vector end, int color)
{
	t_rectangle	rectangle;

	rectangle.start = start;
	rectangle.end = end;
	rectangle.color = color;
	return (rectangle);
}

t_rectangle	set_square(t_vector start, int width, int color)
{
	t_rectangle	square;

	square.start = start;
	square.end = vector_init(start.x + width, start.y + width);
	square.color = color;
	return (square);
}
