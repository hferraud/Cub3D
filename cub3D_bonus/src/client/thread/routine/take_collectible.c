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
#include "player_data.h"

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
		player_status->weapons[PISTOL_INDEX] = true;
	else
		take_ammo(player_status);
}

void	take_assault_riffle(t_player_status *player_status)
{
	if (!player_status->weapons[ASSAULT_RIFLE_INDEX])
		player_status->weapons[ASSAULT_RIFLE_INDEX] = true;
	else
		take_ammo(player_status);
}
