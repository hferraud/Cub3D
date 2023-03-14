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
#include <math.h>
#include "mlx_handler.h"

void	init_player_position(t_cub *cub)
{
	cub->player.x = (float) cub->map.spawn.x;
	cub->player.y = (float) cub->map.spawn.y;
	if (cub->map.spawn.orientation == 'N')
		cub->player.rotation = M_PI_2;
	else if (cub->map.spawn.orientation == 'S')
		cub->player.rotation = M_PI_2 * 3;
	else if (cub->map.spawn.orientation == 'E')
		cub->player.rotation = 0;
	else
		cub->player.rotation = M_PI;
}
