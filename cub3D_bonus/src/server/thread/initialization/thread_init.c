/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 00:19:00 by ethan             #+#    #+#             */
/*   Updated: 2023/03/30 00:19:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "server_data.h"

static t_launch_data	launch_data_init(t_server_data *server_data);
static t_in_game_data	in_game_data_init(t_server_data *server_data);

/**
 * @brief Init server_data and create 2 threads
 * @return server_data on success, NULL otherwise
 */
t_server_data	*thread_init(t_map *map)
{
	t_server_data	*server_data;
	t_launch_data	launch_data;
	t_in_game_data	in_game_data;

	server_data = server_data_init(map);
	if (server_data == NULL)
		return (NULL);
	launch_data = launch_data_init(server_data);
	if (pthread_create(&server_data->thread[LAUNCH], NULL,
			(void *)launch_routine, &launch_data) != 0)
	{
		server_data->thread[LAUNCH] = 0;
		server_data_destroy(server_data);
		return (perror("pthread_create()"), NULL);
	}
	in_game_data = in_game_data_init(server_data);
	if (pthread_create(&server_data->thread[IN_GAME], NULL,
			(void *)in_game_routine, &in_game_data) != 0)
	{
		server_data->thread[IN_GAME] = 0;
		server_data_destroy(server_data);
		return (perror("pthread_create()"), NULL);
	}
	return (server_data);
}

static t_launch_data	launch_data_init(t_server_data *server_data)
{
	t_launch_data	launch_data;

	launch_data.new_player = &server_data->new_players;
	launch_data.mut_new_player = server_data->mut_new_player;
	launch_data.players = server_data->players;
	launch_data.map = server_data->map;
	launch_data.mut_spawn = server_data->mut_spawn;
	return (launch_data);
}

static t_in_game_data	in_game_data_init(t_server_data *server_data)
{
	t_in_game_data	in_game_data;

	in_game_data.map = server_data->map;
	in_game_data.mut_map = server_data->mut_map;
	in_game_data.mut_spawn = server_data->mut_spawn;
	return (in_game_data);
}
