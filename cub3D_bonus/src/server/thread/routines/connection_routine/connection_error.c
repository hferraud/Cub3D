/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connection_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 17:00:00 by ethan             #+#    #+#             */
/*   Updated: 2023/04/02 17:00:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "server_data.h"

int	connection_error(int client_socket, char *error_msg,
		t_server_data *server_data)
{
	lst_del_client(client_socket, server_data, true);
	return (cub_error(error_msg));
}
