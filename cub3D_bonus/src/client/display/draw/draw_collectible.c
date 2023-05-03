/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_collectible.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:46:00 by ethan             #+#    #+#             */
/*   Updated: 2023/04/05 17:46:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include <stdbool.h>
#include "collectible.h"
#include "cub.h"

static void		collectible_set_dist(t_cub *cub);
static void		sort_collectible(t_cub *cub);
static float	get_distance_from_player(t_player player, t_fvector pos);

void	draw_collectible(t_cub *cub)
{
	collectible_set_dist(cub);
	sort_collectible(cub);
	printf("dist: %f\n", cub->map.collectible_data.collectible->dist);
}

/**
 * @brief Set the distance from the player of all collectibles
 */
static void collectible_set_dist(t_cub *cub)
{
	size_t			i;
	t_collectible	*collectibles;

	collectibles = cub->map.collectible_data.collectible;
	i = 0;
	while (i < cub->map.collectible_data.size)
	{
		collectibles[i].dist = get_distance_from_player(cub->player, collectibles[i].pos);
		i++;
	}
}

/**
 * @brief Sort all collectibles from the nearest to the further away of the player
 */
static void sort_collectible(t_cub *cub)
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

static float	get_distance_from_player(t_player player, t_fvector pos)
{
	t_fvector	vect;

	vect.x = fabsf(player.pos.x - pos.x);
	vect.y = fabsf(player.pos.y - pos.y);
	return (sqrtf(vect.x * vect.x + vect.y * vect.y));
}
