/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_server_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 19:16:00 by edelage           #+#    #+#             */
/*   Updated: 2023/05/14 19:16:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "server_data.h"

static void	close_client(t_server_data *server_data);

void	check_server_error(int server_socket, t_server_data *server_data)
{
	pthread_mutex_lock(server_data->server_status->status_lock);
	if (server_data->server_status->status == ERROR)
	{
		pthread_join(server_data->thread[LAUNCH], NULL);
		pthread_join(server_data->thread[IN_GAME], NULL);
		pthread_mutex_unlock(server_data->server_status->status_lock);
		close_client(server_data);
		server_data_destroy(server_data);
		close(server_socket);
	}
	pthread_mutex_unlock(server_data->server_status->status_lock);
}

static void	close_client(t_server_data *server_data)
{
	int		count;
	t_list	*to_close;
	int		client_socket;

	while (server_data->client_socket)
	{
		to_close = server_data->client_socket;
		server_data->client_socket = server_data->client_socket->next;
		close(*(int *) to_close->content);
		ft_lstdelone(to_close, free);
	}
	count = 0;
	while (count < server_data->player->size)
	{
		client_socket = server_data->player->players_socket[count];
		if (client_socket != -1)
			close(client_socket);
		server_data->player->players_socket[count] = -1;
		count++;
	}
}
