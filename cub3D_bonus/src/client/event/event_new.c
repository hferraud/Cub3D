/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:59:00 by ethan             #+#    #+#             */
/*   Updated: 2023/05/08 17:59:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "cub.h"
#include "player_data.h"

t_list	*new_event(t_event event_data)
{
	t_list	*event_node;
	t_event *event;

	event = malloc(sizeof(t_event));
	if (event == NULL)
	{
		perror("new_event()");
		return (NULL);
	}
	event->id = event_data.id;
	event->position = event_data.position;
	event_node = ft_lstnew(event);
	if (event_node == NULL)
	{
		perror("new_event()");
		return (free(event), NULL);
	}
	return (event_node);
}