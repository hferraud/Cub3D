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
#include "socket_server.h"

static int	socket_create(const int port);
static int	server_display_ip(void);

/**
 * @brief Parse the port and create the socket for the server
 * @param n The maximum number of clients
 * @return The socket file descriptor on success, -1 otherwise
 */
int	socket_init(const char *ascii_port, int n) {
	int port;
	int socket_fd;

	port = port_get(ascii_port);
	if (port == -1) {
		cub_error("Invalid port\n");
		return (-1);
	}
	socket_fd = socket_create(port);
	if (socket_fd == -1)
		return (-1);
	if (listen(socket_fd, n) == -1)
	{
		close(socket_fd);
		return (perror("listen()"), -1);
	}
	ft_putstr("Socket created\n");
	server_display_ip();
	return (socket_fd);
}

static int	socket_create(const int port)
{
	int				socket_fd;
	int				optval;
	t_sockaddr_in	socket_addr;

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd == -1)
		return (perror("socket()"), -1);
	socket_addr.sin_addr.s_addr = inet_addr("0.0.0.0");
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

static int	server_display_ip(void)
{
	t_ifaddrs	*ifap;
	t_ifaddrs	*current;
	int			family;
	char		host[1028];

	if (getifaddrs(&ifap) == -1)
		return (perror("getifaddrs()"), -1);
	current = ifap;
	while (current)
	{
		family = current->ifa_addr->sa_family;
		if (family == AF_INET)
		{
			if (getnameinfo(current->ifa_addr, sizeof(t_sockaddr_in), host,
				1028, NULL, 0, NI_NUMERICHOST) != 0)
			{
				freeifaddrs(ifap);
				return (perror("getnameinfo()"), -1);
			}
		}
		current = current->ifa_next;
	}
	freeifaddrs(ifap);
	return (0);
}
