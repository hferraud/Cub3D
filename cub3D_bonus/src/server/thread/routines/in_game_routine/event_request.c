/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_request.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 01:41:00 by ethan             #+#    #+#             */
/*   Updated: 2023/05/08 01:41:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "define.h"
#include "event.h"

int	event_request(int client_socket, t_event event)
{
	if (write(client_socket, EVENT_REQUEST, LENGTH_REQUEST) == -1
		|| write(client_socket, &event.id, sizeof(t_event_id)) == -1)
		return (-1);
	if (event.id == EVENT_DAMAGE)
	{
		if (write(client_socket, &event.damage, sizeof(t_damage)) == -1)
			return (-1);
	}
	else if (write(client_socket, &event.position, sizeof(t_vector)) == -1)
		return (-1);
	return (0);
}
