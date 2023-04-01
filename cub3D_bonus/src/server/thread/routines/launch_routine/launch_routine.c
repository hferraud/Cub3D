/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 01:53:00 by ethan             #+#    #+#             */
/*   Updated: 2023/03/30 01:53:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "server_data.h"

int	map_send(int client_fd, t_launch_data *launch_data, t_spawn *spawn);

static int		new_player_fd_get(t_launch_data *launch_data);
static t_spawn	*new_player_get_spawn(int client_fd, t_launch_data *launch_data);

void	launch_routine(t_launch_data *launch_data)
{
	int		new_player_fd;
	t_spawn	*spawn;

	printf("Launch Thread created\n");
	while (1)
	{
		new_player_fd = new_player_fd_get(launch_data);
		if (new_player_fd != -1)
		{
			spawn = new_player_get_spawn(new_player_fd, launch_data);
			if (spawn == NULL)
			{
				dprintf(STDERR_FILENO, "Spawn not found\n");
				return ;
			}
			if (map_send(new_player_fd, launch_data, spawn) == -1)
				return ;
		}
		else
			sleep(1);
	}
}

static int	new_player_fd_get(t_launch_data *launch_data)
{
	int	new_player_fd;

	pthread_mutex_lock(launch_data->mut_new_player);
	if (*launch_data->new_client == NULL)
	{
		pthread_mutex_unlock(launch_data->mut_new_player);
		return (-1);
	}
	new_player_fd = *((int *) (*launch_data->new_client)->content);
	pthread_mutex_unlock(launch_data->mut_new_player);
	return (new_player_fd);
}

static t_spawn	*new_player_get_spawn(int client_fd, t_launch_data *launch_data)
{
	t_list	*head;
	t_spawn	*spawn;

	spawn = NULL;
	pthread_mutex_lock(launch_data->mut_spawn);
	head = launch_data->map->spawn;
	while (head && spawn == NULL)
	{
		if (((t_spawn *) head->content)->player_id == -1)
		{
			spawn = (t_spawn *) head->content;
			spawn->player_id = client_fd;
		}
		head = head->next;
	}
	pthread_mutex_unlock(launch_data->mut_spawn);
	return (spawn);
}
