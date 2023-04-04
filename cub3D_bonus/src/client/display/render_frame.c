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

/**
 * @brief Update player params and calculate the next image to display
 */
int	render_frame(t_cub *cub)
{
	player_update(cub);
	draw_background(cub);
	draw_player_view(cub, PLAYER_FOV);
	mlx_put_image_to_window(cub->mlx_data->mlx_ptr, cub->mlx_data->win_ptr,
		cub->mlx_data->img_data.img, 0, 0);
	return (0);
}