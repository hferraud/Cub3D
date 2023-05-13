/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_collectible_sprite.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mururoah <mururoah@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 08:14:00 by mururoah          #+#    #+#             */
/*   Updated: 2023/05/05 08:14:00 by mururoah         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "collectible.h"
#include "draw.h"

static void	draw_stripe(t_cub *cub, t_draw_param dp);
static void	sprites_init(t_cub *cub, t_player *player, t_enemy *enemies);

/**
 * @brief Draw all the sprites from nearest to the further away
 */
void	draw_sprites(t_cub *cub, const float *z_buffer)
{
	t_player			player;
	t_enemy				enemies[PLAYER_LIMIT - 1];
	t_collectible_data	collectible_data;
	size_t				i;
	size_t				j;

	sprites_init(cub, &player, enemies);
	collectible_data = cub->map.collectible_data;
	i = 0;
	j = 0;
	pthread_mutex_lock(collectible_data.collectible_lock);
	while (i < PLAYER_LIMIT - 1 && j < collectible_data.size)
	{
		if (enemies[i].dist > collectible_data.collectible[j].dist)
		{
			pthread_mutex_unlock(collectible_data.collectible_lock);
			draw_enemy(cub, enemies[i], z_buffer);
			pthread_mutex_lock(collectible_data.collectible_lock);
			i++;
		}
		else
		{
			pthread_mutex_unlock(collectible_data.collectible_lock);
			draw_collectible(cub, collectible_data.collectible[j], z_buffer);
			pthread_mutex_lock(collectible_data.collectible_lock);
			j++;
		}
	}
	while (i < PLAYER_LIMIT - 1)
	{
		pthread_mutex_unlock(collectible_data.collectible_lock);
		draw_enemy(cub, enemies[i], z_buffer);
		pthread_mutex_lock(collectible_data.collectible_lock);
		i++;
	}
	while (j < collectible_data.size)
	{
		pthread_mutex_unlock(collectible_data.collectible_lock);
		draw_collectible(cub, collectible_data.collectible[j], z_buffer);
		pthread_mutex_lock(collectible_data.collectible_lock);
		j++;
	}
	pthread_mutex_unlock(collectible_data.collectible_lock);
}

/**
 * @brief Initialize and sort the collectible and enemy array
 */
static	void	sprites_init(t_cub *cub, t_player *player, t_enemy *enemies)
{
	pthread_mutex_lock(cub->player_data.player_lock);
	*player = cub->player_data.player;
	pthread_mutex_unlock(cub->player_data.player_lock);
	collectible_set_dist(cub, *player);
	collectible_sort(cub);
	enemies_set_dist(cub, enemies, *player);
	enemies_sort(enemies);
}

void	draw_sprite(t_cub *cub, t_draw_param dp,
					const float *z_buffer, const float dist)
{
	dp.screen.x = dp.draw_start.x;
	if (dp.screen.x < 0)
		dp.screen.x = 0;
	while (dp.screen.x < dp.draw_end.x && dp.screen.x < WIN_WIDTH)
	{
		if (dp.screen.x < WIN_WIDTH && dp.screen.x
			>= 0 && z_buffer[dp.screen.x] > dist)
		{
			dp.texture.x = (dp.screen.x - dp.draw_start.x)
				* dp.sprite.width / dp.width;
			draw_stripe(cub, dp);
		}
		dp.screen.x++;
	}
}

/**
 * @brief Draw the vertical stripe of a sprite
 */
static void	draw_stripe(t_cub *cub, t_draw_param dp)
{
	dp.screen.y = dp.draw_start.y;
	if (dp.screen.y < 0)
		dp.screen.y = 0;
	while (dp.screen.y < dp.draw_end.y && dp.screen.y < WIN_HEIGHT)
	{
		dp.texture.y = (dp.screen.y - dp.draw_start.y)
			* dp.sprite.height / dp.height;
		dp.color = *(int *)(dp.sprite.img_data.addr
				+ dp.texture.x * dp.sprite.img_data.bit_ratio
				+ dp.texture.y * dp.sprite.img_data.line_length);
		if (!(dp.color & 0xFF000000))
			mlx_put_pixel(&cub->mlx_data->img_data,
				dp.screen.x, dp.screen.y, dp.color);
		dp.screen.y++;
	}
}
