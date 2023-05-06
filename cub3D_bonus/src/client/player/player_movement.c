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

static void			player_rotation_update(t_cub *cub);
static void			player_position_update(t_cub *cub);
static t_fvector	new_position_calculate(t_cub *cub);
static int			is_valid_position(t_cub *cub, float x, float y);
static int	player_moved(t_player before, t_player current);

/**
 * @brief Update the position and rotation of the player
 */
void	player_update(t_cub *cub)
{
	t_player	save;

	pthread_mutex_lock(cub->player_data.player_lock);
	save = cub->player_data.player;
	pthread_mutex_unlock(cub->player_data.player_lock);
	player_rotation_update(cub);
	player_position_update(cub);
	pthread_mutex_lock(cub->player_data.player_lock);
	if (player_moved(save, cub->player_data.player))
	{
		pthread_mutex_lock(cub->player_data.update_lock);
		cub->player_data.update = true;
		pthread_mutex_unlock(cub->player_data.update_lock);
	}
	pthread_mutex_unlock(cub->player_data.player_lock);
}

static void	player_rotation_update(t_cub *cub)
{
	static size_t	count = 0;
	int 			x;
	int 			y;

	mlx_mouse_get_pos(cub->mlx_data->mlx_ptr, cub->mlx_data->win_ptr, &x, &y);
	if (x != WIN_WIDTH / 2
		|| is_key_pressed(KEY_LEFT, cub)
		|| is_key_pressed(KEY_RIGHT, cub))
	{
		pthread_mutex_lock(cub->player_data.player_lock);
		if (x != WIN_WIDTH / 2)
			cub->player_data.player.rotation = fvector_rotate(cub->player_data.player.rotation, PLAYER_ROTATION / 100.0f * (x - (WIN_WIDTH / 2)));
		if (is_key_pressed(KEY_LEFT, cub))
			cub->player_data.player.rotation = fvector_rotate(cub->player_data.player.rotation, -PLAYER_ROTATION);
		else if (is_key_pressed(KEY_RIGHT, cub))
			cub->player_data.player.rotation = fvector_rotate(cub->player_data.player.rotation, PLAYER_ROTATION);
		pthread_mutex_unlock(cub->player_data.player_lock);
		cub->player_data.camera = fvector_rotate(cub->player_data.player.rotation, M_PI_2);
	}
	if (count % 2 == 0)
		mlx_mouse_move(cub->mlx_data->mlx_ptr, cub->mlx_data->win_ptr,
			WIN_WIDTH / 2, WIN_HEIGHT / 2);
	count++;
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
	pthread_mutex_lock(cub->player_data.player_lock);
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
				player->pos.x =	1.f - UNCERTAINTY - PLAYER_OFFSET + ((int) player->pos.x);
			else
				player->pos.x =	PLAYER_OFFSET + UNCERTAINTY + ((int) player->pos.x);
		}
		else if (map[(int) new_pos.y][(int)(new_pos.x + PLAYER_OFFSET)] == FLOOR
			&& map[(int)new_pos.y][(int)(new_pos.x - PLAYER_OFFSET)] == FLOOR
			&& is_valid_position(cub, new_pos.x, player->pos.y))
		{
			player->pos.x = new_pos.x;
			if (new_pos.y > player->pos.y)
				player->pos.y =	1.f - UNCERTAINTY - PLAYER_OFFSET + ((int) player->pos.y);
			else
				player->pos.y =	PLAYER_OFFSET + UNCERTAINTY + ((int) player->pos.y);
		}
	}
	pthread_mutex_unlock(cub->player_data.player_lock);
}

static t_fvector	new_position_calculate(t_cub *cub)
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

static int	is_valid_position(t_cub *cub, float x, float y)
{
	char	**map;

	map = cub->map.map;
	return (map[(int)(y - PLAYER_OFFSET)][(int)(x - PLAYER_OFFSET)] == FLOOR
		&& map[(int)(y - PLAYER_OFFSET)][(int)(x + PLAYER_OFFSET)] == FLOOR
		&& map[(int)(y + PLAYER_OFFSET)][(int)(x + PLAYER_OFFSET)] == FLOOR
		&& map[(int)(y + PLAYER_OFFSET)][(int)(x - PLAYER_OFFSET)] == FLOOR);
}

static int	player_moved(t_player before, t_player current)
{
	return (before.pos.x != current.pos.x
		|| before.pos.y != current.pos.y
		|| before.rotation.x != current.rotation.x
		|| before.rotation.y != current.rotation.y);
}
