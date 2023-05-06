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
#include <stdbool.h>
#include "collectible.h"
#include "cub.h"
#include "draw.h"

static t_draw_param	get_draw_param(t_cub *cub, t_fvector camera);
static t_fvector	camera_projection(t_cub *cub, t_collectible collectible);
static void			collectible_set_dist(t_cub *cub);
static void			collectible_sort(t_cub *cub);

void	draw_collectible(t_cub *cub, const float *z_buffer)
{
	t_collectible	collectible;
	t_draw_param	draw_param;
	t_fvector		camera;
	size_t			i;

	collectible_set_dist(cub);
	collectible_sort(cub);
	i = 0;
	while (i < cub->map.collectible_data.size)
	{
		collectible = cub->map.collectible_data.collectible[i];
		camera = camera_projection(cub, collectible);
		if (camera.y > 0)
		{
			draw_param = get_draw_param(cub, camera);
			draw_sprite(cub, draw_param, camera, z_buffer);
		}
		i++;
	}
}

static t_draw_param	get_draw_param(t_cub *cub, t_fvector camera)
{
	t_draw_param	dp;
	int				scale;

	dp.sprite = cub->mlx_data->collectible_sprite[PISTOL_ID];
	dp.width = WIN_WIDTH / (camera.y * 4);
	dp.height = WIN_HEIGHT / (camera.y * 4);
	dp.screen.x = (WIN_WIDTH / 2.f) * (1 + camera.x / camera.y);
	dp.draw_start.x = dp.screen.x - dp.width / 2;
	dp.draw_end.x = dp.screen.x + dp.width / 2;
	scale = abs((int)(WIN_HEIGHT / camera.y / 2));
	dp.draw_start.y = WIN_HEIGHT / 2 + scale - dp.height;
	dp.draw_end.y = WIN_HEIGHT / 2 + scale;
	return (dp);
}

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

/**
 * @brief Set the distance from the player of all collectibles
 */
static void collectible_set_dist(t_cub *cub)
{
	size_t			i;
	t_collectible	*collectible;

	collectible = cub->map.collectible_data.collectible;
	i = 0;
	while (i < cub->map.collectible_data.size)
	{
		pthread_mutex_lock(cub->player_data.player_lock);
		collectible[i].relative_pos = fvector_sub(cub->player_data.player.pos, collectible[i].pos);
		pthread_mutex_unlock(cub->player_data.player_lock);
		collectible[i].dist = collectible[i].relative_pos.x * collectible[i].relative_pos.x
			+ collectible[i].relative_pos.y * collectible[i].relative_pos.y;
		i++;
	}
}

/**
 * @brief Sort all collectibles from the nearest to the further away of the player
 */
static void	collectible_sort(t_cub *cub)
{
	t_collectible	*collectible;
	t_collectible	tmp;
	bool			flag;
	size_t			i;

	collectible = cub->map.collectible_data.collectible;
	flag = true;
	while (flag)
	{
		flag = false;
		i = 1;
		while (i < cub->map.collectible_data.size)
		{
			if (collectible[i].dist > collectible[i - 1].dist)
			{
				flag = true;
				tmp = collectible[i];
				collectible[i] = collectible[i - 1];
				collectible[i - 1] = tmp;
			}
			i++;
		}
	}
}
