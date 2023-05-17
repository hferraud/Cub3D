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

t_damage		get_damage_by_weapon(t_weapon weapon);
bool			can_shoot(t_cub *cub, t_weapon weapon, t_timeval current_time);

static void		shoot_at_enemies(t_cub *cub, t_weapon weapon, t_enemy *enemies);
static void		shoot_at_enemy(t_cub *cub, t_weapon weapon, t_enemy enemy);
static bool		aim_enemy(t_cub *cub, t_weapon weapon, t_enemy enemy);

void	player_shoot(t_cub *cub)
{
	t_enemy			enemies[PLAYER_LIMIT - 1];
	t_player		player;
	t_weapon		weapon;
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
	cub->player_data.player_status.time_last_shot = current_time;
	cub->player_data.player_status.frame_since_last_shot = 0;
	if (weapon != KNIFE_INDEX)
		cub->player_data.player_status.ammo--;
	enemies_set_dist(cub, enemies, player);
	shoot_at_enemies(cub, weapon, enemies);
	pthread_mutex_unlock(cub->player_data.player_lock);
}

static void	shoot_at_enemies(t_cub *cub, t_weapon weapon, t_enemy *enemies)
{
	size_t	i;

	i = 0;
	while (i < PLAYER_LIMIT - 1)
	{
		if (enemies[i].id != -1)
			shoot_at_enemy(cub, weapon, enemies[i]);
		i++;
	}
}

static void	shoot_at_enemy(t_cub *cub, t_weapon weapon, t_enemy enemy)
{
	if (aim_enemy(cub, weapon, enemy))
	{
		add_damage_event(cub, enemy.id,
			get_damage_by_weapon(weapon));
		printf("Hit: %d damage\n", get_damage_by_weapon(weapon));
		cub->player_data.player_status.last_shot_hit = true;
	}
	else
	{
		printf("Miss\n");
		cub->player_data.player_status.last_shot_hit = false;
	}
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
	t_player_data	*player_data;

	if (!is_key_pressed(KEY_SPC, cub))
		return ;
	player_data = &cub->player_data;
	pthread_mutex_lock(player_data->player_lock);
	if (player_data->player_status.weapon_equipped == ASSAULT_RIFLE_INDEX)
	{
		pthread_mutex_unlock(player_data->player_lock);
		player_shoot(cub);
	}
	else
		pthread_mutex_unlock(player_data->player_lock);
}
