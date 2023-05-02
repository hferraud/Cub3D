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

static void clear_data(t_server_data *server_data, t_players_data *players_data);

/* Server send request to client
 * client send if info was update
 * if (update)
 * 	send new player data
 * else
 * 	do nothing
 * Server send new data to other player
 * */

void	in_game_routine(t_server_data *server_data)
{
	int				ret;
	int				index;
	size_t			count;
	t_players_data	players_data;
	int				client_socket;

	count = 0;
	ft_bzero(players_data.players, sizeof(t_player) * PLAYER_LIMIT);
	players_data.events = NULL;
	printf("In Game Thread created\n");
	while (1)
	{
		index = count % server_data->player->size;
		pthread_mutex_lock(server_data->player->players_lock);
		client_socket = server_data->player->players_socket[index];
		pthread_mutex_unlock(server_data->player->players_lock);
		if (client_socket != -1)
		{
			printf("%d\n", client_socket);
			ret = listening_request(client_socket, &players_data, index);
			if (ret == 1)
			{
				return ;
				//TODO: Process the data and call to other player (send request)
			}
			else if (ret == -1)
				disconnect_client(client_socket,  server_data);
			else if (ret == -2)
			{
				printf("Quit in_game_thread\n");
				return (clear_data(server_data, &players_data));
			}
		}
		else
			usleep(10000);
		count++;
	}
}

static void clear_data(t_server_data *server_data, t_players_data *players_data)
{
	pthread_mutex_unlock(server_data->player->players_lock);
	pthread_mutex_lock(server_data->server_status->status_lock);
	server_data->server_status->status = ERROR;
	pthread_mutex_unlock(server_data->server_status->status_lock);
	ft_lstclear(&players_data->events, free);
}
