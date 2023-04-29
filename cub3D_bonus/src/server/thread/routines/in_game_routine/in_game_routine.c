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
#include "player_data.h"

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
	size_t			count;
	size_t			index;
	t_players_data	players_data;
	int				client_socket;

	count = 0;
	ft_bzero(players_data.players, sizeof(t_player) * PLAYER_LIMIT);
	players_data.event = NULL;
	printf("In Game Thread created\n");
	while (1)
	{
		index = count % server_data->player->size;
		pthread_mutex_lock(server_data->player->players_lock);
		client_socket = server_data->player->players_socket[index];
		if (client_socket != -1)
		{
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
				pthread_mutex_unlock(server_data->player->players_lock);
				return ;
				//TODO: clean exit
			}
		}
		pthread_mutex_unlock(server_data->player->players_lock);
		count++;
	}
}
