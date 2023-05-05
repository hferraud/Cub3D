/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_response.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 00:12:00 by edelage           #+#    #+#             */
/*   Updated: 2023/05/04 00:12:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "cub.h"

static t_players	*search_player_by_id(int id, t_players *players);

int send_response(int server_socket, t_cub *cub)
{
	int			id;
	t_player	new_position;
	t_players	*player;

	if (read(server_socket, &id, sizeof(int)) <= 0
		|| read(server_socket, &new_position, sizeof(t_player)) <= 0)
		return (cub_error(CLIENT_LOST));
	pthread_mutex_lock(cub->players_lock);
	player = search_player_by_id(id, cub->players);
	if (player->id == -1)
		player->id = id;
	player->player = new_position;
	printf("Player %d position: x: %f y: %f\n", id, new_position.pos.x, new_position.pos.y);
	printf("Player %d rotation: x: %f y: %f\n", id, new_position.rotation.x, new_position.rotation.y);
	pthread_mutex_unlock(cub->players_lock);
	return (0);
}

static t_players	*search_player_by_id(int id, t_players *players)
{
	size_t		count;
	t_players	*player;

	count = 0;
	player = NULL;
	while (count < PLAYER_LIMIT - 1)
	{
		if (players[count].id == id || (player == NULL && players[count].id == -1))
			player = &players[count];
		count++;
	}
	return (player);
}