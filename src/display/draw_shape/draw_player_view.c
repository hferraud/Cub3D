/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player_view.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 04:55:00 by hferraud          #+#    #+#             */
/*   Updated: 2023/03/17 04:55:00 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "draw.h"
#include "raycasting.h"

/**
 * @brief Draws the player's vision on an image of the mlx
 */
void	draw_player_view(t_cub *cub, float fov)
{
	const float		step = (2 * tanf(fov / 2)) / (WIN_WIDTH + 1);
	float			yaw;
	float			theta;
	int				x;

	x = 0;
	yaw = cub->player->rotation;
	while (x < WIN_WIDTH / 2)
	{
		theta = yaw - atanf(step * (WIN_WIDTH / 2 - x));
		draw_wall(cub, x, ray_cast(cub, theta));
		x++;
	}
	draw_wall(cub, x, ray_cast(cub, yaw));
	x++;
	while (x < WIN_WIDTH)
	{
		theta = yaw + atanf(step * (x - WIN_WIDTH / 2));
		draw_wall(cub, x, ray_cast(cub, theta));
		x++;
	}
}
