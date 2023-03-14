/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:26:00 by ethan             #+#    #+#             */
/*   Updated: 2023/03/14 14:26:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "player.h"
#include "mlx_handler.h"
#include "hook.h"

void	player_position_update(t_cub *cub)
{
	if (is_key_pressed(KEY_W, cub) && !is_key_pressed(KEY_S, cub))
	{
		if (cub->map.map[(int)(cub->player.y - PLAYER_MOVE - PLAYER_OFFSET)][(int) cub->player.x] == FLOOR)
			cub->player.y -= PLAYER_MOVE;
	}
	if (is_key_pressed(KEY_S, cub) && !is_key_pressed(KEY_W, cub))
	{
		if (cub->map.map[(int)(cub->player.y + PLAYER_MOVE + PLAYER_OFFSET)][(int) cub->player.x] == FLOOR)
		cub->player.y -= PLAYER_MOVE;
	}
}
