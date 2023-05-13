/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 02:38:00 by edelage           #+#    #+#             */
/*   Updated: 2023/03/15 02:38:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "draw.h"

void	draw_background(t_cub *cub)
{
	int			floor_color;
	int			ceiling_color;
	t_rectangle	floor;
	t_rectangle	ceiling;

	floor_color = 0x2BFAFA;
	floor = set_rectangle(
			vector_init(0, 0),
			vector_init(WIN_WIDTH - 1, WIN_HEIGHT / 2),
			floor_color);
	ceiling_color = 0x909090;
	ceiling = set_rectangle(
			vector_init(0, WIN_HEIGHT / 2 + 1),
			vector_init(WIN_WIDTH - 1, WIN_HEIGHT - 1),
			ceiling_color);
	draw_rectangle(&cub->mlx_data->img_data, floor);
	draw_rectangle(&cub->mlx_data->img_data, ceiling);
//	draw_rectangle(&cub->mlx_data->img_data, set_rectangle(set_point(0, 0), set_point(WIN_WIDTH - 1, WIN_HEIGHT / 2), 0x2BFAFA));
//	draw_rectangle(&cub->mlx_data->img_data, set_rectangle(set_point(0, WIN_HEIGHT / 2 + 1), set_point(WIN_WIDTH - 1, WIN_HEIGHT - 1), 0x909090));
}
