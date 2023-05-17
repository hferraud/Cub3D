/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listening_response.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 01:43:00 by edelage           #+#    #+#             */
/*   Updated: 2023/05/03 01:43:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "cub.h"
#include "player_data.h"

static int	send_position(int server_socket, t_player_data *player_data,
				bool update);
static int	send_events(int server_socket, t_player_data *player_data);
static int	send_events_router(int server_socket, t_event event,
				t_player_data *player_data);

int	listening_response(int server_socket, t_player_data *player_data)
{
	bool	update;

	pthread_mutex_lock(player_data->update_lock);
	update = player_data->update;
	pthread_mutex_unlock(player_data->update_lock);
	if (send_position(server_socket, player_data, update) == -1)
		return (-1);
	if (update == false)
		return (0);
	if (player_data->events == NULL)
	{
		if (write(server_socket, UP_TO_DATE, LENGTH_REQUEST) == -1)
			return (cub_error(SERVER_LOST));
	}
	else
	{
		if (write(server_socket, UPDATE, LENGTH_REQUEST) == -1
			|| send_events(server_socket, player_data) == -1)
			return (cub_error(SERVER_LOST));
	}
	return (0);
}

static int	send_position(int server_socket, t_player_data *player_data,
				bool update)
{
	if (update == false)
	{
		if (write(server_socket, UP_TO_DATE, LENGTH_REQUEST) == -1)
			return (cub_error(SERVER_LOST));
		return (0);
	}
	if (write(server_socket, UPDATE, LENGTH_REQUEST) == -1)
		return (cub_error(SERVER_LOST));
	pthread_mutex_lock(player_data->player_lock);
	if (write(server_socket, &player_data->player, sizeof(t_player)) == -1)
	{
		pthread_mutex_unlock(player_data->player_lock);
		return (cub_error(SERVER_LOST));
	}
	pthread_mutex_unlock(player_data->player_lock);
	pthread_mutex_lock(player_data->update_lock);
	player_data->update = false;
	pthread_mutex_unlock(player_data->update_lock);
	return (0);
}

/**
 * @return 0 on success, -1 otherwise
 */
static int	send_events(int server_socket, t_player_data *player_data)
{
	t_list	*current;
	t_event	*current_event;

	current = player_data->events;
	while (current)
	{
		current_event = current->content;
		if (write(server_socket, &current_event->id, sizeof(t_event_id)) == -1)
			return (-1);
		if (send_events_router(server_socket, *current_event, player_data)
			== -1)
			return (-1);
		current = current->next;
		if (current && write(server_socket, NEW_EVENT, LENGTH_REQUEST) == -1)
			return (-1);
	}
	if (write(server_socket, NO_EVENT, LENGTH_REQUEST) == -1)
		return (-1);
	ft_lstclear(&player_data->events, free);
	player_data->events = NULL;
	return (0);
}

static int	send_events_router(int server_socket, t_event event,
				t_player_data *player_data)
{
	if (event.id == EVENT_TAKE_COLLECTIBLE)
	{
		if (send_collectible_event(server_socket, event,
				player_data) == -1)
			return (-1);
	}
	else if (event.id == EVENT_DAMAGE)
	{
		if (send_damage_event(server_socket, event) == -1)
			return (-1);
	}
	else if (event.id == EVENT_OPEN_DOOR || event.id == EVENT_CLOSE_DOOR)
	{
		if (send_door_event(server_socket, event) == -1)
			return (-1);
	}
	return (0);
}
