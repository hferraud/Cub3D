/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:27:00 by edelage           #+#    #+#             */
/*   Updated: 2023/05/01 15:27:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "server_data.h"

int	mutexes_init(t_server_data *server_data)
{
	server_data->client_lock = malloc(sizeof(pthread_mutex_t));
	if (server_data->client_lock == NULL)
		return (-1);
	if (pthread_mutex_init(server_data->client_lock, NULL) != 0)
	{
		free(server_data->client_lock);
		server_data->client_lock = NULL;
		return (-1);
	}
	server_data->map_lock = malloc(sizeof(pthread_mutex_t));
	if (server_data->map_lock == NULL)
		return (-1);
	if (pthread_mutex_init(server_data->map_lock, NULL) != 0)
	{
		free(server_data->map_lock);
		server_data->map_lock = NULL;
		return (-1);
	}
	server_data->spawn_lock = malloc(sizeof(pthread_mutex_t));
	if (server_data->spawn_lock == NULL)
		return (-1);
	if (pthread_mutex_init(server_data->spawn_lock, NULL) != 0)
	{
		free(server_data->spawn_lock);
		server_data->spawn_lock = NULL;
		return (-1);
	}
	return (0);
}
