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
#include "hud.h"
#include "raycasting.h"

static void	*raycast_view(void *arg);

/**
 * @brief Draws the player's vision on a mlx image
 */
void	draw_player_view(t_cub *cub)
{
	const t_raycast_param	raycast_param[2] = {
	{.start = 0, .end = WIN_WIDTH / 2, .cub = cub},
	{.start = WIN_WIDTH / 2, WIN_WIDTH, .cub = cub}
	};
	pthread_t				thread;

	draw_background(cub);
	pthread_create(&thread, NULL, &raycast_view, (void *) raycast_param);
	raycast_view((void *)(raycast_param + 1));
	pthread_join(thread, NULL);
	draw_sprites(cub, cub->z_buffer);
	draw_hud(cub);
}

static void	*raycast_view(void *arg)
{
	t_ray				ray;
	t_fvector			ray_dir;
	float				camera_x;
	t_raycast_param		*raycast_param;

	raycast_param = arg;
	while (raycast_param->start < raycast_param->end)
	{
		camera_x = 2.f * (float)raycast_param->start / WIN_WIDTH - 1;
		pthread_mutex_lock(raycast_param->cub->player_data.player_lock);
		ray_dir = fvector_add(raycast_param->cub->player_data.player.rotation,
				fvector_mul(raycast_param->cub->player_data.camera, camera_x));
		pthread_mutex_unlock(raycast_param->cub->player_data.player_lock);
		pthread_mutex_lock(raycast_param->cub->map.map_lock);
		ray = ray_cast(raycast_param->cub, ray_dir);
		pthread_mutex_unlock(raycast_param->cub->map.map_lock);
		raycast_param->cub->z_buffer[raycast_param->start] = ray.length;
		draw_wall(raycast_param->cub, raycast_param->start, ray);
		raycast_param->start++;
	}
	return (NULL);
}
