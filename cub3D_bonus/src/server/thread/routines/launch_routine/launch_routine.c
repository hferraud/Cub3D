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

static int	new_player_fd_get(t_launch_data *launch_data);

void	launch_routine(t_launch_data *launch_data)
{
	int	new_player_fd;

	printf("Launch Thread created\n");
	while (1)
	{
		new_player_fd = new_player_fd_get(launch_data);
		if (new_player_fd != -1)
		{

		}
	}
}

static int	new_player_fd_get(t_launch_data *launch_data)
{
	int	new_player_fd;

	pthread_mutex_lock(launch_data->mut_new_player);
	if (*launch_data->new_player == NULL)
	{
		pthread_mutex_unlock(launch_data->mut_new_player);
		return (-1);
	}
	new_player_fd = *(int *) (*launch_data->new_player)->content;
	pthread_mutex_unlock(launch_data->mut_new_player);
	return (new_player_fd);
}
