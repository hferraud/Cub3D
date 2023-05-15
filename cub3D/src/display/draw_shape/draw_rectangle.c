/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rectangle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:52:00 by ethan             #+#    #+#             */
/*   Updated: 2023/03/14 12:52:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "draw.h"

static void	draw_vertical_line(t_img_data *img_data, char *dst,
				int height, int color);

/**
 * @brief Draw a rectangle of the color given in parameter
 * @param rectangle The param of the rectangle
 */
void	draw_rectangle(t_img_data *img_data, t_rectangle rectangle)
{
	int		column;
	int		height;
	char	*dst;

	column = rectangle.start.x;
	dst = img_data->addr + (rectangle.start.y * img_data->line_length
			+ (rectangle.start.x) * (img_data->bit_ratio));
	height = rectangle.end.y - rectangle.start.y + 1;
	while (column <= rectangle.end.x)
	{
		draw_vertical_line(img_data, dst, height, rectangle.color);
		dst += img_data->bit_ratio;
		column++;
	}
}

static void	draw_vertical_line(t_img_data *img_data, char *dst,
				int height, int color)
{
	while (height > 0)
	{
		*(unsigned int *)dst = color;
		dst += img_data->line_length;
		height--;
	}
}
