/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_data_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 00:42:00 by ethan             #+#    #+#             */
/*   Updated: 2023/03/30 00:42:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "server_data.h"

static int				players_init(t_player *players, int nb_spawn);
static int				mutexes_init(t_server_data *server_data);
static void				server_data_set_to_default(t_server_data *server_data,
							t_map *map);
static t_server_data	*server_data_init_error(t_server_data *server_data,
							char *error_msg);

t_server_data	*server_data_init(t_map *map)
{
	t_server_data	*server_data;

	server_data = (t_server_data *) malloc(sizeof(t_server_data));
	if (server_data == NULL)
		return (server_data_init_error(NULL, "malloc()"));
	server_data_set_to_default(server_data, map);
	server_data->player = (t_player *) malloc(sizeof(t_player));
	if (server_data->player == NULL)
		return (server_data_init_error(server_data, "malloc()"));
	if (players_init(server_data->player, map->nb_spawn) == -1)
		return (server_data_init_error(server_data, "players_init()"));
	if (mutexes_init(server_data) == -1)
		return (server_data_init_error(server_data, "mutexes_init()"));
	return (server_data);
}

static int	players_init(t_player *players, int nb_spawn)
{
	ft_bzero(players, sizeof(t_player));
	players->players_socket = (int *) malloc(sizeof(int) * nb_spawn);
	if (players->players_socket == NULL)
		return (-1);
	players->players_lock = malloc(sizeof(pthread_mutex_t));
	if (players->players_lock == NULL)
		return (-1);
	if (pthread_mutex_init(players->players_lock, NULL) != 0)
	{
		free(players->players_lock);
		players->players_lock = NULL;
		return (-1);
	}
	players->size = nb_spawn;
	return (0);
}

static int	mutexes_init(t_server_data *server_data)
{
	server_data->client_lock = malloc(sizeof(pthread_mutex_t));
	if (server_data->client_lock == NULL)
		return (-1);
	if (pthread_mutex_init(server_data->client_lock, NULL) != 0)
	{
		free(server_data->client_lock);
		server_data->client_lock = NULL;
		return (-1);
	}
	server_data->map_lock = malloc(sizeof(pthread_mutex_t));
	if (server_data->map_lock == NULL)
		return (-1);
	if (pthread_mutex_init(server_data->map_lock, NULL) != 0)
	{
		free(server_data->map_lock);
		server_data->map_lock = NULL;
		return (-1);
	}
	server_data->spawn_lock = malloc(sizeof(pthread_mutex_t));
	if (server_data->spawn_lock == NULL)
		return (-1);
	if (pthread_mutex_init(server_data->spawn_lock, NULL) != 0)
	{
		free(server_data->spawn_lock);
		server_data->spawn_lock = NULL;
		return (-1);
	}
	return (0);
}

static void	server_data_set_to_default(t_server_data *server_data, t_map *map)
{
	server_data->server_socket = -1;
	server_data->client_socket = NULL;
	server_data->player = NULL;
	server_data->map = map;
	server_data->map_lock = NULL;
	server_data->spawn_lock = NULL;
	ft_bzero(server_data->thread, sizeof(pthread_t) * 2);
}

static t_server_data	*server_data_init_error(t_server_data *server_data,
							char *error_msg)
{
	perror(error_msg);
	if (server_data)
		server_data_destroy(server_data);
	return (NULL);
}
