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
#include "cub.h"
#include "hook.h"
#include "player.h"

void 	collectible_set_dist(t_cub *cub, t_player player);
void	collectible_sort(t_cub *cub);

static void			player_rotation_update(t_cub *cub);
static void			player_position_update(t_cub *cub);

/**
 * @brief Update the position and rotation of the player
 */
void	player_update(t_cub *cub)
{
	t_player	save;

	pthread_mutex_lock(cub->player_data.player_lock);
	save = cub->player_data.player;
	player_rotation_update(cub);
	player_position_update(cub);
	collectible_set_dist(cub, cub->player_data.player);
	collectible_sort(cub);
	if (player_moved(save, cub->player_data.player))
	{
		pthread_mutex_lock(cub->player_data.update_lock);
		cub->player_data.update = true;
		pthread_mutex_unlock(cub->player_data.update_lock);
		if ((save.pos.x != cub->player_data.player.pos.x
			|| save.pos.y != cub->player_data.player.pos.y)
			&& player_hit_collectible(cub))
			add_collectible_event(cub);
	}
	pthread_mutex_unlock(cub->player_data.player_lock);
}

static void	player_rotation_update(t_cub *cub)
{
//	static size_t	count = 0;
	int 			x;
	int 			y;

	(void) x;
	(void) y;
//	mlx_mouse_get_pos(cub->mlx_data->mlx_ptr, cub->mlx_data->win_ptr, &x, &y);
	if (/*x != WIN_WIDTH / 2
		|| */is_key_pressed(KEY_LEFT, cub)
		|| is_key_pressed(KEY_RIGHT, cub))
	{
//		if (x != WIN_WIDTH / 2)
//			cub->player_data.player.rotation = fvector_rotate(cub->player_data.player.rotation, PLAYER_ROTATION / 100.0f * (x - (WIN_WIDTH / 2)));
		if (is_key_pressed(KEY_LEFT, cub))
			cub->player_data.player.rotation = fvector_rotate(cub->player_data.player.rotation, -PLAYER_ROTATION);
		if (is_key_pressed(KEY_RIGHT, cub))
			cub->player_data.player.rotation = fvector_rotate(cub->player_data.player.rotation, PLAYER_ROTATION);
		cub->player_data.camera = fvector_rotate(cub->player_data.player.rotation, M_PI_2);
	}
//	if (count % 2 == 0)
//		mlx_mouse_move(cub->mlx_data->mlx_ptr, cub->mlx_data->win_ptr,
//			WIN_WIDTH / 2, WIN_HEIGHT / 2);
//	count++;
}

/**
 * @brief Update the position player and check the collision with the walls
 */
static void	player_position_update(t_cub *cub)
{
	t_player	*player;
	t_fvector	new_pos;
	char		**map;

	player = &cub->player_data.player;
	map = cub->map.map;
	new_pos = new_position_calculate(cub);
	if (is_valid_position(cub, new_pos.x, new_pos.y))
		player->pos = new_pos;
	else
	{
		if (is_floor(map[(int)(new_pos.y - PLAYER_OFFSET)][(int) new_pos.x])
			&& is_floor(map[(int)(new_pos.y + PLAYER_OFFSET)][(int) new_pos.x])
			&& is_valid_position(cub, player->pos.x, new_pos.y))
		{
			player->pos.y = new_pos.y;
			if (new_pos.x > player->pos.x)
				player->pos.x =	1.f - UNCERTAINTY - PLAYER_OFFSET + ((int) player->pos.x);
			else
				player->pos.x =	PLAYER_OFFSET + UNCERTAINTY + ((int) player->pos.x);
		}
		else if (is_floor(map[(int) new_pos.y][(int)(new_pos.x + PLAYER_OFFSET)])
			&& is_floor(map[(int)new_pos.y][(int)(new_pos.x - PLAYER_OFFSET)])
			&& is_valid_position(cub, new_pos.x, player->pos.y))
		{
			player->pos.x = new_pos.x;
			if (new_pos.y > player->pos.y)
				player->pos.y =	1.f - UNCERTAINTY - PLAYER_OFFSET + ((int) player->pos.y);
			else
				player->pos.y =	PLAYER_OFFSET + UNCERTAINTY + ((int) player->pos.y);
		}
	}
}
