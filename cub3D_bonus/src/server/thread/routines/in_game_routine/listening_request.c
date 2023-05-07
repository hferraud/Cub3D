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
 * @return 1 if players data has been update, 0 if players data are the same,
 *  -1 in client error case and -2 in server error cas
 */
int	listening_request(int client_socket, t_players_data *players_data, t_server_data *server_data, int client_index)
{
	int		ret;
	char	buf;

	if (write(client_socket, LISTEN_REQUEST, LENGTH_REQUEST) == -1
		|| read(client_socket, &buf, sizeof(char)) <= 0)
		return (cub_error(CLIENT_LOST));
	if (buf == *UP_TO_DATE)
		return (0);
	printf("Player %d data needs to be update\n", client_socket);
	if (read(client_socket, &players_data->players[client_index], sizeof(t_player)) <= 0
		|| read(client_socket, &buf, sizeof(char)) <= 0)
		return (cub_error(CLIENT_LOST));
	printf("Player %d position: x: %f y: %f\n", client_socket, players_data->players[client_index].pos.x, players_data->players[client_index].pos.y);
	printf("Player %d rotation: x: %f y: %f\n", client_socket, players_data->players[client_index].rotation.x, players_data->players[client_index].rotation.y);
	if (buf == *UP_TO_DATE)
	{
		printf("Player %d has no events\n", client_socket);
		return (1);
	}
	printf("Player %d has events\n", client_socket);
	ret = listen_events(client_socket, server_data);
	if (ret == -1)
		return (-1);
	else if (ret == -2)
		return (-2);
	return (1);
}

/**
 * @brief Listen events from a client
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
		if (manage_event(client_socket, event, server_data) == -1)
			return (-1);
		if (read(client_socket, &buf, sizeof(char)) <= 0)
			return (cub_error(CLIENT_LOST));
	}
	return (0);
}

/**
 * @return 0 on success, -1 otherwise
 */
static int	listen_event(int client_socket, t_event *event)
{
	if (read(client_socket, &event->id, sizeof(t_event_id)) <= 0)
	{
		free(event);
		return (cub_error(CLIENT_LOST));
	}
	if (event->id == EVENT_DEATH)
		return (0);
	if (read(client_socket, &event->position, sizeof(t_vector)) <= 0)
	{
		free(event);
		return (cub_error(CLIENT_LOST));
	}
	return (0);
}