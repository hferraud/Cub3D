/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_release.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 08:46:00 by edelage           #+#    #+#             */
/*   Updated: 2023/03/14 08:46:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "hook.h"

static void	add_key_release(int key_code, t_cub *cub);

int	key_release(int key_code, t_cub *cub)
{
	if (key_code == KEY_ESC)
		cub_exit(cub);
	else
		add_key_release(key_code, cub);
	return (0);
}

static void	add_key_release(int key_code, t_cub *cub)
{
	size_t	index;

	index = 0;
	while (index < MAX_KEY)
	{
		if (key_code == cub->mlx_data->key_press[index])
			cub->mlx_data->key_press[index] = -1;
		index++;
	}
}
