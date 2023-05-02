/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player_pos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:15:00 by ethan             #+#    #+#             */
/*   Updated: 2023/03/14 14:15:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "mlx_handler.h"

/**
 * @brief Set the position player to the spawn point
 */
void	player_pos_init(t_cub *cub)
{
	cub->player_data.player.pos.x = (float)(cub->map.spawn.x + 0.5);
	cub->player_data.player.pos.y = (float)(cub->map.spawn.y + 0.5);
	if (cub->map.spawn.orientation == 'N')
		cub->player_data.player.rotation = fvector_init(0, 1);
	else if (cub->map.spawn.orientation == 'S')
		cub->player_data.player.rotation = fvector_init(0, -1);
	else if (cub->map.spawn.orientation == 'E')
		cub->player_data.player.rotation = fvector_init(1, 0);
	else
		cub->player_data.player.rotation = fvector_init(-1, 0);
}
