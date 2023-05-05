/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   players_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:28:00 by edelage           #+#    #+#             */
/*   Updated: 2023/05/01 15:28:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "server_data.h"

int	players_init(t_players *players, int nb_spawn)
{
	int	count;

	ft_bzero(players, sizeof(t_players));
	players->players_socket = (int *) malloc(sizeof(int) * nb_spawn);
	if (players->players_socket == NULL)
		return (-1);
	count = 0;
	while (count < nb_spawn)
	{
		players->players_socket[count] = -1;
		count++;
	}
	players->players_lock = malloc(sizeof(pthread_mutex_t));
	if (players->players_lock == NULL)
		return (-1);
	if (pthread_mutex_init(players->players_lock, NULL) != 0)
	{
		free(players->players_lock);
		players->players_lock = NULL;
		return (-1);
	}
	players->size = nb_spawn;
	return (0);
}
