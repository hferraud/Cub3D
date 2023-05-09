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
void collectible_set_dist(t_cub *cub, t_player player)
{
	t_collectible	*collectible;
	size_t			i;

	collectible = cub->map.collectible_data.collectible;
	i = 0;
	pthread_mutex_lock(cub->map.collectible_data.collectible_lock);
	while (i < cub->map.collectible_data.size)
	{
		collectible[i].relative_pos = fvector_sub(player.pos, collectible[i].pos);
		collectible[i].dist = collectible[i].relative_pos.x * collectible[i].relative_pos.x
							  + collectible[i].relative_pos.y * collectible[i].relative_pos.y;
		i++;
	}
	pthread_mutex_unlock(cub->map.collectible_data.collectible_lock);
}

/**
 * @brief Sort all collectibles from the most far away to the nearest of the player
 */
void	collectible_sort(t_cub *cub)
{
	t_collectible	*collectible;
	t_collectible	tmp;
	bool			flag;
	size_t			i;

	collectible = cub->map.collectible_data.collectible;
	flag = true;
	pthread_mutex_lock(cub->map.collectible_data.collectible_lock);
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
	pthread_mutex_unlock(cub->map.collectible_data.collectible_lock);
}
