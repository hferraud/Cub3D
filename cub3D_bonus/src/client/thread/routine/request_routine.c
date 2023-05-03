/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:00:00 by edelage           #+#    #+#             */
/*   Updated: 2023/05/01 15:00:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "cub.h"

void	request_routine(t_cub *cub)
{
	char	buf;

	printf("Request thread created\n");
	while (1)
	{
		printf("%zu\n", read(cub->server_socket, &buf, 1));
		if (read(cub->server_socket, &buf, sizeof(char)) <= 0)
		{
			pthread_mutex_lock(cub->client_status.status_lock);
			cub->client_status.status = ERROR;
			pthread_mutex_unlock(cub->client_status.status_lock);
			perror(NULL);
			printf("Exit thread\n");
			return ;
		}
		if (buf == *LISTEN_REQUEST)
			if (listening_response(cub->server_socket, &cub->player_data) == -1)
			{
				pthread_mutex_lock(cub->client_status.status_lock);
				cub->client_status.status = ERROR;
				pthread_mutex_unlock(cub->client_status.status_lock);
				printf("Exit thread\n");
				return ;
			}

	}
}