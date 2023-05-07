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
#include <stdbool.h>
#include "cub.h"

static bool	is_door(t_cub *cub, t_vector map_scan);
static void	door_interact(t_cub *cub, t_vector map_pos);

void	player_door_interact(t_cub *cub)
{
	t_vector	map_scan;

	pthread_mutex_lock(cub->player_data.player_lock);
	map_scan.y = (int)cub->player_data.player.pos.x;
	map_scan.x = (int)cub->player_data.player.pos.y;
	pthread_mutex_unlock(cub->player_data.player_lock);
	map_scan.x -= 1;
	if (is_door(cub, map_scan))
		door_interact(cub, map_scan);
	map_scan.x += 1;
	map_scan.y += 1;
	if (is_door(cub, map_scan))
		door_interact(cub, map_scan);
	map_scan.y -= 2;
	if (is_door(cub, map_scan))
		door_interact(cub, map_scan);
	map_scan.y += 1;
	map_scan.x += 1;
	if (is_door(cub, map_scan))
		door_interact(cub, map_scan);
	player_update(cub);
}

static void	door_interact(t_cub *cub, t_vector map_pos)
{
	if (cub->map.map[map_pos.x][map_pos.y] == DOOR_OPEN)
	{
		cub->map.map[map_pos.x][map_pos.y] = DOOR_CLOSE;
		pthread_mutex_lock(cub->player_data.player_lock);
		if (!is_valid_position(cub, cub->player_data.player.pos.x, cub->player_data.player.pos.y))
			cub->map.map[map_pos.x][map_pos.y] = DOOR_OPEN;
		pthread_mutex_unlock(cub->player_data.player_lock);
	}
	else
		cub->map.map[map_pos.x][map_pos.y] = DOOR_OPEN;
}

static bool	is_door(t_cub *cub, t_vector map_scan)
{
	char	cell;

	cell = cub->map.map[map_scan.x][map_scan.y];
	return (cell == DOOR_OPEN || cell == DOOR_CLOSE);
}
