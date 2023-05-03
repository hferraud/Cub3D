/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listening_response.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 01:43:00 by edelage           #+#    #+#             */
/*   Updated: 2023/05/03 01:43:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "cub.h"
#include "player_data.h"

int	listening_response(int server_socket, t_player_data *player_data)
{
	bool	update;

	pthread_mutex_lock(player_data->update_lock);
	update = player_data->update;
	pthread_mutex_unlock(player_data->update_lock);
	if (update == false)
	{
		if (write(server_socket, UP_TO_DATE, LENGTH_REQUEST) == -1)
			return (cub_error(SERVER_LOST));
		return (0);
	}
	if (write(server_socket, UPDATE, LENGTH_REQUEST) == -1)
		return (cub_error(SERVER_LOST));
	pthread_mutex_lock(player_data->player_lock);
	if (write(server_socket, &player_data->player, sizeof(t_player)) == -1)
	{
		pthread_mutex_unlock(player_data->player_lock);
		return (cub_error(SERVER_LOST));
	}
	pthread_mutex_unlock(player_data->player_lock);
	pthread_mutex_lock(player_data->update_lock);
	player_data->update = false;
	pthread_mutex_unlock(player_data->update_lock);
	if (write(server_socket, UP_TO_DATE, LENGTH_REQUEST) == -1)
		return (cub_error(SERVER_LOST));
	return (0);
}