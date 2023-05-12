/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_weapon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mururoah <mururoah@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:53:00 by mururoah          #+#    #+#             */
/*   Updated: 2023/05/12 10:53:00 by mururoah         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "hud.h"
#include "draw.h"

static void	draw_weapon_sprite(t_cub *cub, t_sprite sprite);

void	draw_weapon(t_cub *cub)
{
	t_sprite	sprite;
	int			weapon_index;

	pthread_mutex_lock(cub->player_data.player_lock);
	weapon_index = cub->player_data.player_status.weapon_equipped;
	pthread_mutex_unlock(cub->player_data.player_lock);
	sprite = cub->mlx_data->hud_sprite.weapon[weapon_index];
	draw_weapon_sprite(cub, sprite);
}

static void	draw_weapon_sprite(t_cub *cub, t_sprite sprite)
{
	t_vector	screen;
	t_vector	texture;
	int			color;

	screen.y = WIN_HEIGHT - (WEAPON_HEIGHT / 2 + sprite.height / 2);
	texture.y = 0;
	while (texture.y < sprite.height)
	{
		screen.x = WIN_WIDTH - (WEAPON_WIDTH / 2 + sprite.width / 2);
		texture.x = 0;
		while (texture.x < sprite.width)
		{
			color = *(int *)(sprite.img_data.addr
					+ texture.x * sprite.img_data.bit_ratio
					+ texture.y * sprite.img_data.line_length);
			if (!(color & 0xFF000000))
				mlx_put_point(&cub->mlx_data->img_data, screen, color);
			screen.x++;
			texture.x++;
		}
		screen.y++;
		texture.y++;
	}
}
