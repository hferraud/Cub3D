/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_door_interact.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mururoah <mururoah@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 23:34:00 by mururoah          #+#    #+#             */
/*   Updated: 2023/05/06 23:34:00 by mururoah         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "cub.h"
#include "raycasting.h"

void	player_door_interact(t_cub *cub)
{
	t_ray	ray;

	if (is_key_pressed(KEY_F, cub))
	{
		ray = ray_cast(cub, cub->player_data.player.rotation);
		if (ray.is_door)
	}
}