/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_request.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 23:17:00 by edelage           #+#    #+#             */
/*   Updated: 2023/05/03 23:17:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "server_data.h"
#include "players_data.h"

static int	send_enemy_position(int client_socket, t_player player, int client_index);

/**
 * @brief Sends new data to other players
 * @return 1 if players data has been update, 0 if players data are the same,
 *  -1 in client error case and -2 in server error cas
 */
int send_request(int client_socket, t_players_data *players_data, int client_index)
{
//	printf("Send request to client %d\n", client_socket);
	if (write(client_socket, SEND_REQUEST, LENGTH_REQUEST) == -1)
		return (cub_error(CLIENT_LOST));
	send_enemy_position(client_socket, players_data->players[client_index], client_index);
	return (0);
}

static int	send_enemy_position(int client_socket, t_player player, int client_index)
{
	if (write(client_socket, &client_index, sizeof(int)) == -1
		|| write(client_socket, &player, sizeof(t_player)) == -1)
		return (cub_error(CLIENT_LOST));
	return (0);
}