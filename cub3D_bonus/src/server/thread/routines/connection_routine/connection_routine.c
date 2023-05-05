/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connection_routine.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 01:53:00 by ethan             #+#    #+#             */
/*   Updated: 2023/03/30 01:53:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "server_data.h"

static int		client_get_socket(t_server_data *server_data);
static t_spawn	*client_get_spawn(int client_socket,
					t_server_data *server_data);
static void		client_to_player(int client_socket, t_server_data *server_data);
static int 		check_end_routine(t_server_status *server_status);

void	connection_routine(t_server_data *server_data)
{
	int		client_socket;
	t_spawn	*spawn;

	printf("Connection Thread created\n");
	while (1)
	{
		if (check_end_routine(server_data->server_status) == -1)
			return ;
		client_socket = client_get_socket(server_data);
		if (client_socket != -1)
		{
			spawn = client_get_spawn(client_socket, server_data);
			if (spawn == NULL)
			{
				dprintf(STDERR_FILENO, "Spawn not found\n");
				printf("Quit connection Thread\n");
				pthread_mutex_lock(server_data->server_status->status_lock);
				server_data->server_status->status = ERROR;
				pthread_mutex_unlock(server_data->server_status->status_lock);
				return ;
			}
			if (map_send(client_socket, server_data, spawn) != -1
				&& path_send(client_socket, server_data) != -1)
				client_to_player(client_socket, server_data);
			else
			{
				lst_del_client(client_socket, server_data, true);
				pthread_mutex_lock(server_data->client_connected->client_connected_lock);
				server_data->client_connected->nb_client_connected++;
				pthread_mutex_unlock(server_data->client_connected->client_connected_lock);
			}
		}
		else
			sleep(1);
	}
}

static int	client_get_socket(t_server_data *server_data)
{
	int	client_socket;

	pthread_mutex_lock(server_data->client_lock);
	if (server_data->client_socket == NULL)
	{
		pthread_mutex_unlock(server_data->client_lock);
		return (-1);
	}
	client_socket = *((int *) server_data->client_socket->content);
	pthread_mutex_unlock(server_data->client_lock);
	return (client_socket);
}

static t_spawn	*client_get_spawn(int client_socket, t_server_data *server_data)
{
	t_list	*head;
	t_spawn	*spawn;

	spawn = NULL;
	pthread_mutex_lock(server_data->spawn_lock);
	head = server_data->map->spawn;
	while (head && spawn == NULL)
	{
		if (((t_spawn *) head->content)->player_id == -1)
		{
			spawn = (t_spawn *) head->content;
			spawn->player_id = client_socket;
		}
		head = head->next;
	}
	pthread_mutex_unlock(server_data->spawn_lock);
	return (spawn);
}

static void	client_to_player(int client_socket, t_server_data *server_data)
{
	int			index;
	t_enemies	*players;

	players = server_data->player;
	index = 0;
	lst_del_client(client_socket, server_data, false);
	pthread_mutex_lock(players->players_lock);
	while (index < players->size && players->players_socket[index] != -1)
		index++;
	players->players_socket[index] = client_socket;
	pthread_mutex_unlock(players->players_lock);
	printf("Data has been sent to the client\n\n");
}

static int check_end_routine(t_server_status *server_status)
{
	pthread_mutex_lock (server_status->status_lock);
	if (server_status->status == ERROR)
	{
		pthread_mutex_unlock (server_status->status_lock);
		return (-1);
	}
	pthread_mutex_unlock (server_status->status_lock);
	return (0);
}
