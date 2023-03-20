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
	const float	step = fov / WIN_WIDTH;
	float		yaw;
	float		theta;
	float		theta_max;
	int			x;

	yaw = cub->player->rotation;
	x = 0;
	theta = yaw - fov / 2;
	theta_max = yaw + fov / 2;
	while (theta < theta_max)
	{
		draw_wall(cub, x, ray_cast(cub, theta));
		theta += step;
		x++;
	}
}
