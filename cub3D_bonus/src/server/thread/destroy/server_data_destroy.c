/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_data_destroy.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 00:46:00 by ethan             #+#    #+#             */
/*   Updated: 2023/03/30 00:46:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "server_data.h"

void	map_data_clear(t_map *map);

void	server_data_destroy(t_server_data *server_data)
{
	ft_lstclear(&server_data->new_player, free);
	if (server_data->players)
	{
		free(server_data->players->players_fd);
		if (server_data->players->mut_players_fd)
			pthread_mutex_destroy(server_data->players->mut_players_fd);
		free(server_data->players);
	}
	map_data_clear(server_data->map);
	if (server_data->mut_map)
		pthread_mutex_destroy(server_data->mut_map);
	free(server_data->mut_map);
	if (server_data->mut_spawn)
		pthread_mutex_destroy(server_data->mut_spawn);
	free(server_data->mut_spawn);
	if (server_data->thread[LAUNCH] != 0)
		pthread_cancel(server_data->thread[LAUNCH]);
	if (server_data->thread[IN_GAME] != 0)
		pthread_cancel(server_data->thread[IN_GAME]);
	free(server_data);
}
