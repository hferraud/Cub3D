/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_shoot_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 22:50:00 by edelage           #+#    #+#             */
/*   Updated: 2023/05/13 22:50:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "cub.h"

size_t	elapsed_time(t_timeval start_time, t_timeval current_time);

t_damage	get_damage_by_weapon(t_weapon weapon)
{
	const t_weapon	weapon_index[]
		= {KNIFE_INDEX, PISTOL_INDEX, ASSAULT_RIFLE_INDEX};
	const t_damage	damage[]
		= {KNIFE_DAMAGE, PISTOL_DAMAGE, ASSAULT_RIFFLE_DAMAGE};
	size_t			count;

	count = 0;
	while (count < NB_WEAPONS)
	{
		if (weapon == weapon_index[count])
			return (damage[count]);
		count++;
	}
	return (0);
}

bool	can_shoot(t_cub *cub, t_weapon weapon, t_timeval current_time)
{
	const t_rate_fire	rate_fire[]
		= {KNIFE_RATE_FIRE, PISTOL_RATE_FIRE, ASSAULT_RIFFLE_RATE_FIRE};
	struct timeval		last_shot;
	t_player			player;

	player = cub->player_data.player;
	if (player.pos.x == cub->map.spawn.x + 0.5f
		&& player.pos.y == cub->map.spawn.y + 0.5f)
		return (false);
	last_shot = cub->player_data.player_status.time_last_shoot;
	if (weapon != KNIFE_INDEX && cub->player_data.player_status.ammo <= 0)
		return (false);
	if (elapsed_time(last_shot, current_time)
		< (size_t)(60.f / rate_fire[weapon] * 1000000))
		return (false);
	return (true);
}
