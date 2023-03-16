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

static void		player_rotation_update(t_cub *cub);
static void		player_position_update(t_cub *cub);
static t_pos	new_position_calculate(t_cub *cub);
static int		is_valid_position(t_cub *cub, float x, float y);

void	player_update(t_cub *cub)
{
	player_rotation_update(cub);
	player_position_update(cub);
}

static void	player_rotation_update(t_cub *cub)
{
	if (is_key_pressed(KEY_LEFT, cub))
		cub->player->rotation -= (float) PLAYER_ROTATION;
	if (is_key_pressed(KEY_RIGHT, cub))
		cub->player->rotation += (float) PLAYER_ROTATION;
	if (cub->player->rotation > (2 * M_PI))
		cub->player->rotation -= (float) (2 * M_PI);
	else if (cub->player->rotation < 0)
		cub->player->rotation += 2 * M_PI;
}

static void	player_position_update(t_cub *cub)
{
	t_player	*player;
	t_pos		new_pos;
	char 		**map;

	player = cub->player;
	map = cub->map->map;
	new_pos = new_position_calculate(cub);
	if (is_valid_position(cub, new_pos.x, new_pos.y))
		player->pos = new_pos;
	else
	{
		if (map[(int)(new_pos.y - PLAYER_OFFSET)][(int) new_pos.x] == FLOOR
			&& map[(int)(new_pos.y + PLAYER_OFFSET)][(int) new_pos.x] == FLOOR
			&& is_valid_position(cub, player->pos.x, new_pos.y))
		{
			player->pos.y = new_pos.y;
			if (new_pos.x > player->pos.x)
				player->pos.x =	1. - UNCERTAINTY - PLAYER_OFFSET + ((int) player->pos.x);
			else
				player->pos.x =	PLAYER_OFFSET + UNCERTAINTY + ((int) player->pos.x);
		}
		else if (map[(int) new_pos.y][(int)(new_pos.x + PLAYER_OFFSET)] == FLOOR
			&& map[(int)new_pos.y][(int)(new_pos.x - PLAYER_OFFSET)] == FLOOR
			&& is_valid_position(cub, new_pos.x, player->pos.y))
		{
			player->pos.x = new_pos.x;
			if (new_pos.y > player->pos.y)
				player->pos.y =	1. - UNCERTAINTY - PLAYER_OFFSET + ((int) player->pos.y);
			else
				player->pos.y =	PLAYER_OFFSET + UNCERTAINTY + ((int) player->pos.y);
		}
	}
}

static t_pos	new_position_calculate(t_cub *cub)
{
	t_player	*player;
	t_pos	new_pos;

	player = cub->player;
	new_pos.x = player->pos.x;
	new_pos.y = player->pos.y;
	if (is_key_pressed(KEY_S, cub))
	{
		new_pos.x -= cosf(player->rotation) * PLAYER_MOVE;
		new_pos.y -= sinf(player->rotation) * PLAYER_MOVE;
	}
	if (is_key_pressed(KEY_W, cub))
	{
		new_pos.x += cosf(player->rotation) * PLAYER_MOVE;
		new_pos.y += sinf(player->rotation) * PLAYER_MOVE;
	}
	if (is_key_pressed(KEY_D, cub))
	{
		new_pos.x += cosf(player->rotation + M_PI_2) * PLAYER_MOVE;
		new_pos.y += sinf(player->rotation + M_PI_2) * PLAYER_MOVE;
	}
	if (is_key_pressed(KEY_A, cub))
	{
		new_pos.x += cosf(player->rotation - M_PI_2) * PLAYER_MOVE;
		new_pos.y += sinf(player->rotation - M_PI_2) * PLAYER_MOVE;
	}
	return (new_pos);
}

static int	is_valid_position(t_cub *cub, float x, float y)
{
	char	**map;

	map = cub->map->map;
	return (map[(int)(y - PLAYER_OFFSET)][(int)(x - PLAYER_OFFSET)] == FLOOR
		&& map[(int)(y - PLAYER_OFFSET)][(int)(x + PLAYER_OFFSET)] == FLOOR
		&& map[(int)(y + PLAYER_OFFSET)][(int)(x + PLAYER_OFFSET)] == FLOOR
		&& map[(int)(y + PLAYER_OFFSET)][(int)(x - PLAYER_OFFSET)] == FLOOR);
}
