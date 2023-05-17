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

pthread_mutex_t	*mutex_init(void);

int	mutexes_init(t_server_data *server_data)
{
	server_data->client_lock = mutex_init();
	if (server_data->client_lock == NULL)
		return (-1);
	server_data->map_lock = mutex_init();
	if (server_data->map_lock == NULL)
		return (-1);
	server_data->spawn_lock = mutex_init();
	if (server_data->spawn_lock == NULL)
		return (-1);
	return (0);
}
