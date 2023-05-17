/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:59:00 by ethan             #+#    #+#             */
/*   Updated: 2023/05/08 17:59:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "cub.h"
#include "weapons_data.h"

static void	add_event(t_cub *cub, t_event event_data)
{
	t_list	*event_node;

	event_node = new_event(event_data);
	if (event_node == NULL)
	{
		perror("add_collectible_event()");
		cub_exit(cub);
	}
	pthread_mutex_lock(cub->player_data.events_lock);
	ft_lstadd_front(&cub->player_data.events, event_node);
	pthread_mutex_unlock(cub->player_data.events_lock);
	pthread_mutex_lock(cub->player_data.update_lock);
	cub->player_data.update = true;
	pthread_mutex_unlock(cub->player_data.update_lock);
}

void	add_collectible_event(t_cub *cub)
{
	t_event				event;
	t_collectible_data	*collectible_data;

	collectible_data = &cub->map.collectible_data;
	pthread_mutex_lock(collectible_data->collectible_lock);
	collectible_data->size--;
	event.position.x
		= (int)collectible_data->collectible[collectible_data->size].pos.x;
	event.position.y
		= (int)collectible_data->collectible[collectible_data->size].pos.y;
	pthread_mutex_unlock(collectible_data->collectible_lock);
	event.id = EVENT_TAKE_COLLECTIBLE;
	add_event(cub, event);
}

void	add_door_event(t_cub *cub, t_vector map_pos, char door_state)
{
	t_event	event;

	if (door_state == DOOR_OPEN)
		event.id = EVENT_OPEN_DOOR;
	else
		event.id = EVENT_CLOSE_DOOR;
	event.position.x = map_pos.x;
	event.position.y = map_pos.y;
	add_event(cub, event);
}

void	add_damage_event(t_cub *cub, int enemy_id, t_damage damage)
{
	t_event	event;

	event.id = EVENT_DAMAGE;
	event.enemy_id = enemy_id;
	event.damage = damage;
	add_event(cub, event);
}
