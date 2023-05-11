/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/* 	 draw_collectible.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 23:23:00 by edelage           #+#    #+#             */
/*   Updated: 2023/03/13 23:23:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "collectible.h"
#include "cub.h"
#include "draw.h"

static t_draw_param	get_draw_param(t_cub *cub, t_fvector camera, t_collectible collectible);
static t_fvector	camera_projection(t_cub *cub, t_collectible collectible);

void	draw_collectible(t_cub *cub, t_collectible collectible, const float *z_buffer)
{
	t_draw_param		draw_param;
	t_fvector			camera;

	camera = camera_projection(cub, collectible);
	if (camera.y > 0)
	{
		draw_param = get_draw_param(cub, camera, collectible);
		draw_sprite(cub, draw_param, z_buffer, camera.y);
	}
}

/**
 * @brief Get the parameters needed to draw the sprite
 */
static t_draw_param	get_draw_param(t_cub *cub, t_fvector camera, t_collectible collectible)
{
	t_draw_param	dp;
	int				scale;

	dp.sprite = cub->mlx_data->collectible_sprite[collectible.id];
	dp.width = dp.sprite.width / camera.y;
	dp.height = dp.sprite.height / camera.y;
	dp.screen.x = (WIN_WIDTH / 2.f) * (1 + camera.x / camera.y);
	dp.draw_start.x = dp.screen.x - dp.width / 2;
	dp.draw_end.x = dp.screen.x + dp.width / 2;
	scale = abs((int)(WIN_HEIGHT / camera.y / 2));
	dp.draw_start.y = WIN_HEIGHT / 2 + scale - dp.height;
	dp.draw_end.y = WIN_HEIGHT / 2 + scale;
	return (dp);
}

/**
 * @brief Project the sprite in camera space
 */
static t_fvector	camera_projection(t_cub *cub, t_collectible collectible)
{
	t_fvector	camera;
	float		inverse_det;

	pthread_mutex_lock(cub->player_data.player_lock);
	inverse_det = -1.f / (
			cub->player_data.camera.x * cub->player_data.player.rotation.y
			- cub->player_data.player.rotation.x * cub->player_data.camera.y);
	camera.x = inverse_det * (
			cub->player_data.player.rotation.y * collectible.relative_pos.x
			- cub->player_data.player.rotation.x * collectible.relative_pos.y);
	pthread_mutex_unlock(cub->player_data.player_lock);
	camera.y = inverse_det * (
			-cub->player_data.camera.y * collectible.relative_pos.x
			+ cub->player_data.camera.x * collectible.relative_pos.y);
	return (camera);
}
