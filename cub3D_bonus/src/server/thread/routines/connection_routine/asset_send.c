/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_send.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 22:17:00 by ethan             #+#    #+#             */
/*   Updated: 2023/04/03 22:17:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "server_data.h"

int	path_send(int client_socket, t_server_data *server_data)
{
	int				ret;
	char			**path;
	t_texture_id	id;

	path = server_data->map->path;
	id = 0;
	while (id != UNDEFINED_ID)
	{
		ret = file_send(client_socket, path[id]);
		if (ret == -1)
			return (-1);
		else if (ret == 1)
			exit(1);
		id++;
	}
	printf("All texture have been sent to the client\n");
	return (0);
}
