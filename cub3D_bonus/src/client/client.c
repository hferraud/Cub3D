/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 22:23:00 by edelage           #+#    #+#             */
/*   Updated: 2023/03/28 22:23:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "socket_client.h"

int	main(int argc, char **argv)
{
	uint16_t	port;
	int			socket_fd;

	if (argc != 3)
		return (cub_error("./cub3D IP port\n"));
	port = port_get(argv[2]);
	if (errno)
		return (cub_error("Invalid port\n"));
	socket_fd = socket_client_init(argv[1], port);
	if (socket_fd == -1)
		return (-1);
	close(socket_fd);
	return (0);
}