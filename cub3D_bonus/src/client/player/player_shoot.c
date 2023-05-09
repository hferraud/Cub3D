/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_shoot.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 21:19:00 by hferraud          #+#    #+#             */
/*   Updated: 2023/05/07 21:19:00 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "cub.h"
#include "draw.h"

void	player_shoot(t_cub *cub)
{
	t_enemy			enemies[PLAYER_LIMIT - 1];
	t_player		player;
	t_fvector		camera;
	t_draw_param	dp;
	size_t			i;

	pthread_mutex_lock(cub->player_data.player_lock);
	player = cub->player_data.player;
	pthread_mutex_unlock(cub->player_data.player_lock);
	enemies_set_dist(cub, enemies, player);
	i = 0;
	while (i < PLAYER_LIMIT - 1)
	{
		if (enemies[i].id != -1)
		{
			camera = enemy_camera_projection(cub, enemies[i]);
			dp = enemy_get_draw_param(cub, camera);
			if (dp.screen.x < WIN_WIDTH / 2 + dp.width / 2 && dp.screen.x > WIN_WIDTH / 2 - dp.width / 2)
				printf("Hit\n");
			else
				printf("Miss\n");
		}
		i++;
	}
}
