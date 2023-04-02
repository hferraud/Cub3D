/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connection_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 01:53:00 by ethan             #+#    #+#             */
/*   Updated: 2023/03/30 01:53:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "server_data.h"

int				map_send(int client_fd, t_server_data *server_data,
					t_spawn *spawn);

static int		client_get_socket(t_server_data *server_data);
static t_spawn	*client_get_spawn(int client_fd, t_server_data *server_data);

void	connection_routine(t_server_data *server_data)
{
	int		new_player_fd;
	t_spawn	*spawn;

	printf("Launch Thread created\n");
	while (1)
	{
		new_player_fd = client_get_socket(server_data);
		if (new_player_fd != -1)
		{
			spawn = client_get_spawn(new_player_fd, server_data);
			if (spawn == NULL)
			{
				dprintf(STDERR_FILENO, "Spawn not found\n");
				return ;
			}
			if (map_send(new_player_fd, server_data, spawn) == -1)
				return ;
		}
		else
			sleep(1);
	}
}

static int	client_get_socket(t_server_data *server_data)
{
	int	client_socket;

	pthread_mutex_lock(server_data->new_client_lock);
	if (server_data->new_client == NULL)
	{
		pthread_mutex_unlock(server_data->new_client_lock);
		return (-1);
	}
	client_socket = *((int *) server_data->new_client->content);
	pthread_mutex_unlock(server_data->new_client_lock);
	return (client_socket);
}

static t_spawn	*client_get_spawn(int client_fd, t_server_data *server_data)
{
	t_list	*head;
	t_spawn	*spawn;

	spawn = NULL;
	pthread_mutex_lock(server_data->spawn_lock);
	head = server_data->map->spawn;
	while (head && spawn == NULL)
	{
		if (((t_spawn *) head->content)->player_id == -1)
		{
			spawn = (t_spawn *) head->content;
			spawn->player_id = client_fd;
		}
		head = head->next;
	}
	pthread_mutex_unlock(server_data->spawn_lock);
	return (spawn);
}
