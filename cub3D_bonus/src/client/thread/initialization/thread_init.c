/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 19:21:00 by edelage           #+#    #+#             */
/*   Updated: 2023/05/02 19:21:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "cub.h"

void		routine(t_cub *cub);
static int	players_init(t_cub *cub);

/**
 * @brief Initialize data and create thread for data transfers
 * @return 0 on success, -1 otherwise
 */
int	thread_init(t_cub *cub)
{
	if (player_data_init(&cub->player_data) == -1)
		return (-1);
	if (players_init(cub) == -1)
	{
		player_data_destroy(&cub->player_data);
		return (-1);
	}
	if (pthread_create(&cub->thread, NULL, (void *) routine, cub) != 0)
	{
		player_data_destroy(&cub->player_data);
		return (-1);
	}
	return (0);
}

static int players_init(t_cub *cub)
{
	size_t	count;

	cub->players_lock = malloc(sizeof(pthread_mutex_t));
	if (cub->players_lock == NULL)
		return (-1);
	if (pthread_mutex_init(cub->players_lock, NULL) != 0)
	{
		free(cub->players_lock);
		cub->players_lock = NULL;
		return (-1);
	}
	count = 0;
	while (count < PLAYER_LIMIT - 1)
	{
		cub->enemies[count].id = -1;
		count++;
	}
	return (0);
}