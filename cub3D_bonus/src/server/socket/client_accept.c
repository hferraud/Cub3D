/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_accept.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 02:37:00 by edelage           #+#    #+#             */
/*   Updated: 2023/03/29 02:37:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "socket_client.h"

int client_accept(int server_socket_fd)
{
	int				client_socket_fd;
	socklen_t		client_addr_len;
	t_sockaddr_in	client_addr;


	client_addr_len = sizeof(t_sockaddr_in);
	client_socket_fd = accept(server_socket_fd, (t_sockaddr *) &client_addr,
		&client_addr_len);
	if (client_socket_fd == -1)
		return (perror("accept()"), errno);
	printf("Connection with the client established\n");
	return (client_socket_fd);
}
