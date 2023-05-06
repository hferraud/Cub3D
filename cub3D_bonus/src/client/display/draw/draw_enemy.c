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

static t_draw_param	get_draw_param(t_cub *cub, t_fvector camera);
static t_fvector	camera_projection(t_cub *cub, t_enemy enemy);
static void			enemies_set_dist(t_cub *cub, t_enemy *enemies);
static void			enemies_sort(t_cub *cub, t_enemy *enemies);

void	draw_enemies(t_cub *cub, const float *z_buffer)
{
	t_enemy			enemies[PLAYER_LIMIT - 1];
	t_draw_param	draw_param;
	t_fvector		camera;
	size_t			i;

	enemies_set_dist(cub, enemies);
	enemies_sort(cub, enemies);
	i = 0;
	while (i < PLAYER_LIMIT - 1)
	{
		camera = camera_projection(cub, enemies[i]);
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

	dp.sprite = cub->mlx_data->collectible_sprite[AMMO_ID];
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

static t_fvector	camera_projection(t_cub *cub, t_enemy enemy)
{
	t_fvector	camera;
	float		inverse_det;

	pthread_mutex_lock(cub->player_data.player_lock);
	inverse_det = -1.f / (
			cub->player_data.camera.x * cub->player_data.player.rotation.y
			- cub->player_data.player.rotation.x * cub->player_data.camera.y);
	camera.x = inverse_det * (
			cub->player_data.player.rotation.y * enemy.relative_pos.x
			- cub->player_data.player.rotation.x * enemy.relative_pos.y);
	pthread_mutex_unlock(cub->player_data.player_lock);
	camera.y = inverse_det * (
			-cub->player_data.camera.y * enemy.relative_pos.x
			+ cub->player_data.camera.x * enemy.relative_pos.y);
}

static void	enemies_set_dist(t_cub *cub, t_enemy *enemies)
{
	size_t	i;

	i = 0;
	while (i < PLAYER_LIMIT - 1)
	{
		pthread_mutex_lock(cub->players_lock);
		enemies[i].player = cub->enemies[i].player;
		pthread_mutex_lock(cub->player_data.player_lock);
		enemies[i].relative_pos = fvector_sub(cub->player_data.player.pos,
				enemies[i].player.pos);
		pthread_mutex_unlock(cub->player_data.player_lock);
		pthread_mutex_unlock(cub->players_lock);
		enemies[i].dist = enemies[i].relative_pos.x * enemies[i].relative_pos.x
			+ enemies[i].relative_pos.y * enemies[i].relative_pos.y;
		i++;
	}
}

static void	enemies_sort(t_cub *cub, t_enemy *enemies)
{
	t_enemy	tmp;
	bool	flag;
	size_t	i;

	flag = true;
	while (flag)
	{
		flag = false;
		i = 1;
		while (i < PLAYER_LIMIT - 1)
		{
			if (enemies[i].dist < enemies[i - 1].dist)
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
