/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:10:00 by ethan             #+#    #+#             */
/*   Updated: 2023/03/24 15:10:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "parser_server.h"
#include "socket_server.h"
#include "server_data.h"

int	main(int argc, char **argv)
{
	t_server_data	*server_data;
	t_map			map;
	int				port;
	int				server_fd;

	if (argc != 3)
		return (cub_error("./cub3D_server map.cub port\n"));
	if (parser(argv, &map) == -1)
		return (2);
	server_data = thread_init(&map);
	if (server_data == NULL)
	{
		map_data_clear(&map);
		return (1);
	}
	port = port_get(argv[2]);
	if (port == -1)
	{
		server_data_destroy(server_data);
		return (cub_error("Invalid port\n"));
	}
	server_fd = socket_init(argv[2], map.nb_spawn);
	if (server_fd == -1)
		return (server_data_destroy(server_data), 1);
	listen_connections(server_fd, server_data);
}
