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

size_t	diff_time(struct timeval start_time, struct timeval current_time);

static t_damage get_damage_by_weapon(t_weapon weapon);
static int		can_shoot(t_weapon weapon, t_timeval time_last_shoot, t_timeval current_time);

void	player_shoot(t_cub *cub)
{
	t_enemy			enemies[PLAYER_LIMIT - 1];
	t_player		player;
	t_player_status	player_status;
	t_fvector		camera;
	t_draw_param	dp;
	size_t			i;
	t_timeval		current_time;

	gettimeofday(&current_time, NULL);
	pthread_mutex_lock(cub->player_data.player_lock);
	if (!can_shoot(cub->player_data.player_status.weapon_equipped, cub->player_data.player_status.time_last_shoot, current_time))
	{
		pthread_mutex_unlock(cub->player_data.player_lock);
		return ;
	}
	if (cub->player_data.player_status.ammo == 0 && cub->player_data.player_status.weapon_equipped != KNIFE_INDEX)
	{
		pthread_mutex_unlock(cub->player_data.player_lock);
		printf("No ammo\n");
		return ;
	}
	cub->player_data.player_status.time_last_shoot = current_time;
	cub->player_data.player_status.frame_since_last_shoot = 0;
	if (cub->player_data.player_status.weapon_equipped != KNIFE_INDEX)
		cub->player_data.player_status.ammo--;
	player = cub->player_data.player;
	player_status = cub->player_data.player_status;
	pthread_mutex_unlock(cub->player_data.player_lock);
	enemies_set_dist(cub, enemies, player);
	i = 0;
	while (i < PLAYER_LIMIT - 1)
	{
		if (enemies[i].id != -1)
		{
			camera = enemy_camera_projection(cub, enemies[i]);
			dp = enemy_get_draw_param(cub, camera);
			if (dp.screen.x < WIN_WIDTH / 2 + dp.width / 2
				&& dp.screen.x > WIN_WIDTH / 2 - dp.width / 2)
			{
				add_damage_event(cub, enemies[i].id,
					get_damage_by_weapon(player_status.weapon_equipped));
				printf("Hit: %d damage\n", get_damage_by_weapon(player_status.weapon_equipped));
			}
			else
				printf("Miss\n");
		}
		i++;
	}
}

static t_damage get_damage_by_weapon(t_weapon weapon)
{
	const t_weapon		weapon_index[] =
		{KNIFE_INDEX, PISTOL_INDEX,ASSAULT_RIFLE_INDEX};
	const t_damage		damage[] =
		{KNIFE_DAMAGE, PISTOL_DAMAGE, ASSAULT_RIFFLE_DAMAGE};
	size_t	count;

	count = 0;
	while (count < NB_WEAPONS)
	{
		if (weapon == weapon_index[count])
			return (damage[count]);
		count++;
	}
	return (0);
}

static int	can_shoot(t_weapon weapon, t_timeval time_last_shoot, t_timeval current_time)
{
	const t_weapon		weapon_index[] =
			{KNIFE_INDEX, PISTOL_INDEX,ASSAULT_RIFLE_INDEX};
	const t_rate_fire	rate_fire[] =
			{KNIFE_RATE_FIRE, PISTOL_RATE_FIRE, ASSAULT_RIFFLE_RATE_FIRE};
	size_t	count;

	count = 0;
	while (count < NB_WEAPONS)
	{
		if (weapon == weapon_index[count]
			&& diff_time(time_last_shoot, current_time)
			>= (size_t)(60.f / rate_fire[count] * 1000000))
			return (1);
		count++;
	}
	return (0);
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
