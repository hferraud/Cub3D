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

static void	door_interact(t_cub *cub, t_vector map_pos);
static bool	is_door_closable(t_cub *cub);
static bool	is_valid_player_position(t_cub *cub);
static bool	is_door(t_cub *cub, t_vector map_scan);

void	player_door_interact(t_cub *cub)
{
	t_vector	map_scan;

	pthread_mutex_lock(cub->player_data.player_lock);
	map_scan.y = (int)cub->player_data.player.pos.y;
	map_scan.x = (int)cub->player_data.player.pos.x;
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
}

static void	door_interact(t_cub *cub, t_vector map_pos)
{
	char	door_state;
	bool	change_state;

	change_state = true;
	if (cub->map.map[map_pos.y][map_pos.x] == DOOR_OPEN)
	{
		cub->map.map[map_pos.y][map_pos.x] = DOOR_CLOSE;
		if (!is_door_closable(cub))
		{
			door_state = DOOR_OPEN;
			change_state = false;
		}
		else
			door_state = DOOR_CLOSE;
	}
	else
		door_state = DOOR_OPEN;
	cub->map.map[map_pos.y][map_pos.x] = door_state;
	if (change_state)
		add_door_event(cub, map_pos, door_state);
}

static bool	is_door_closable(t_cub *cub)
{
	size_t	i;

	i = 0;
	if (is_valid_player_position(cub) == false)
		return (false);
	while (i < PLAYER_LIMIT - 1)
	{
		pthread_mutex_lock(cub->enemies_lock);
		if (cub->enemies[i].id != -1)
		{
			if (!is_valid_position(cub, cub->enemies[i].player.pos.x,
					cub->enemies[i].player.pos.y))
			{
				pthread_mutex_unlock(cub->enemies_lock);
				return (false);
			}
		}
		pthread_mutex_unlock(cub->enemies_lock);
		i++;
	}
	return (true);
}

static bool	is_valid_player_position(t_cub *cub)
{
	pthread_mutex_lock(cub->player_data.player_lock);
	if (!is_valid_position(cub, cub->player_data.player.pos.x,
			cub->player_data.player.pos.y))
	{
		pthread_mutex_unlock(cub->player_data.player_lock);
		return (false);
	}
	pthread_mutex_unlock(cub->player_data.player_lock);
	return (true);
}

static bool	is_door(t_cub *cub, t_vector map_scan)
{
	char	cell;

	cell = cub->map.map[map_scan.y][map_scan.x];
	return (cell == DOOR_OPEN || cell == DOOR_CLOSE);
}
