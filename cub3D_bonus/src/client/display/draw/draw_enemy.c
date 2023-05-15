/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_enemy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mururoah <mururoah@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 19:13:00 by mururoah          #+#    #+#             */
/*   Updated: 2023/05/05 19:13:00 by mururoah         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "cub.h"
#include "draw.h"

void	draw_enemy(t_cub *cub, t_enemy enemy, const float *z_buffer)
{
	t_draw_param	draw_param;
	t_fvector		camera;

	if (enemy.id == -1)
		return ;
	camera = enemy_camera_projection(cub, enemy);
	if (camera.y > 0)
	{
		draw_param = enemy_get_draw_param(cub, camera);
		draw_sprite(cub, draw_param, z_buffer, camera.y);
	}
}

/**
 * @brief Get the parameters needed to draw the sprite
 */
t_draw_param	enemy_get_draw_param(t_cub *cub, t_fvector camera)
{
	t_draw_param	dp;
	int				scale;

	dp.sprite = cub->mlx_data->collectible_sprite[MEDIC_KIT_ID];
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

/**
 * @brief Project the sprite in camera space
 */
t_fvector	enemy_camera_projection(t_cub *cub, t_enemy enemy)
{
	t_fvector	camera;
	float		inverse_det;

	inverse_det = -1.f / (
			cub->player_data.camera.x * cub->player_data.player.rotation.y
			- cub->player_data.player.rotation.x * cub->player_data.camera.y);
	camera.x = inverse_det * (
			cub->player_data.player.rotation.y * enemy.relative_pos.x
			- cub->player_data.player.rotation.x * enemy.relative_pos.y);
	camera.y = inverse_det * (
			-cub->player_data.camera.y * enemy.relative_pos.x
			+ cub->player_data.camera.x * enemy.relative_pos.y);
	return (camera);
}

/**
 * @brief Set the distance from the player of all enemies
 */
void	enemies_set_dist(t_cub *cub, t_enemy *enemies, t_player player)
{
	size_t	i;

	i = 0;
	while (i < PLAYER_LIMIT - 1)
	{
		pthread_mutex_lock(cub->enemies_lock);
		enemies[i].id = cub->enemies[i].id;
		if (enemies[i].id != -1)
		{
			enemies[i].player = cub->enemies[i].player;
			pthread_mutex_unlock(cub->enemies_lock);
			enemies[i].relative_pos = fvector_sub(player.pos,
					enemies[i].player.pos);
			enemies[i].dist
				= enemies[i].relative_pos.x * enemies[i].relative_pos.x
				+ enemies[i].relative_pos.y * enemies[i].relative_pos.y;
		}
		else
			pthread_mutex_unlock(cub->enemies_lock);
		i++;
	}
}

/**
 * @brief Sort all enemies from the most far away to the nearest of the player
 */
void	enemies_sort(t_enemy *enemies)
{
	t_enemy	tmp;
	bool	flag;
	size_t	i;

	flag = true;
	while (flag)
	{
		flag = false;
		i = 1;
		while (i < PLAYER_LIMIT - 1 && enemies[i].id != -1)
		{
			if (enemies[i].id != -1 && enemies[i - 1].id != -1
				&& enemies[i].dist > enemies[i - 1].dist)
			{
				flag = true;
				tmp = enemies[i];
				enemies[i] = enemies[i - 1];
				enemies[i - 1] = tmp;
			}
			i++;
		}
	}
}
