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
#include "hook.h"
#include "player.h"

static void	player_position_update(t_cub *cub);
static void	player_rotation_update(t_cub *cub);

void	player_update(t_cub *cub)
{
	player_rotation_update(cub);
	player_position_update(cub);
}

static void	player_position_update(t_cub *cub)
{
	t_player	*player;

	player = cub->player;
	if (is_key_pressed(KEY_S, cub))
	{
		player->x -= cosf(player->rotation) * PLAYER_MOVE;
		player->y -= sinf(player->rotation) * PLAYER_MOVE;
	}
	if (is_key_pressed(KEY_W, cub))
	{
		player->x += cosf(player->rotation) * PLAYER_MOVE;
		player->y += sinf(player->rotation) * PLAYER_MOVE;
	}
	if (is_key_pressed(KEY_D, cub))
	{
		player->x += cosf(player->rotation + M_PI_2) * PLAYER_MOVE;
		player->y += sinf(player->rotation + M_PI_2) * PLAYER_MOVE;
	}
	if (is_key_pressed(KEY_A, cub))
	{
		player->x += cosf(player->rotation - M_PI_2) * PLAYER_MOVE;
		player->y += sinf(player->rotation - M_PI_2) * PLAYER_MOVE;
	}
}

static void	player_rotation_update(t_cub *cub)
{
	if (is_key_pressed(KEY_LEFT, cub))
		cub->player->rotation -= (float) PLAYER_ROTATION;
	if (is_key_pressed(KEY_RIGHT, cub))
		cub->player->rotation += (float) PLAYER_ROTATION;
	if (cub->player->rotation > (2 * M_PI))
		cub->player->rotation -= (float) (2 * M_PI);
}
