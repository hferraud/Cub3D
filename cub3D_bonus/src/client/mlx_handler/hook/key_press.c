/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 08:44:00 by edelage           #+#    #+#             */
/*   Updated: 2023/03/14 08:44:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "hook.h"

static void	change_weapon(int key_code, t_player_data *player_data);

/**
 * @brief Adds the key_code of the pressed key in the array
 * if the key should be hooked
 */
int	key_press(int key_code, t_cub *cub)
{
	const int	valid_key[MAX_KEY] = {KEY_W, KEY_A, KEY_S, KEY_D,
									   KEY_LEFT, KEY_RIGHT, KEY_SPC};
	size_t		index;

	index = 0;
	while (index < MAX_KEY)
	{
		if (key_code == valid_key[index])
			cub->mlx_data->key_press[index] = key_code;
		index++;
	}
	if (key_code == KEY_SPC)
		player_shoot(cub);
	else if (key_code == KEY_1 || key_code == KEY_2 || key_code == KEY_3)
		change_weapon(key_code, &cub->player_data);
	else if (key_code == KEY_F)
		player_door_interact(cub);
	return (0);
}

int	is_key_pressed(int key_code, t_cub *cub)
{
	size_t	index;
	int		*key_press;

	index = 0;
	key_press = cub->mlx_data->key_press;
	while (index < MAX_KEY)
	{
		if (key_code == key_press[index])
			return (1);
		index++;
	}
	return (0);
}

static void	change_weapon(int key_code, t_player_data *player_data)
{
	const int		weapon_key[] = {KEY_1, KEY_2, KEY_3};
	const t_weapon	weapon_id[] =
		{ASSAULT_RIFLE_INDEX, PISTOL_INDEX, KNIFE_INDEX};
	t_player_status	*player_status;
	size_t			count;

	count = 0;
	player_status = &player_data->player_status;
	pthread_mutex_lock(player_data->player_lock);
	while (count < NB_WEAPONS && weapon_key[count] != key_code)
		count++;
	if (count < NB_WEAPONS && player_status->weapons[weapon_id[count]] == true)
		player_status->weapon_equipped = weapon_id[count];
	pthread_mutex_unlock(player_data->player_lock);
}
