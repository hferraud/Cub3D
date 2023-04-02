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
#include "socket_server.h"

static int	client_accept(int server_socket_fd);
static int	new_player_add(int player_socket_fd, t_server_data *server_data);

void	listen_connections(int server_socket_fd, t_server_data *server_data)
{
	int	client_socket_fd;

	int i = 0;
	while (i < 3)
	{
		client_socket_fd = client_accept(server_socket_fd);
		if (client_socket_fd == -1)
		{
			server_data_destroy(server_data);
			exit(1);
		}
		if (new_player_add(client_socket_fd, server_data) == -1)
		{
			server_data_destroy(server_data);
			exit(1);
		}
		i++;
	}
	server_data_destroy(server_data);
}

/**
 * @brief Accept a request from a client_socket
 * @return The file descriptor of the client_socket socket, -1 otherwise
 */
static int	client_accept(int server_socket_fd)
{
	int				client_socket_fd;
	socklen_t		client_addr_len;
	t_sockaddr_in	client_addr;


	client_addr_len = sizeof(t_sockaddr_in);
	client_socket_fd = accept(server_socket_fd, (t_sockaddr *) &client_addr,
			&client_addr_len);
	if (client_socket_fd == -1)
		return (perror("accept()"), errno);
	printf("Connection with a client_socket established\n");
	return (client_socket_fd);
}

static int	new_player_add(int player_socket_fd, t_server_data *server_data)
{
	t_list	*new;
	int		*content;

	pthread_mutex_lock(server_data->client_lock);
	content = (int *) malloc(sizeof(int));
	if (content == NULL)
		return (perror("malloc()"), -1);
	*content = player_socket_fd;
	new = ft_lstnew(content);
	if (new == NULL)
	{
		free(content);
		return (perror("malloc()"), -1);
	}
	ft_lstadd_back(&server_data->client_socket, new);
	pthread_mutex_unlock(server_data->client_lock);
	return (0);
}
