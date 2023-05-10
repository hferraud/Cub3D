/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_response.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 01:56:00 by ethan             #+#    #+#             */
/*   Updated: 2023/05/08 01:56:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "cub.h"
#include "player_data.h"

static void	process_event(t_event event, t_cub *cub);
static void	process_door_event(t_event event, t_map_client *map);
static void	process_collectible_event(t_vector position, t_collectible_data *collectible_data);
static void	process_damage_event(t_damage damage, t_cub *cub);

int event_response(int server_socket, t_cub *cub)
{
	t_event	event;

	if (read(server_socket, &event.id, sizeof(t_event_id)) <= 0)
		return (-1);
	if (event.id == EVENT_DAMAGE)
	{
		if (read(server_socket, &event.damage, sizeof(t_damage)) <= 0)
			return (-1);
	}
	else if (read(server_socket, &event.position, sizeof(t_vector)) <= 0)
		return (-1);
	process_event(event, cub);
	return (0);
}

static void	process_event(t_event event, t_cub *cub)
{
	if (event.id == EVENT_TAKE_COLLECTIBLE)
		process_collectible_event(event.position, &cub->map.collectible_data);
	else if (event.id == EVENT_DAMAGE)
		process_damage_event(event.damage, cub);
	else if (event.id == EVENT_OPEN_DOOR || event.id == EVENT_CLOSE_DOOR)
		process_door_event(event, &cub->map);
}

static void	process_door_event(t_event event, t_map_client *map)
{
	char	*cell;

	cell = &map->map[event.position.y][event.position.x];
	pthread_mutex_lock(map->map_lock);
	if (event.id == EVENT_CLOSE_DOOR)
		*cell = DOOR_CLOSE;
	else
		*cell = DOOR_OPEN;
	pthread_mutex_unlock(map->map_lock);
}

static void	process_collectible_event(t_vector position, t_collectible_data *collectible_data)
{
	size_t				index;

	index = 0;
	pthread_mutex_lock(collectible_data->collectible_lock);
	while (index < collectible_data->size
		&& ((int) collectible_data->collectible[index].pos.x != position.x
		|| (int) collectible_data->collectible[index].pos.y != position.y))
		index++;
	if (index == collectible_data->size)
	{
		pthread_mutex_unlock(collectible_data->collectible_lock);
		return ;
	}
	if (index < collectible_data->size - 1)
		collectible_data->collectible[index]
		= collectible_data->collectible[collectible_data->size - 1];
	collectible_data->size--;
	pthread_mutex_unlock(collectible_data->collectible_lock);
}

static void	process_damage_event(t_damage damage, t_cub *cub)
{
	int	*life;

	life = &cub->player_data.player_status.life;
	pthread_mutex_lock(cub->player_data.player_lock);
	*life = *life - damage;
	if (*life <= 0)
	{
		printf("You're dead\n");
		player_pos_init(cub);
		pthread_mutex_lock(cub->player_data.update_lock);
		cub->player_data.update = true;
		pthread_mutex_unlock(cub->player_data.update_lock);
		*life = LIFE_MAX;
	}
	else
		printf("life: %d\n", *life);
	pthread_mutex_unlock(cub->player_data.player_lock);
}
