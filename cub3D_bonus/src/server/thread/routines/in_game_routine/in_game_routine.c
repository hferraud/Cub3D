/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_game_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 02:00:00 by ethan             #+#    #+#             */
/*   Updated: 2023/03/30 02:00:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "server_data.h"
#include "players_data.h"

void		send_data(int client_index, t_server_data *server_data,
				t_players_data *players_data, bool lock_players);
int			check_server_status(t_server_status *server_status);

static int	process_listening_request(int client_socket,
				t_players_data *players_data, t_server_data *server_data,
				int index);
static void	clear_data(t_server_data *server_data);

/**
 * @brief Routine to retrieve and send data from all players
 */
void	in_game_routine(t_server_data *server_data)
{
	int				index;
	size_t			count;
	t_players_data	players_data;
	int				client_socket;

	count = 0;
	ft_bzero(players_data.players, sizeof(t_player) * PLAYER_LIMIT);
	printf("In Game Thread created\n");
	while (1)
	{
		index = count % server_data->player->size;
		if (index == 0 && check_server_status(server_data->server_status) == -1)
		{
			printf("In Game thread exit\n");
			return ;
		}
		pthread_mutex_lock(server_data->player->players_lock);
		client_socket = server_data->player->players_socket[index];
		pthread_mutex_unlock(server_data->player->players_lock);
		if (client_socket != -1)
			if (process_listening_request(client_socket, &players_data,
					server_data, index) == -1)
				return ;
		count++;
	}
}

static int	process_listening_request(int client_socket,
				t_players_data *players_data, t_server_data *server_data,
				int index)
{
	int	ret;

	ret = listening_request(client_socket, players_data, server_data,
			index);
	if (ret == 1)
		send_data(index, server_data, players_data, true);
	else if (ret == -1)
		disconnect_client(client_socket, server_data, index, players_data);
	else if (ret == -2)
	{
		printf("Quit in_game_thread\n");
		return (clear_data(server_data), -1);
	}
	return (0);
}

static void	clear_data(t_server_data *server_data)
{
	pthread_mutex_unlock(server_data->player->players_lock);
	pthread_mutex_lock(server_data->server_status->status_lock);
	server_data->server_status->status = ERROR;
	pthread_mutex_unlock(server_data->server_status->status_lock);
}

void	send_data(int client_index, t_server_data *server_data,
				t_players_data *players_data, bool lock_players)
{
	int		count;
	int		client_socket;

	count = 0;
	if (lock_players)
		pthread_mutex_lock(server_data->player->players_lock);
	while (count < server_data->player->size)
	{
		client_socket = server_data->player->players_socket[count];
		if (client_socket != -1 && count != client_index
			&& send_request(client_socket, players_data, client_index,
				server_data->player->players_socket[client_index]))
			disconnect_client(client_socket, server_data, client_index,
				players_data);
		count++;
	}
	if (lock_players)
		pthread_mutex_unlock(server_data->player->players_lock);
}
