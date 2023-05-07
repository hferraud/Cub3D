/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 21:23:00 by edelage           #+#    #+#             */
/*   Updated: 2023/05/07 21:23:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "server_data.h"
#include "players_data.h"
#include "collectible.h"

static int event_take_collectible(int client_socket, t_vector event_position, t_server_data *server_data);

int	manage_event(int client_socket, t_event event, t_server_data *server_data)
{
	if (event.id == EVENT_TAKE_COLLECTIBLE)
		return (event_take_collectible(client_socket, event.position, server_data));
	return (0);
}

static int event_take_collectible(int client_socket, t_vector event_position, t_server_data *server_data)
{
	char *cell;

	pthread_mutex_lock(server_data->map_lock);
	cell = &server_data->map->map[event_position.y][event_position.x];
	if (collectible_id_get(*cell) != UNDEFINED)
	{
		printf("take at: %d %d\n", event_position.x, event_position.y);
		if (write(client_socket, cell, sizeof(char)) == -1)
		{
			pthread_mutex_unlock(server_data->map_lock);
			return (-1);
		}
		*cell = FLOOR;
		//TODO: Send info to other player
	}
	else
	{
		printf("cant take at: %d %d\n", event_position.x, event_position.y);
		if (write(client_socket, CANT_TAKE, sizeof(char)) == -1)
		{
			pthread_mutex_unlock(server_data->map_lock);
			return (-1);
		}
	}
	pthread_mutex_unlock(server_data->map_lock);
	return (0);
}
