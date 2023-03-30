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
# include "map.h"

typedef struct s_server_data		t_server_data;
typedef struct s_launch_data		t_launch_data;
typedef struct s_in_game_data		t_in_game_data;
typedef struct s_players			t_players;

struct s_players
{
	int				*players_fd;
	int				size;
	pthread_mutex_t	*mut_players_fd;
};

struct s_launch_data
{
	t_list			**new_player;
	pthread_mutex_t	*mut_new_player;
	t_players		*players;
	t_map			*map;
	pthread_mutex_t	*mut_spawn;
};

struct s_in_game_data
{
	t_map			*map;
	pthread_mutex_t	*mut_map;
	pthread_mutex_t	*mut_spawn;
};

enum
{
	LAUNCH	=	0,
	IN_GAME	=	1,
};

struct s_server_data
{
	int				server_socket_fd;
	t_list			*new_players;
	pthread_mutex_t	*mut_new_player;
	t_players		*players;
	t_map			*map;
	pthread_mutex_t	*mut_map;
	pthread_mutex_t	*mut_spawn;
	pthread_t		thread[2];
};

/* --- THREAD FUNCTIONS --- */

t_server_data	*thread_init(t_map *map);

/* --- ROUTINES FUNCTIONS --- */

void			launch_routine(t_launch_data *launch_data);
void			in_game_routine(t_in_game_data *in_game_data);

/* ---	SERVER_DATA FUNCTIONS --- */

t_server_data	*server_data_init(t_map *map);
void			server_data_destroy(t_server_data *server_data);

#endif
