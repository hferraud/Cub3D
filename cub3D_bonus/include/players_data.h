/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   players_data.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:15:00 by edelage           #+#    #+#             */
/*   Updated: 2023/04/27 15:15:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef PLAYERS_DATA_H
# define PLAYERS_DATA_H

# include "server_data.h"
# include "player.h"
# include "event.h"

# define PLAYER_LIMIT	10

# define LISTEN_REQUEST			"1"
# define LENGTH_LISTEN_REQUEST	1
# define SEND_REQUEST			"2"
# define LENGTH_SEND_REQUEST	1
# define UPDATE					'1'
# define UP_TO_DATE				'0'
# define NEW_EVENT				'1'
# define NO_EVENT				'0'

typedef struct s_players_data	t_players_data;

struct s_players_data
{
	t_player	players[PLAYER_LIMIT];
	t_list		*events;
};

void	disconnect_client(int client_socket, t_server_data *server_data);
int		listening_request(int client_socket, t_players_data *players_data,
			int client_index);

#endif
