/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_data.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 21:56:00 by ethan             #+#    #+#             */
/*   Updated: 2023/03/29 21:56:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef SERVER_DATA_H
# define SERVER_DATA_H

# include <pthread.h>
# include <stdio.h>
# include <errno.h>
# include "map_server.h"

typedef struct s_server_data		t_server_data;
typedef struct s_players			t_players;

struct s_players
{
	int				*players_socket;
	int				size;
	pthread_mutex_t	*socket_lock;
};

enum
{
	LAUNCH	=	0,
	IN_GAME	=	1,
};

struct s_server_data
{
	int				server_socket;
	t_list			*new_client;
	pthread_mutex_t	*new_client_lock;
	t_players		*players;
	t_map			*map;
	pthread_mutex_t	*map_lock;
	pthread_mutex_t	*spawn_lock;
	pthread_t		thread[2];
};

/* --- THREAD FUNCTIONS --- */

t_server_data	*thread_init(t_map *map);

/* --- ROUTINES FUNCTIONS --- */

void			connection_routine(t_server_data *server_data);
void			in_game_routine(t_server_data *server_data);

/* ---	SERVER_DATA FUNCTIONS --- */

t_server_data	*server_data_init(t_map *map);
void			server_data_destroy(t_server_data *server_data);

#endif
