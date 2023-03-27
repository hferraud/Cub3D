/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 23:21:00 by ethan             #+#    #+#             */
/*   Updated: 2023/03/26 23:21:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "socket_bonus.h"

static int	socket_create(const char *ip, const int port);

/**
 * @brief Parse the port and create the socket for the server
 * @return The socket file descriptor on success, -1 otherwise
 */
int	socket_init(const char *ip, const char *ascii_port)
{
	int	port;
	int	socket_fd;

	port = port_get(ascii_port);
	if (port == -1)
	{
		cub_error("Invalid port\n");
		return (EINVAL);
	}
	socket_fd = socket_create(ip, port);
	if (socket_fd >= 0)
		ft_putstr("Socket created\n");
	return (socket_fd);
}

static int	socket_create(const char *ip, const int port)
{
	int				socket_fd;
	int				optval;
	t_sockaddr_in	socket_addr;

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd == -1)
		return (perror("socket()"), -1);
	socket_addr.sin_addr.s_addr = inet_addr(ip);
	socket_addr.sin_family = AF_INET;
	socket_addr.sin_port = htons(port);
	optval = 1;
	if (setsockopt(socket_fd, SOL_SOCKET,
			SO_REUSEADDR | SO_REUSEPORT, &optval, sizeof(int)) == -1)
	{
		close(socket_fd);
		return (perror("setsockopt()"), -1);
	}
	if (bind(socket_fd, (t_sockaddr *) &socket_addr, sizeof(t_sockaddr_in))
		== -1)
	{
		close(socket_fd);
		return (perror("bind()"), -1);
	}
	return (socket_fd);
}
