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

	printf("rot: %f %f\n", cub->player->rotation.x, cub->player->rotation.y);
	yaw = cub->player->rotation;
	printf("yaw before: %f %f\n", yaw.x, yaw.y);
	yaw = fvector_rotate(cub->player->rotation, theta);
	printf("yaw after: %f %f\n", yaw.x, yaw.y);

	theta = 1000;
	while (theta < theta_max)
	{
		yaw = fvector_rotate(cub->player->rotation, theta);
		printf("yaw: %f %f\n", yaw.x, yaw.y);
		draw_wall(cub, x, ray_cast(cub, yaw));
		theta += step;
		x++;
	}
	exit(0);
}
