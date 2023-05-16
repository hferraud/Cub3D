/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disconnect_client.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:55:00 by edelage           #+#    #+#             */
/*   Updated: 2023/04/29 16:55:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "server_data.h"
#include "players_data.h"

void		send_data(int client_index, t_server_data *server_data,
				t_players_data *players_data);

static void	send_disconnect_client(int client_index, t_server_data *server_data,
				t_players_data *players_data);
static void	free_spawn(int client_socket, t_server_data *server_data);

void	disconnect_client(int client_socket, t_server_data *server_data,
			int client_index, t_players_data *players_data)
{
	int	count;

	count = 0;
	pthread_mutex_lock(server_data->player->players_lock);
	while (count < server_data->player->size
		&& client_socket != server_data->player->players_socket[count])
		count++;
	if (count < server_data->player->size)
	{
		printf("client %d disconnected\n", client_socket);
		close(client_socket);
		pthread_mutex_unlock(server_data->player->players_lock);
		send_disconnect_client(client_index, server_data, players_data);
		pthread_mutex_lock(server_data->player->players_lock);
		server_data->player->players_socket[count] = -1;
	}
	pthread_mutex_unlock(server_data->player->players_lock);
	pthread_mutex_lock(server_data->client_connected->client_connected_lock);
	server_data->client_connected->nb_client_connected++;
	free_spawn(client_socket, server_data);
	pthread_mutex_unlock(server_data->client_connected->client_connected_lock);
}

static void	send_disconnect_client(int client_index, t_server_data *server_data,
				t_players_data *players_data)
{
	players_data->players[client_index].pos.x = -1;
	send_data(client_index, server_data, players_data);
}

static void	free_spawn(int client_socket, t_server_data *server_data)
{
	t_list	*current;
	t_spawn	*current_spawn;

	pthread_mutex_lock(server_data->map_lock);
	current = server_data->map->spawn;
	while (current)
	{
		current_spawn = current->content;
		if (current_spawn->player_id == client_socket)
		{
			current_spawn->player_id = -1;
			pthread_mutex_unlock(server_data->map_lock);
			return ;
		}
		current = current->next;
	}
	pthread_mutex_unlock(server_data->map_lock);
}
