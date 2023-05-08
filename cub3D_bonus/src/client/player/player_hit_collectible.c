/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_hit_collectible.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 13:58:00 by edelage           #+#    #+#             */
/*   Updated: 2023/05/07 13:58:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "cub.h"
#include "player.h"

void	add_event_take_collectible(t_cub *cub)
{
	t_list				*event_node;
	t_event				*event;
	t_collectible_data	*collectible_data;

	collectible_data = &cub->map.collectible_data;
	collectible_data->size--;
	event = malloc(sizeof(t_event));
	if (event == NULL)
	{
		perror("add_event_take_collectible()");
		cub_exit(cub);
	}
	event->id = EVENT_TAKE_COLLECTIBLE;
	event->position.x = (int) collectible_data->collectible[collectible_data->size].pos.x;
	event->position.y = (int) collectible_data->collectible[collectible_data->size].pos.y;
	event_node = ft_lstnew(event);
	if (event_node == NULL)
	{
		perror("add_event_take_collectible()");
		free(event);
		cub_exit(cub);
	}
	pthread_mutex_lock(cub->player_data.events_lock);
	ft_lstadd_front(&cub->player_data.events, event_node);
	pthread_mutex_unlock(cub->player_data.events_lock);
}

/**
 * @return 1 if the player touches a collectible, 0 otherwise
 */
int	player_hit_collectible(t_cub *cub)
{
	t_collectible_data	collectible_data;
	t_collectible		nearest_collectible;
	t_player			player;
	float				dist;

	collectible_data = cub->map.collectible_data;
	if (collectible_data.size == 0)
		return (0);
	nearest_collectible = collectible_data.collectible[collectible_data.size - 1];
	player = cub->player_data.player;
	dist = sqrtf(
			powf(nearest_collectible.pos.x - player.pos.x, 2)
			+ powf(nearest_collectible.pos.y - player.pos.y, 2)
			);
	return (dist < (PLAYER_OFFSET + COLLECTIBLE_OFFSET));
}
