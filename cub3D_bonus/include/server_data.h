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
# include <fcntl.h>
# include <sys/stat.h>
# include "map_server.h"
# include "define.h"

typedef struct s_server_data		t_server_data;
typedef struct s_players			t_players;

struct s_players
{
	int				*players_socket;
	int				size;
	pthread_mutex_t	*players_lock;
};

enum
{
	LAUNCH	=	0,
	IN_GAME	=	1,
};

struct s_server_data
{
	int				server_socket;
	t_list			*client_socket;
	pthread_mutex_t	*client_lock;
	t_players		*player;
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

/* --- CONNECTION_ROUTINE UTILS FUNCTIONS --- */

int				map_send(int client_socket, t_server_data *server_data,
					t_spawn *spawn);
int				path_send(int client_socket, t_server_data *server_data);
int				file_send(int client_socket, char *path);
void			lst_del_client(int client_socket, t_server_data *server_data);
int				connection_error(int client_socket, char *error_msg,
					t_server_data *server_data);

/* ---	SERVER_DATA FUNCTIONS --- */

t_server_data	*server_data_init(t_map *map);
void			server_data_destroy(t_server_data *server_data);

#endif
