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

static int				mutexes_init(t_player_data *player_data);
static pthread_mutex_t	*mutex_init(void);
static t_player_status	player_status_init(void);
static void				player_data_set_to_default(t_player_data *player_data);

int	player_data_init(t_player_data *player_data)
{
	player_data_set_to_default(player_data);
	if (mutexes_init(player_data) == -1)
	{
		player_data_destroy(player_data);
		player_data_set_to_default(player_data);
		return (perror("player_data_init()"), -1);
	}
	player_data->player_status = player_status_init();
	return (0);
}

static int	mutexes_init(t_player_data *player_data)
{
	player_data->update_lock = mutex_init();
	if (player_data->update_lock == NULL)
		return (-1);
	player_data->player_lock = mutex_init();
	if (player_data->player_lock == NULL)
		return (-1);
	player_data->events_lock = mutex_init();
	if (player_data->events_lock == NULL)
		return (-1);
	return (0);
}

static pthread_mutex_t	*mutex_init(void)
{
	pthread_mutex_t	*mutex;

	mutex = malloc(sizeof(pthread_mutex_t));
	if (mutex == NULL)
		return (NULL);
	if (pthread_mutex_init(mutex, NULL) != 0)
	{
		free(mutex);
		return (NULL);
	}
	return (mutex);
}

static t_player_status	player_status_init(void)
{
	t_player_status	player_status;

	player_status.life = LIFE_MAX;
	player_status.weapons[KNIFE_INDEX] = true;
	player_status.weapons[PISTOL_INDEX] = false;
	player_status.weapons[ASSAULT_RIFLE_INDEX] = false;
	player_status.weapon_equipped = KNIFE_INDEX;
	player_status.ammo = AMMO_DEFAULT;
	ft_bzero(&player_status.time_last_shoot, sizeof(t_timeval));
	return (player_status);
}

static void	player_data_set_to_default(t_player_data *player_data)
{
	player_data->update = true;
	player_data->update_lock = NULL;
	player_data->player_lock = NULL;
	player_data->events = NULL;
	player_data->events_lock = NULL;
}
