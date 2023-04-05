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

int	is_valid_point(t_point point)
{
	return (point.x >= 0 && point.x < WIN_WIDTH
		&& point.y >= 0 && point.y < WIN_HEIGHT);
}

t_point	set_point(int x, int y)
{
	t_point	point;

	point.x = x;
	point.y = y;
	return (point);
}

t_rectangle	set_rectangle(t_point start, t_point end, int color)
{
	t_rectangle	rectangle;

	rectangle.start = start;
	rectangle.end = end;
	rectangle.color = color;
	return (rectangle);
}

t_rectangle	set_square(t_point start, int width, int color)
{
	t_rectangle	square;

	square.start = start;
	square.end = set_point(start.x + width, start.y + width);
	square.color = color;
	return (square);
}
