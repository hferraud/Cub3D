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

static int				players_init(t_players *players, int nb_spawn);
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
	server_data->players = (t_players *) malloc(sizeof(t_players));
	if (server_data->players == NULL)
		return (server_data_init_error(server_data, "malloc()"));
	if (players_init(server_data->players, map->nb_spawn) == -1)
		return (server_data_init_error(server_data, "players_init()"));
	if (mutexes_init(server_data) == -1)
		return (server_data_init_error(server_data, "mutexes_init()"));
	return (server_data);
}

static int	players_init(t_players *players, int nb_spawn)
{
	ft_bzero(players, sizeof(t_players));
	players->players_fd = (int *) malloc(sizeof(int) * nb_spawn);
	if (players->players_fd == NULL)
		return (-1);
	players->mut_players_fd = malloc(sizeof(pthread_mutex_t));
	if (players->mut_players_fd == NULL)
		return (-1);
	if (pthread_mutex_init(players->mut_players_fd, NULL) != 0)
	{
		free(players->mut_players_fd);
		players->mut_players_fd = NULL;
		return (-1);
	}
	players->size = nb_spawn;
	return (0);
}

static int	mutexes_init(t_server_data *server_data)
{
	server_data->mut_new_player = malloc(sizeof(pthread_mutex_t));
	if (server_data->mut_new_player == NULL)
		return (-1);
	if (pthread_mutex_init(server_data->mut_new_player, NULL) != 0)
	{
		free(server_data->mut_new_player);
		server_data->mut_new_player = NULL;
		return (-1);
	}
	server_data->mut_map = malloc(sizeof(pthread_mutex_t));
	if (server_data->mut_map == NULL)
		return (-1);
	if (pthread_mutex_init(server_data->mut_map, NULL) != 0)
	{
		free(server_data->mut_map);
		server_data->mut_map = NULL;
		return (-1);
	}
	server_data->mut_spawn = malloc(sizeof(pthread_mutex_t));
	if (server_data->mut_spawn == NULL)
		return (-1);
	if (pthread_mutex_init(server_data->mut_spawn, NULL) != 0)
	{
		free(server_data->mut_spawn);
		server_data->mut_spawn = NULL;
		return (-1);
	}
	return (0);
}

static void	server_data_set_to_default(t_server_data *server_data, t_map *map)
{
	server_data->server_socket_fd = -1;
	server_data->new_players = NULL;
	server_data->players = NULL;
	server_data->map = map;
	server_data->mut_map = NULL;
	server_data->mut_spawn = NULL;
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
