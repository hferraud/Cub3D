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
	draw_rectangle(&cub->mlx_data->img_data, set_rectangle(set_point(0, 0), set_point(WIN_WIDTH - 1, WIN_HEIGHT / 2), 0x2BFAFA));
	draw_rectangle(&cub->mlx_data->img_data, set_rectangle(set_point(0, WIN_HEIGHT / 2 + 1), set_point(WIN_WIDTH - 1, WIN_HEIGHT - 1), 0x00909090));
}
