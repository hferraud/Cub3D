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
# include "define.h"


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
