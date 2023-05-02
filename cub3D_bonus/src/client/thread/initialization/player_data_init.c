/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_data_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 19:24:00 by edelage           #+#    #+#             */
/*   Updated: 2023/05/02 19:24:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "player_data.h"

int	player_data_init(t_player_data *player_data)
{
	return (0);
}

static int	mutexes_init(t_player_data *player_data)
{
	player_data->update_lock = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
	if (player_data->update_lock == NULL)
		return (-1);
	if (pthread_mutex_init(player_data->update_lock, NULL) != 0)
	{
		free(player_data->update_lock);
		player_data->update_lock = NULL;
		return (-1);
	}
	player_data->player_lock = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
	if (player_data->player_lock == NULL)
		return (-1);
	if (pthread_mutex_init(player_data->player_lock, NULL) != 0)
	{
		free(player_data->player_lock);
		player_data->player_lock = NULL;
		return (-1);
	}
	return (0);
}