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

static void	disconnect_client(t_list *new_players, t_enemies *players);

void	server_data_destroy(t_server_data *server_data)
{
	map_data_clear(server_data->map);
	if (server_data->server_status)
		pthread_mutex_destroy(server_data->server_status->status_lock);
	free(server_data->server_status);
	if (server_data->client_connected)
		pthread_mutex_destroy(server_data->client_connected->client_connected_lock);
	free(server_data->client_connected);
	if (server_data->client_lock)
		pthread_mutex_destroy(server_data->client_lock);
	free(server_data->client_lock);
	if (server_data->map_lock)
		pthread_mutex_destroy(server_data->map_lock);
	free(server_data->map_lock);
	if (server_data->spawn_lock)
		pthread_mutex_destroy(server_data->spawn_lock);
	free(server_data->spawn_lock);
	if (server_data->thread[LAUNCH] != 0)
		pthread_cancel(server_data->thread[LAUNCH]);
	if (server_data->thread[IN_GAME] != 0)
		pthread_cancel(server_data->thread[IN_GAME]);
	disconnect_client(server_data->client_socket, server_data->player);
	ft_lstclear(&server_data->client_socket, free);
	if (server_data->player)
	{
		free(server_data->player->players_socket);
		if (server_data->player->players_lock)
			pthread_mutex_destroy(server_data->player->players_lock);
		free(server_data->player->players_lock);
		free(server_data->player);
	}
	free(server_data);
}

static void	disconnect_client(t_list *new_players, t_enemies *players)
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
		if (players->players_socket[index] != -1)
			close(players->players_socket[index]);
		index++;
	}
}
