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
	float	yaw;
	float	theta;
	int		x;
	t_ray	ray;

	yaw = cub->player->rotation;
	x = 0;
	theta = yaw - fov / 2;
	while (theta < yaw + fov / 2)
	{
		ray = ray_cast(cub, theta);
		draw_wall(cub, x, ray);
		theta += fov / WIN_WIDTH;
		x++;
	}
}
