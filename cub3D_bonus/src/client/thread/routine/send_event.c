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

int	send_door_event(int server_socket, t_event event)
{
	if (write(server_socket, &event.position, sizeof(t_vector)) == -1)
		return (-1);
	return (0);
}

int	send_collectible_event(int server_socket, t_event event,
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

int	send_damage_event(int server_socket, t_event event)
{
	if (write(server_socket, &event.enemy_id, sizeof(int)) == -1
		|| write(server_socket, &event.damage, sizeof(t_damage)) == -1)
		return (-1);
	return (0);
}
