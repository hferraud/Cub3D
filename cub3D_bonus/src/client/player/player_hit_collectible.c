/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_hit_collectible.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 13:58:00 by edelage           #+#    #+#             */
/*   Updated: 2023/05/07 13:58:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "cub.h"
#include "player.h"

/**
 * @return 1 if the player touches a collectible, 0 otherwise
 */
int	player_hit_collectible(t_cub *cub)
{
	t_collectible_data	collectible_data;
	t_collectible		nearest_collectible;
	t_player			player;
	float				dist;

	collectible_data = cub->map.collectible_data;
	if (collectible_data.size == 0)
		return (0);
	nearest_collectible
		= collectible_data.collectible[collectible_data.size - 1];
	player = cub->player_data.player;
	pthread_mutex_lock(collectible_data.collectible_lock);
	dist = sqrtf(
			powf(nearest_collectible.pos.x - player.pos.x, 2)
			+ powf(nearest_collectible.pos.y - player.pos.y, 2)
			);
	pthread_mutex_unlock(collectible_data.collectible_lock);
	return (dist < (PLAYER_OFFSET + COLLECTIBLE_OFFSET));
}
