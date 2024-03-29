/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_put_pixel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:35:00 by ethan             #+#    #+#             */
/*   Updated: 2023/03/14 12:35:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "draw.h"

void	mlx_put_pixel(t_img_data *img_data, int x, int y, int color)
{
	char	*dst;

	dst = img_data->addr
		+ y * img_data->line_length
		+ x * (img_data->bit_ratio);
	*(int *)dst = color;
}

void	mlx_put_point(t_img_data *img_data, t_vector point, int color)
{
	mlx_put_pixel(img_data, point.x, point.y, color);
}
