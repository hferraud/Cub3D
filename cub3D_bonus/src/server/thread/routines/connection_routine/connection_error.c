/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connection_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 17:00:00 by ethan             #+#    #+#             */
/*   Updated: 2023/04/02 17:00:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "server_data.h"

static void	lst_del_client(int client_socket, t_list **head);
static void	client_delete(void *content);

int	connection_error(int client_socket, char *error_msg,
		t_server_data *server_data)
{
	pthread_mutex_lock(server_data->client_lock);
	lst_del_client(client_socket, &server_data->client_socket);
	pthread_mutex_unlock(server_data->client_lock);
	return (cub_error(error_msg));
}

static void	lst_del_client(int client_socket, t_list **head)
{
	t_list	*previous;
	t_list	*current;

	current = *head;
	if (*(int *) current->content == client_socket)
	{
		*head = current->next;
		ft_lstdelone(current, client_delete);
		return ;
	}
	previous = NULL;
	while (current && *(int *) current->content != client_socket)
	{
		previous = current;
		current = current->next;
	}
	if (current == NULL)
		return ;
	previous->next = current->next;
	ft_lstdelone(current, client_delete);
}

static void	client_delete(void *content)
{
	close(*(int *) content);
	free(content);
}
