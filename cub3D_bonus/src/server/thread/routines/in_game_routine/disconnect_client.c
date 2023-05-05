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

void	disconnect_client(int client_socket, t_server_data *server_data)
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
		server_data->player->players_socket[count] = -1;
	}
	pthread_mutex_unlock(server_data->player->players_lock);
}