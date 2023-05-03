/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_delete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 00:20:00 by edelage           #+#    #+#             */
/*   Updated: 2023/04/03 00:20:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "server_data.h"

static void	client_delete(void *content);

void	lst_del_client(int client_socket, t_server_data *server_data, bool close)
{
	t_list	*previous;
	t_list	*current;

	pthread_mutex_lock(server_data->client_lock);
	current = server_data->client_socket;
	if (*(int *) current->content == client_socket)
	{
		server_data->client_socket = current->next;
		if (close == true)
			ft_lstdelone(current, client_delete);
		else
			ft_lstdelone(current, free);
		pthread_mutex_unlock(server_data->client_lock);
		return ;
	}
	previous = NULL;
	while (current && *(int *) current->content != client_socket)
	{
		previous = current;
		current = current->next;
	}
	if (current == NULL)
	{
		pthread_mutex_unlock(server_data->client_lock);
		return ;
	}
	previous->next = current->next;
	if (close == true)
		ft_lstdelone(current, client_delete);
	else
		ft_lstdelone(current, free);
	pthread_mutex_unlock(server_data->client_lock);
}

static void	client_delete(void *content)
{
	close(*(int *) content);
	free(content);
}
