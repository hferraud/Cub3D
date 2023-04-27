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
	size_t			count;
	size_t			index;
	t_players_data	players_data;

	count = 0;
	ft_bzero(players_data.players, sizeof(t_player) * PLAYER_LIMIT);
	players_data.event = NULL;
	printf("In Game Thread created\n");
	while (1)
	{
		index = count % server_data->player->size;
		pthread_mutex_lock(server_data->player->players_lock);
		if (server_data->player->players_socket[index] != -1)
		{

		}
		pthread_mutex_unlock(server_data->player->players_lock);
		count++;
	}
}
