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

void	player_pos_init(t_cub *cub)
{
	cub->player->pos.x = (float)(cub->map->spawn.x + 0.5);
	cub->player->pos.y = (float)(cub->map->spawn.y + 0.5);
	if (cub->map->spawn.orientation == 'S')
		cub->player->rotation = M_PI_2;
	else if (cub->map->spawn.orientation == 'N')
		cub->player->rotation = M_PI_2 * 3;
	else if (cub->map->spawn.orientation == 'E')
		cub->player->rotation = 0;
	else
		cub->player->rotation = M_PI;
}
