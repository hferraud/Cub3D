/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_data.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:55:00 by edelage           #+#    #+#             */
/*   Updated: 2023/05/02 14:55:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef PLAYER_DATA_H
# define PLAYER_DATA_H

# include "event.h"
# include "player.h"
# include "libft.h"
# include "weapons_data.h"
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>

# define LIFE_MAX		100
# define AMMO_DEFAULT	30
# define AMMO_MAX		120
# define MEDIC_LIFE		50
# define AMMO_PACK		60

typedef struct s_player_data	t_player_data;
typedef struct s_player_status	t_player_status;
typedef enum e_weapon			t_weapon;
typedef struct timeval			t_timeval;

enum e_weapon
{
	KNIFE_INDEX,
	PISTOL_INDEX,
	ASSAULT_RIFLE_INDEX,
};

struct s_player_status
{
	int			life;
	t_weapon	weapon_equipped;
	bool		weapons[NB_WEAPONS];
	int			ammo;
	t_timeval	time_last_shoot;
};

struct s_player_data
{
	bool			update;
	pthread_mutex_t	*update_lock;
	t_player		player;
	t_player_status	player_status;
	t_fvector		camera;
	pthread_mutex_t	*player_lock;
	t_list			*events;
	pthread_mutex_t	*events_lock;
};

int		thread_init(t_cub *cub);
int		player_data_init(t_player_data *player_data);
void	player_data_destroy(t_player_data *player_data);
int		listening_response(int server_socket, t_player_data *player_data);
int		send_collectible_event(int server_socket, t_event event,
			t_player_data *player_data);
int		send_door_event(int server_socket, t_event event);
int		send_damage_event(int server_socket, t_event event);
int		send_response(int server_socket, t_cub *cub);
int		event_response(int server_socket, t_cub *cub);

void	take_collectible(char cell, t_player_data *player_data);
void	take_medic_kit(t_player_status *player_status);
void	take_ammo(t_player_status *player_status);
void	take_pistol(t_player_status *player_status);
void	take_assault_riffle(t_player_status *player_status);

#endif
