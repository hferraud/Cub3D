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

static int	socket_create(uint16_t port);
static int	server_display_ip(void);

/**
 * @brief Parse the port and create the socket for the server
 * @param n The maximum number of clients
 * @return The file descriptor of the socket on success, -1 otherwise
 */
int	socket_init(const char *ascii_port, int n)
{
	uint16_t	port;
	int			socket_fd;

	port = port_get(ascii_port);
	if (errno)
		return (cub_error("Invalid port\n"));
	socket_fd = socket_create(port);
	if (socket_fd == -1)
		return (-1);
	printf("%d\n", n);
	if (listen(socket_fd, n) == -1)
	{
		close(socket_fd);
		return (perror("listen()"), -1);
	}
	ft_putstr("Socket created\n");
	if (server_display_ip() == -1)
		return (close(socket_fd), -1);
	printf("Port\t  : %d\n", port);
	return (socket_fd);
}

static int	socket_create(uint16_t port)
{
	int				socket_fd;
	int				optval;
	t_sockaddr_in	socket_addr;

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd == -1)
		return (perror("socket()"), -1);
	optval = 1;
	if (setsockopt(socket_fd, SOL_SOCKET,
			SO_REUSEADDR | SO_REUSEPORT, &optval, sizeof(int)) == -1)
	{
		close(socket_fd);
		return (perror("setsockopt()"), -1);
	}
	socket_addr.sin_addr.s_addr = inet_addr("0.0.0.0");
	socket_addr.sin_family = AF_INET;
	socket_addr.sin_port = htons(port);
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
	int			ip_found;
	char		host[1028];

	if (getifaddrs(&ifap) == -1)
		return (perror("getifaddrs()"), -1);
	current = ifap;
	ip_found = 0;
	while (current)
	{
		family = current->ifa_addr->sa_family;
		if (family == AF_INET)
		{
			ip_found = 1;
			if (getnameinfo(current->ifa_addr, sizeof(t_sockaddr_in), host,
					1028, NULL, 0, NI_NUMERICHOST) != 0)
			{
				freeifaddrs(ifap);
				return (perror("getnameinfo()"), -1);
			}
			printf("%-10s: IP:\t%s\n", current->ifa_name, host);
		}
		current = current->ifa_next;
	}
	freeifaddrs(ifap);
	if (!ip_found)
		return (cub_error("IP not found\n"));
	return (0);
}
