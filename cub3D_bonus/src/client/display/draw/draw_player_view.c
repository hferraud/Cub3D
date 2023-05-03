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
	t_ray		ray;
	t_fvector	ray_dir;
	float		z_buffer[WIN_WIDTH];
	int			screen_x;
	float		camera_x;

	(void) fov;
	screen_x = 0;
	while (screen_x < WIN_WIDTH)
	{
		camera_x = 2.f * screen_x / (float) WIN_WIDTH - 1;
		ray_dir = fvector_add(cub->player.rotation,
				fvector_mul(cub->player.camera, camera_x));
		ray = ray_cast(cub, ray_dir);
		z_buffer[screen_x] = ray.length;
		draw_wall(cub, screen_x, ray);
		draw_collectible(cub);
		screen_x++;
	}
	(void)z_buffer;
}
