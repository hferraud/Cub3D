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

void	draw_enemy(t_cub *cub)
{
	size_t	i;


}

t_enemy	*enemy_set_dist(t_cub *cub)
{
	t_enemy	enemies[PLAYER_LIMIT - 1];
	size_t	i;

	i = 0;
	while (i < PLAYER_LIMIT - 1)
	{
		pthread_mutex_lock(cub->players_lock);
		enemies[i].player = cub->enemies[i].player;
		enemies[i].relative_pos = fvector_sub(cub->player_data.player.pos,
				enemies[i].player.pos);
		pthread_mutex_unlock(cub->players_lock);
		enemies[i].dist = enemies[i].relative_pos.x * enemies[i].relative_pos.x
			+ enemies[i].relative_pos.y * enemies[i].relative_pos.y;
		i++;
	}
}