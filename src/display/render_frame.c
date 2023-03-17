/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 11:22:00 by edelage           #+#    #+#             */
/*   Updated: 2023/03/14 11:22:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "hook.h"
#include "draw.h"
#include "raycasting.h"

static void clear_frame(t_cub *cub);

int	render_frame(t_cub *cub)
{
	player_update(cub);
    clear_frame(cub);
	draw_background(cub);
	draw_player_view(cub, PLAYER_FOV);
	mlx_put_image_to_window(cub->mlx_data->mlx_ptr, cub->mlx_data->win_ptr,
		cub->mlx_data->img_data.img, 0, 0);
	return (0);
}

static void clear_frame(t_cub *cub)
{
    t_rectangle screen;

    screen.start = set_point(0,0);
    screen.end = set_point(WIN_WIDTH - 1,WIN_HEIGHT - 1);
    screen.color = 0x0;
    draw_rectangle(&cub->mlx_data->img_data, screen);
}