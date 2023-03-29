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

/**
 * @brief Create the socket and connect it to the server
 * @return The socket file descriptor on success, -1 otherwise
 */
int	socket_client_init(const char *ip, uint16_t port)
{
	int				socket_fd;
	t_hostent		*host_info;
	t_sockaddr_in	addr;

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd == -1)
		return (perror("socket()"), -1);
	host_info = gethostbyname(ip);
	if (host_info == NULL)
	{
		close(socket_fd);
		return (cub_error("Unknown host\n"));
	}
	addr.sin_addr = *(struct in_addr *) host_info->h_addr;
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;
	if (connect(socket_fd, (t_sockaddr *) &addr, sizeof(t_sockaddr_in)) == -1)
	{
		close(socket_fd);
		return (perror("connect()"), -1);
	}
	ft_putstr("Connected with the server established\n");
	return (socket_fd);
}
