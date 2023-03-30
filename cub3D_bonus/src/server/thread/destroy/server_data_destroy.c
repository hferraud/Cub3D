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

void		map_data_clear(t_map *map);

static void	disconnect_client(t_list *new_players, t_players *players);

void	server_data_destroy(t_server_data *server_data)
{
	map_data_clear(server_data->map);
	if (server_data->mut_new_player)
		pthread_mutex_destroy(server_data->mut_new_player);
	free(server_data->mut_new_player);
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
	disconnect_client(server_data->new_players, server_data->players);
	ft_lstclear(&server_data->new_players, free);
	if (server_data->players)
	{
		free(server_data->players->players_fd);
		if (server_data->players->mut_players_fd)
			pthread_mutex_destroy(server_data->players->mut_players_fd);
		free(server_data->players->mut_players_fd);
		free(server_data->players);
	}
	if (server_data->server_socket_fd != -1)
		close(server_data->server_socket_fd);
	free(server_data);
}

static void	disconnect_client(t_list *new_players, t_players *players)
{
	int	index;

	while (new_players)
	{
		close(*(int *) new_players->content);
		new_players = new_players->next;
	}
	if (players == NULL)
		return ;
	index = 0;
	while (index < players->size)
	{
		if (players->players_fd[index] != -1)
			close(players->players_fd[index]);
		index++;
	}
}
