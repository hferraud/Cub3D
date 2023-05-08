/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_response.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 01:56:00 by ethan             #+#    #+#             */
/*   Updated: 2023/05/08 01:56:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "cub.h"
#include "player_data.h"

static void	process_event(t_event event, t_cub *cub);
static void	process_event_collectible(t_vector position, t_cub *cub);

int event_response(int server_socket, t_cub *cub)
{
	t_event	event;

	if (read(server_socket, &event.id, sizeof(t_event_id)) <= 0)
		return (-1);
	if (event.id != EVENT_DEATH
		&& read(server_socket, &event.position, sizeof(t_vector)) <= 0)
		return (-1);
	process_event(event, cub);
	return (0);
}

static void	process_event(t_event event, t_cub *cub)
{
	if (event.id == EVENT_TAKE_COLLECTIBLE)
		process_event_collectible(event.position, cub);
}

static void	process_event_collectible(t_vector position, t_cub *cub)
{
	size_t				index;
	t_collectible_data	collectible_data;

	index = 0;
	collectible_data = cub->map.collectible_data;
	while (index < collectible_data.size
		&& ((int) collectible_data.collectible[index].pos.x != position.x
		|| (int) collectible_data.collectible[index].pos.y != position.y))
		index++;
	if (index == collectible_data.size)
		return ;
	if (index < collectible_data.size - 1)
		collectible_data.collectible[index]
		= collectible_data.collectible[collectible_data.size - 1];
	collectible_data.size--;
}

//TODO: do process_event for door and death
