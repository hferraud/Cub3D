/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 03:12:00 by ethan             #+#    #+#             */
/*   Updated: 2023/03/17 03:12:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "draw.h"
#include "raycasting.h"

void	draw_wall(t_cub *cub, int x, t_ray ray)
{
	float		dist;
	int			draw_start;
	int			draw_end;
    int         line_height;
	int			color;

	dist = ray.ray_length;
	line_height = WIN_HEIGHT / dist;
	draw_start = -line_height / 2 + WIN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + WIN_HEIGHT / 2;
	if (draw_end >= WIN_HEIGHT)
		draw_end = WIN_HEIGHT - 1;
	if (ray.wall_face == 'N')
		color = 0xFF;
	else if (ray.wall_face == 'E')
		color = 0xCC;
	else if (ray.wall_face == 'S')
		color = 0xAA;
	else
		color = 0x77;
	draw_rectangle(&cub->mlx_data->img_data, set_rectangle(set_point(x, draw_start), set_point(x, draw_end), color));
}