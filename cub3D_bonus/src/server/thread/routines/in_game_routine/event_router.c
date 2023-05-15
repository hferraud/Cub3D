/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_router.c                                     :+:      :+:    :+:   */
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

static int	event_take_collectible(int client_socket, t_event event,
				t_server_data *server_data);
static int	take_collectible(int client_socket, char *cell,
				t_server_data *server_data, t_event event);
static int	event_door(int client_socket, t_event event,
				t_server_data *server_data);
static int	send_event_update(int event_client_socket, t_event event,
				t_server_data *server_data);

int	event_router(int client_socket, t_event event, t_server_data *server_data)
{
	if (event.id == EVENT_TAKE_COLLECTIBLE)
		return (event_take_collectible(client_socket, event, server_data));
	else if (event.id == EVENT_OPEN_DOOR || event.id == EVENT_CLOSE_DOOR)
		return (event_door(client_socket, event, server_data));
	else if (event.id == EVENT_DAMAGE)
		return (event_request(event.enemy_id, event));
	return (0);
}

static int	event_door(int client_socket, t_event event,
				t_server_data *server_data)
{
	char	*cell;

	pthread_mutex_lock(server_data->map_lock);
	cell = &server_data->map->map[event.position.y][event.position.x];
	if ((event.id == EVENT_CLOSE_DOOR && *cell == DOOR_OPEN)
		|| (event.id == EVENT_OPEN_DOOR && *cell == DOOR_CLOSE))
	{
		if (event.id == EVENT_CLOSE_DOOR)
		{
			printf("%d close door at: %d %d\n", client_socket, event.position.x,
				event.position.y);
			*cell = DOOR_CLOSE;
		}
		else
		{
			printf("%d open door at: %d %d\n", client_socket, event.position.x,
				event.position.y);
			*cell = DOOR_OPEN;
		}
		if (send_event_update(client_socket, event, server_data) == -1)
			return (-1);
	}
	pthread_mutex_unlock(server_data->map_lock);
	return (0);
}

static int	event_take_collectible(int client_socket, t_event event,
				t_server_data *server_data)
{
	char	*cell;

	pthread_mutex_lock(server_data->map_lock);
	cell = &server_data->map->map[event.position.y][event.position.x];
	if (collectible_id_get(*cell) != UNDEFINED)
	{
		if (take_collectible(client_socket, cell, server_data, event) == -1)
			return (-1);
	}
	else
	{
		printf("%d cant take at: %d %d\n", client_socket, event.position.x,
			event.position.y);
		if (write(client_socket, CANT_TAKE, sizeof(char)) == -1)
		{
			pthread_mutex_unlock(server_data->map_lock);
			return (-1);
		}
	}
	pthread_mutex_unlock(server_data->map_lock);
	return (0);
}

static int	take_collectible(int client_socket, char *cell,
				t_server_data *server_data, t_event event)
{
	printf("%d take collectible at: %d %d\n", client_socket,
		event.position.x, event.position.y);
	if (write(client_socket, cell, sizeof(char)) == -1)
	{
		pthread_mutex_unlock(server_data->map_lock);
		return (-1);
	}
	*cell = FLOOR;
	if (send_event_update(client_socket, event, server_data) == -1)
		return (-1);
	return (0);
}

static int	send_event_update(int event_client_socket, t_event event,
				t_server_data *server_data)
{
	int		client_socket;
	int		index;

	index = 0;
	pthread_mutex_lock(server_data->player->players_lock);
	while (index < server_data->player->size)
	{
		client_socket = server_data->player->players_socket[index];
		if (client_socket != -1 && client_socket != event_client_socket)
		{
			if (event_request(client_socket, event) == -1)
			{
				pthread_mutex_unlock(server_data->player->players_lock);
				return (-1);
			}
		}
		index++;
	}
	pthread_mutex_unlock(server_data->player->players_lock);
	return (0);
}
