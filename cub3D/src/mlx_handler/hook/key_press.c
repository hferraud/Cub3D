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

static void	add_key_press(int key_code, t_cub *cub);

/**
 * @brief Adds the key_code of the pressed key in the array
 * if the key should be hooked
 */
int	key_press(int key_code, t_cub *cub)
{
	add_key_press(key_code, cub);
	return (0);
}

static void	add_key_press(int key_code, t_cub *cub)
{
	const int	valid_key[MAX_KEY] = {KEY_W, KEY_A, KEY_S, KEY_D,
		KEY_LEFT, KEY_RIGHT};
	size_t		index;

	index = 0;
	while (index < MAX_KEY)
	{
		if (key_code == valid_key[index])
			cub->mlx_data->key_press[index] = key_code;
		index++;
	}
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