/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 07:52:00 by hferraud          #+#    #+#             */
/*   Updated: 2023/05/16 07:52:00 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include"cub.h"

int	is_valid_position(t_cub *cub, float x, float y)
{
	char	**map;

	map = cub->map->map;
	return (map[(int)(y - PLAYER_OFFSET)][(int)(x - PLAYER_OFFSET)] == FLOOR
			&& map[(int)(y - PLAYER_OFFSET)][(int)(x + PLAYER_OFFSET)] == FLOOR
			&& map[(int)(y + PLAYER_OFFSET)][(int)(x + PLAYER_OFFSET)] == FLOOR
			&& map[(int)(y + PLAYER_OFFSET)][(int)(x - PLAYER_OFFSET)] == FLOOR
			);
}
