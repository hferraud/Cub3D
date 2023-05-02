/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 00:19:00 by ethan             #+#    #+#             */
/*   Updated: 2023/03/30 00:19:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "server_data.h"

/**
 * @brief Init server_data and create 2 threads
 * @return server_data on success, NULL otherwise
 */
t_server_data	*thread_init(t_map *map)
{
	t_server_data	*server_data;

	server_data = server_data_init(map);
	if (server_data == NULL)
		return (NULL);
	if (pthread_create(&server_data->thread[LAUNCH], NULL,
			(void *) connection_routine, server_data) != 0)
	{
		server_data->thread[LAUNCH] = 0;
		server_data_destroy(server_data);
		return (perror("pthread_create()"), NULL);
	}
	if (pthread_create(&server_data->thread[IN_GAME], NULL,
			(void *)in_game_routine, server_data) != 0)
	{
		pthread_mutex_lock(server_data->server_status->status_lock);
		server_data->server_status->status = ERROR;
		pthread_mutex_unlock(server_data->server_status->status_lock);
		pthread_join(server_data->thread[LAUNCH], NULL);
		server_data->thread[IN_GAME] = 0;
		server_data_destroy(server_data);
		return (perror("pthread_create()"), NULL);
	}
	return (server_data);
}
