/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_shoot.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 21:19:00 by hferraud          #+#    #+#             */
/*   Updated: 2023/05/07 21:19:00 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "cub.h"
#include "draw.h"
#include "weapons_data.h"
#include "event.h"
#include <sys/time.h>

size_t			elapsed_time(struct timeval start_time,
					struct timeval current_time);

static t_damage	get_damage_by_weapon(t_weapon weapon);
static bool		can_shoot(t_cub *cub, t_weapon weapon, t_timeval current_time);
static bool		aim_enemy(t_cub *cub, t_weapon weapon, t_enemy enemy);

void	player_shoot(t_cub *cub)
{
	t_enemy			enemies[PLAYER_LIMIT - 1];
	t_player		player;
	t_weapon		weapon;
	size_t			i;
	t_timeval		current_time;

	gettimeofday(&current_time, NULL);
	pthread_mutex_lock(cub->player_data.player_lock);
	player = cub->player_data.player;
	weapon = cub->player_data.player_status.weapon_equipped;
	if (!can_shoot(cub, weapon, current_time))
	{
		pthread_mutex_unlock(cub->player_data.player_lock);
		return ;
	}
	cub->player_data.player_status.time_last_shoot = current_time;
	cub->player_data.player_status.frame_since_last_shoot = 0;
	if (weapon != KNIFE_INDEX)
		cub->player_data.player_status.ammo--;
	pthread_mutex_unlock(cub->player_data.player_lock);
	enemies_set_dist(cub, enemies, player);
	i = 0;
	while (i < PLAYER_LIMIT - 1)
	{
		if (enemies[i].id != -1)
		{
			if (aim_enemy(cub, weapon, enemies[i]))
			{
				add_damage_event(cub, enemies[i].id,
					get_damage_by_weapon(weapon));
				printf("Hit: %d damage\n", get_damage_by_weapon(weapon));
			}
			else
				printf("Miss\n");
		}
		i++;
	}
}

static t_damage	get_damage_by_weapon(t_weapon weapon)
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

static bool	can_shoot(t_cub *cub, t_weapon weapon, t_timeval current_time)
{
	const t_rate_fire	rate_fire[]
		= {KNIFE_RATE_FIRE, PISTOL_RATE_FIRE, ASSAULT_RIFFLE_RATE_FIRE};
	struct timeval		last_shot;

	last_shot = cub->player_data.player_status.time_last_shoot;
	if (weapon != KNIFE_INDEX && cub->player_data.player_status.ammo <= 0)
		return (false);
	if (elapsed_time(last_shot, current_time)
		< (size_t)(60.f / rate_fire[weapon] * 1000000))
		return (false);
	return (true);
}

static bool	aim_enemy(t_cub *cub, t_weapon weapon, t_enemy enemy)
{
	t_fvector		camera;
	t_draw_param	dp;

	camera = enemy_camera_projection(cub, enemy);
	if (camera.y > cub->z_buffer[WIN_WIDTH / 2])
		return (false);
	if (weapon == KNIFE_INDEX && camera.y > KNIFE_RANGE)
		return (false);
	dp = enemy_get_draw_param(cub, camera);
	return (dp.screen.x < WIN_WIDTH / 2 + dp.width / 2
		&& dp.screen.x > WIN_WIDTH / 2 - dp.width / 2);
}

void	check_assault_riffle_shoot(t_cub *cub)
{
	t_timeval		current_time;
	t_player_data	*player_data;

	if (!is_key_pressed(KEY_SPC, cub))
		return ;
	player_data = &cub->player_data;
	pthread_mutex_lock(player_data->player_lock);
	gettimeofday(&current_time, NULL);
	if (player_data->player_status.weapon_equipped == ASSAULT_RIFLE_INDEX)
	{
		pthread_mutex_unlock(player_data->player_lock);
		player_shoot(cub);
	}
	else
		pthread_mutex_unlock(player_data->player_lock);
}
