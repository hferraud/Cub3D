/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_data_destroy.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 23:58:00 by edelage           #+#    #+#             */
/*   Updated: 2023/05/02 23:58:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "player_data.h"

static void	destroy_mutex(pthread_mutex_t *mutex);

void	player_data_destroy(t_player_data *player_data)
{
	if (player_data->update_lock)
		destroy_mutex(player_data->update_lock);
	if (player_data->player_lock)
		destroy_mutex(player_data->player_lock);
	if (player_data->events_lock)
		destroy_mutex(player_data->events_lock);
	ft_lstclear(&player_data->events, free);
}

static void	destroy_mutex(pthread_mutex_t *mutex)
{
	pthread_mutex_destroy(mutex);
	free(mutex);
}
