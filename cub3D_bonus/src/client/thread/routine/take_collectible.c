/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_collectible.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 20:39:00 by edelage           #+#    #+#             */
/*   Updated: 2023/05/07 20:39:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "cub.h"
#include "player_data.h"

typedef void	(*t_take_function)(t_player_status *player_status);

void	take_collectible(char cell, t_player_data *player_data)
{
	const t_collectible_id	collectible_id[]
		= {MEDIC_KIT_ID, AMMO_ID, PISTOL_ID, ASSAULT_RIFFLE_ID};
	const t_take_function	take_function[]
		= {take_medic_kit, take_ammo, take_pistol, take_assault_riffle};
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

void	take_medic_kit(t_player_status *player_status)
{
	player_status->life += MEDIC_LIFE;
	if (player_status->life > LIFE_MAX)
		player_status->life = LIFE_MAX;
}

void	take_ammo(t_player_status *player_status)
{
	player_status->ammo += AMMO_PACK;
	if (player_status->ammo > AMMO_MAX)
		player_status->ammo = AMMO_MAX;
}

void	take_pistol(t_player_status *player_status)
{
	if (!player_status->weapons[PISTOL_INDEX])
	{
		player_status->weapons[PISTOL_INDEX] = true;
		if (player_status->weapons[ASSAULT_RIFLE_INDEX] == false)
			player_status->weapon_equipped = PISTOL_INDEX;
	}
	else
		take_ammo(player_status);
}

void	take_assault_riffle(t_player_status *player_status)
{
	if (!player_status->weapons[ASSAULT_RIFLE_INDEX])
	{
		player_status->weapons[ASSAULT_RIFLE_INDEX] = true;
		player_status->weapon_equipped = ASSAULT_RIFLE_INDEX;
	}
	else
		take_ammo(player_status);
}
