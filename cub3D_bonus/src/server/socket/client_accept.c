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
static void	check_server_error(int server_socket, t_server_data *server_data);
static void	close_client(t_server_data *server_data);

void	listen_connections(int server_socket, t_server_data *server_data)
{
	int	client_socket_fd;

	while (1)
	{
		check_server_error(server_socket, server_data);
		client_socket_fd = client_accept(server_socket);
		if (client_socket_fd == -1)
		{
			server_data_destroy(server_data);
			exit(1);
		}
		pthread_mutex_lock(server_data->client_connected->client_connected_lock);
		if (server_data->client_connected->nb_client_connected == 0)
		{
			printf("No more spawns available\n");
			close(client_socket_fd);
			pthread_mutex_unlock(server_data->client_connected->client_connected_lock);
			continue ;
		}
		else
			server_data->client_connected->nb_client_connected--;
		pthread_mutex_unlock(server_data->client_connected->client_connected_lock);
		if (new_player_add(client_socket_fd, server_data) == -1)
		{
			server_data_destroy(server_data);
			exit(1);
		}
	}
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
	printf("Connection with a client established\n");
	return (client_socket_fd);
}

static int	new_player_add(int player_socket_fd, t_server_data *server_data)
{
	t_list	*new;
	int		*content;

	pthread_mutex_lock(server_data->client_lock);
	content = (int *) malloc(sizeof(int));
	if (content == NULL)
	{
		pthread_mutex_unlock(server_data->client_lock);
		return (perror("malloc()"), -1);
	}
	*content = player_socket_fd;
	new = ft_lstnew(content);
	if (new == NULL)
	{
		free(content);
		pthread_mutex_unlock(server_data->client_lock);
		return (perror("malloc()"), -1);
	}
	ft_lstadd_back(&server_data->client_socket, new);
	pthread_mutex_unlock(server_data->client_lock);
	return (0);
}

static void	check_server_error(int server_socket, t_server_data *server_data)
{
	pthread_mutex_lock(server_data->server_status->status_lock);
	if (server_data->server_status->status == ERROR)
	{
		pthread_join(server_data->thread[LAUNCH], NULL);
		pthread_join(server_data->thread[IN_GAME], NULL);
		pthread_mutex_unlock(server_data->server_status->status_lock);
		close_client(server_data);
		server_data_destroy(server_data);
		close(server_socket);
	}
	pthread_mutex_unlock(server_data->server_status->status_lock);
}

static void	close_client(t_server_data *server_data)
{
	int		count;
	t_list	*to_close;
	int		client_socket;

	while (server_data->client_socket)
	{
		to_close = server_data->client_socket;
		server_data->client_socket = server_data->client_socket->next;
		close(*(int *) to_close->content);
		ft_lstdelone(to_close, free);
	}
	count = 0;
	while (count < server_data->player->size)
	{
		client_socket = server_data->player->players_socket[count];
		if (client_socket != -1)
			close(client_socket);
		server_data->player->players_socket[count] = -1;
		count++;
	}
}
