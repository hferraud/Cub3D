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
#include "player_data.h"

static int	listen_events(int client_socket, t_list **events_list);
static int	listen_event(int client_socket, t_event *event);

/**
 * @brief Sends a listening request and updates the information
 * @return 1 if players data has been update, 0 if players data are the same,
 *  -1 in client error case and -2 in server error cas
 */
int	listening_request(int client_socket, t_players_data *players_data, int client_index)
{
	int		ret;
	char	buf;

	if (write(client_socket, LISTEN_REQUEST, LENGTH_LISTEN_REQUEST) == -1
		|| read(client_socket, &buf, sizeof(char)) <= 0)
		return (cub_error(CLIENT_LOST));
	if (buf == UP_TO_DATE)
		return (0);
	if (read(client_socket, &players_data->players[client_index], sizeof(t_player)) <= 0
		|| read(client_socket, &buf, sizeof(char)) <= 0)
		return (cub_error(CLIENT_LOST));
	if (buf == UP_TO_DATE)
		return (1);
	ret = listen_events(client_socket, &players_data->event);
	if (ret == -1)
	{
		players_data->event = NULL;
		return (-1);
	}
	else if (ret == -2)
		return (-2);
	return (1);
}

/**
 * @brief Listen events from a client
 * @return 0 on success, -1 on client error, -2 on server error
 */
static int	listen_events(int client_socket, t_list **events_list)
{
	char	buf;
	t_event	*event;

	if (read(client_socket, &buf, sizeof(char)) <= 0)
		return (cub_error(CLIENT_LOST));
	while (buf == NEW_EVENT)
	{
		event = (t_event *) malloc(sizeof(t_event));
		if (event == NULL)
		{
			ft_lstclear(events_list, free);
			return (perror("listen_events()"), -2);
		}
		if (listen_event(client_socket, event) == -1)
		{
			free(event);
			return (ft_lstclear(events_list, free), -1);
		}
		ft_lstadd_front(events_list, event);
		if (read(client_socket, &buf, sizeof(char)) <= 0)
			return (ft_lstclear(events_list, free), cub_error(CLIENT_LOST));
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
	if (event->id == EVENT_SHOOT)
		return (0);
	if (read(client_socket, &event->position, sizeof(t_vector)) <= 0)
	{
		free(event);
		return (cub_error(CLIENT_LOST));
	}
	return (0);
}