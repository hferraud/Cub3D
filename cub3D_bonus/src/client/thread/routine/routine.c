/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:00:00 by edelage           #+#    #+#             */
/*   Updated: 2023/05/01 15:00:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "cub.h"

static int	response_router(t_cub *cub, char buf);
static void	error_exit(t_cub *cub);

void	routine(t_cub *cub)
{
	char	buf;

	printf("Request thread created\n");
	while (1)
	{
		pthread_mutex_lock(cub->client_status.status_lock);
		if (cub->client_status.status == ERROR)
		{
			pthread_mutex_unlock(cub->client_status.status_lock);
			printf("Exit thread\n");
			return ;
		}
		pthread_mutex_unlock(cub->client_status.status_lock);
		if (read(cub->server_socket, &buf, sizeof(char)) <= 0)
			return (error_exit(cub));
		if (response_router(cub, buf) == -1)
			return (error_exit(cub));
	}
}

static int	response_router(t_cub *cub, char buf)
{
	if (buf == *LISTEN_REQUEST)
	{
		if (listening_response(cub->server_socket, &cub->player_data) == -1)
			return (-1);
	}
	else if (buf == *SEND_REQUEST)
	{
		if (send_response(cub->server_socket, cub) == -1)
			return (-1);
	}
	else if (buf == *EVENT_REQUEST)
	{
		if (event_response(cub->server_socket, cub) == -1)
			return (-1);
	}
	return (0);
}

static void	error_exit(t_cub *cub)
{
	pthread_mutex_lock(cub->client_status.status_lock);
	cub->client_status.status = ERROR;
	pthread_mutex_unlock(cub->client_status.status_lock);
	printf("Exit thread\n");
}
