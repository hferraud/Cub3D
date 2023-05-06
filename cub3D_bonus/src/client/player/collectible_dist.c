/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectible_dist.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 17:20:00 by edelage           #+#    #+#             */
/*   Updated: 2023/05/06 17:20:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "collectible.h"
#include "cub.h"

/**
 * @brief Set the distance from the player of all collectibles
 */
void collectible_set_dist(t_cub *cub)
{
	size_t			i;
	t_collectible	*collectibles;

	collectibles = cub->map.collectible_data.collectible;
	i = 0;
	while (i < cub->map.collectible_data.size)
	{
		pthread_mutex_lock(cub->player_data.player_lock);
		collectibles[i].relative_pos = fvector_sub(cub->player_data.player.pos, collectibles->pos);
		pthread_mutex_unlock(cub->player_data.player_lock);
		collectibles[i].dist = collectibles->relative_pos.x * collectibles->relative_pos.x
							   + collectibles->relative_pos.y * collectibles->relative_pos.y;
		i++;
	}
}

/**
 * @brief Sort all collectibles from the nearest to the further away of the player
 */
void	sort_collectible(t_cub *cub)
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
