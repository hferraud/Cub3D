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

static int event_take_collectible(int client_socket, t_event event, t_server_data *server_data);
static int	send_event_to_other_player(int event_client_socket, t_event event, t_server_data *server_data);

int	manage_event(int client_socket, t_event event, t_server_data *server_data)
{
	if (event.id == EVENT_TAKE_COLLECTIBLE)
		return (event_take_collectible(client_socket, event, server_data));
	return (0);
}

static int event_take_collectible(int client_socket, t_event event, t_server_data *server_data)
{
	char *cell;

	pthread_mutex_lock(server_data->map_lock);
	cell = &server_data->map->map[event.position.y][event.position.x];
	if (collectible_id_get(*cell) != UNDEFINED)
	{
		printf("take at: %d %d\n", event.position.x, event.position.y);
		if (write(client_socket, cell, sizeof(char)) == -1)
		{
			pthread_mutex_unlock(server_data->map_lock);
			return (-1);
		}
		*cell = FLOOR;
		if (send_event_to_other_player(client_socket, event, server_data) == -1)
			return (-1);
	}
	else
	{
		printf("cant take at: %d %d\n", event.position.x, event.position.y);
		if (write(client_socket, CANT_TAKE, sizeof(char)) == -1)
		{
			pthread_mutex_unlock(server_data->map_lock);
			return (-1);
		}
	}
	pthread_mutex_unlock(server_data->map_lock);
	return (0);
}

static int	send_event_to_other_player(int event_client_socket, t_event event, t_server_data *server_data)
{
	int		client_socket;
	int		index;

	index = 0;
	pthread_mutex_lock(server_data->player->players_lock);
	while (index < server_data->player->size)
	{
		client_socket = server_data->player->players_socket[index];
		if (client_socket != -1 && client_socket != event_client_socket)
			if (event_request(client_socket, event) == -1)
			{
				pthread_mutex_unlock(server_data->player->players_lock);
				return (-1);
			}
		index++;
	}
	pthread_mutex_unlock(server_data->player->players_lock);
	return (0);
}
