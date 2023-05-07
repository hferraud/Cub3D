/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_event.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 19:07:00 by edelage           #+#    #+#             */
/*   Updated: 2023/05/07 19:07:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "cub.h"
#include "player_data.h"

void	take_collectible(char cell, t_player_data *player_data);

int send_take_collectible_event(int server_socket, t_event event,
		t_player_data *player_data)
{
	char	buf;

	if (write(server_socket, &event.position, sizeof(t_vector)) == -1
		|| read(server_socket, &buf, sizeof(char)) <= 0)
		return (-1);
	if (buf != *CANT_TAKE)
		take_collectible(buf, player_data);
	return (0);
}

typedef void	(*t_take_function)(t_player_status *player_status);

void	take_collectible(char cell, t_player_data *player_data)
{
	const t_collectible_id	collectible_id[] = {MEDIC_KIT_ID, AMMO_ID, PISTOL_ID, ASSAULT_RIFFLE_ID};
	const t_take_function	take_function[] = {take_medic_kit, take_ammo, take_pistol, take_assault_riffle};
	t_collectible_id		id;
	size_t					index;

	index = 0;
	id = collectible_id_get(cell);
	pthread_mutex_lock(player_data->player_lock);
	while (id != collectible_id[index])
		index++;
	take_function[index](&player_data->player_status);
	pthread_mutex_unlock(player_data->player_lock);
}