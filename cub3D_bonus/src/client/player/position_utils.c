/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 17:24:00 by edelage           #+#    #+#             */
/*   Updated: 2023/05/06 17:24:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "cub.h"
#include "player.h"

t_fvector	new_position_calculate(t_cub *cub)
{
	t_fvector	new_pos;
	t_fvector	rotation;

	new_pos = cub->player_data.player.pos;
	rotation = cub->player_data.player.rotation;
	if (is_key_pressed(KEY_W, cub))
		new_pos = fvector_add(new_pos, fvector_mul(rotation, PLAYER_MOVE));
	if (is_key_pressed(KEY_S, cub))
	{
		rotation = fvector_rotate(rotation, M_PI);
		new_pos = fvector_add(new_pos, fvector_mul(rotation, PLAYER_MOVE));
	}
	rotation = cub->player_data.player.rotation;
	if (is_key_pressed(KEY_D, cub))
	{
		rotation = fvector_rotate(rotation, M_PI_2);
		new_pos = fvector_add(new_pos, fvector_mul(rotation, PLAYER_MOVE));
	}
	rotation = cub->player_data.player.rotation;
	if (is_key_pressed(KEY_A, cub))
	{
		rotation = fvector_rotate(rotation, -M_PI_2);
		new_pos = fvector_add(new_pos, fvector_mul(rotation, PLAYER_MOVE));
	}
	return (new_pos);
}

int	is_valid_position(t_cub *cub, float x, float y)
{
	char	**map;

	map = cub->map.map;
	return (is_floor(map[(int)(y - PLAYER_OFFSET)][(int)(x - PLAYER_OFFSET)])
			&& is_floor(map[(int)(y - PLAYER_OFFSET)][(int)(x + PLAYER_OFFSET)])
			&& is_floor(map[(int)(y + PLAYER_OFFSET)][(int)(x + PLAYER_OFFSET)])
			&& is_floor(map[(int)(y + PLAYER_OFFSET)][(int)(x - PLAYER_OFFSET)]));
}

int	player_moved(t_player before, t_player current)
{
	return (before.pos.x != current.pos.x
			|| before.pos.y != current.pos.y
			|| before.rotation.x != current.rotation.x
			|| before.rotation.y != current.rotation.y);
}

int is_floor(char cell)
{
	return (cell == FLOOR || cell == DOOR_OPEN);
}