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
#include <signal.h>

t_server_data	*g_server_data;

void	server_exit(int signum);

int	main(int argc, char **argv)
{
	t_map			map;
	int				server_fd;

	if (argc != 3)
		return (cub_error("./cub3D_server map.cub port\n"));
	if (parser(argv, &map) == -1)
		return (2);
	g_server_data = thread_init(&map);
	if (g_server_data == NULL)
	{
		map_data_clear(&map);
		return (1);
	}
	server_fd = socket_init(argv[2], map.nb_spawn);
	if (server_fd == -1)
		return (server_data_destroy(g_server_data), 1);
	signal(SIGINT, server_exit);
	listen_connections(server_fd, g_server_data);
}
