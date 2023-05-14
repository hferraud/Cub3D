/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_send_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 01:35:00 by edelage           #+#    #+#             */
/*   Updated: 2023/05/14 01:35:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "server_data.h"

void	map_send_error(int client_socket, t_server_data *server_data)
{
	lst_del_client(client_socket, server_data, true);
	pthread_mutex_lock(server_data->client_connected
		->client_connected_lock);
	server_data->client_connected->nb_client_connected++;
	pthread_mutex_unlock(server_data->client_connected
		->client_connected_lock);
}
