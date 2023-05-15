/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listening_request.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:44:00 by edelage           #+#    #+#             */
/*   Updated: 2023/04/27 15:44:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "server_data.h"
#include "players_data.h"

static int	listen_events(int client_socket, t_server_data *server_data);
static int	listen_event(int client_socket, t_event *event);

/**
 * @brief Sends a listening request and updates the information
 * @return 1 if enemies data has been update, 0 if enemies data are the same,
 *  -1 in client error case and -2 in server error cas
 */
int	listening_request(int client_socket, t_players_data *players_data,
		t_server_data *server_data, int client_index)
{
	int		ret;
	char	buf;

	if (write(client_socket, LISTEN_REQUEST, LENGTH_REQUEST) == -1
		|| read(client_socket, &buf, sizeof(char)) <= 0)
		return (cub_error(CLIENT_LOST));
	if (buf == *UP_TO_DATE)
		return (0);
	if (read(client_socket, &players_data->players[client_index],
			sizeof(t_player)) <= 0
		|| read(client_socket, &buf, sizeof(char)) <= 0)
		return (cub_error(CLIENT_LOST));
	if (buf == *UP_TO_DATE)
		return (1);
	ret = listen_events(client_socket, server_data);
	if (ret == -1)
		return (-1);
	else if (ret == -2)
		return (-2);
	return (1);
}

/**
 * @brief Listen all events from a client
 * @return 0 on success, -1 on client error, -2 on server error
 */
static int	listen_events(int client_socket, t_server_data *server_data)
{
	char	buf;
	t_event	event;

	buf = *NEW_EVENT;
	while (buf == *NEW_EVENT)
	{
		if (listen_event(client_socket, &event) == -1)
			return (-1);
		if (event_router(client_socket, event, server_data) == -1)
			return (-1);
		if (read(client_socket, &buf, sizeof(char)) <= 0)
			return (cub_error(CLIENT_LOST));
	}
	return (0);
}

/**
 * @brief Listen an event from a client and stock it in event
 * @return 0 on success, -1 otherwise
 */
static int	listen_event(int client_socket, t_event *event)
{
	if (read(client_socket, &event->id, sizeof(t_event_id)) <= 0)
		return (free(event), cub_error(CLIENT_LOST));
	if (event->id == EVENT_DAMAGE)
	{
		if (read(client_socket, &event->enemy_id, sizeof(int)) <= 0
			|| read(client_socket, &event->damage, sizeof(t_damage)) <= 0)
			return (free(event), cub_error(CLIENT_LOST));
	}
	else if (read(client_socket, &event->position, sizeof(t_vector)) <= 0)
		return (free(event), cub_error(CLIENT_LOST));
	return (0);
}
