/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listening_request.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:44:00 by edelage           #+#    #+#             */
/*   Updated: 2023/04/27 15:44:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "player_data.h"

/**
 * @brief Sends a listening request and updates the information
 * @return 0
 */
int	listening_request(int client_socket, t_players_data *players_data)
{
	char	buf;

	if (write(client_socket, LISTEN_REQUEST, LENGTH_LISTEN_REQUEST) == -1
		|| read(client_socket, &buf, sizeof(char)) <= 0)
		return (cub_error(CLIENT_LOST));
	if (buf == UPDATE)
}