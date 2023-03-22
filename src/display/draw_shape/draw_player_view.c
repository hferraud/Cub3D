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

void	draw_player_view(t_cub *cub, float fov)
{
	const float	step = fov / WIN_WIDTH;
	t_fvector	yaw;
	float		theta;
	float		theta_max;
	int			x;

	x = 0;
	theta = PLAYER_FOV / -2.f;
	theta_max = PLAYER_FOV / 2.f;
	while (theta < theta_max)
	{
		yaw = fvector_rotate(cub->player->rotation, theta);
		draw_wall(cub, x, ray_cast(cub, yaw));
		theta += step;
		x++;
	}
}
