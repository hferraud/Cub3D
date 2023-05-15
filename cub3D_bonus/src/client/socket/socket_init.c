/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 02:01:00 by edelage           #+#    #+#             */
/*   Updated: 2023/03/29 02:01:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "socket_client.h"

static int	socket_client_parse(int argc, char **argv, t_hostent **host_info,
				uint16_t *port);

/**
 * @brief Create the socket and connect it to the server
 * @return The socket file descriptor on success, -1 otherwise
 */
int	socket_client_init(int argc, char **argv)
{
	int				socket_fd;
	t_hostent		*host_info;
	t_sockaddr_in	addr;
	uint16_t		port;

	if (socket_client_parse(argc, argv, &host_info, &port) == -1)
		return (-1);
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd == -1)
		return (perror("socket()"), -1);
	addr.sin_addr = *(struct in_addr *) host_info->h_addr;
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;
	if (connect(socket_fd, (t_sockaddr *) &addr, sizeof(t_sockaddr_in)) == -1)
	{
		close(socket_fd);
		return (perror("connect()"), -1);
	}
	ft_putstr("Connection with server established\n");
	return (socket_fd);
}

static int	socket_client_parse(int argc, char **argv, t_hostent **host_info,
				uint16_t *port)
{
	if (argc != 3)
		return (cub_error("./cub3D IP port\n"));
	*port = port_get(argv[2]);
	if (errno)
		return (cub_error("Invalid port\n"));
	*host_info = gethostbyname(argv[1]);
	if (*host_info == NULL)
		return (cub_error("Unknown IP\n"));
	return (0);
}
