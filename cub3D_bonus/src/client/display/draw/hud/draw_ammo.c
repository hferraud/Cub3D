/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ammo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mururoah <mururoah@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 19:17:00 by mururoah          #+#    #+#             */
/*   Updated: 2023/05/11 19:17:00 by mururoah         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "hud.h"
#include "draw.h"

static void	draw_bullet(t_cub *cub, t_sprite sprite, t_vector screen);

void	draw_ammo(t_cub *cub)
{
	t_vector	screen;
	t_sprite	bullet_sprite;
	int			bullet_drawn;
	int			ammo;

	pthread_mutex_lock(cub->player_data.player_lock);
	ammo = cub->player_data.player_status.ammo;
	pthread_mutex_unlock(cub->player_data.player_lock);
	bullet_sprite = cub->mlx_data->hud_sprite.ammo;
	screen.x = WIN_WIDTH - 100;
	screen.y = WIN_HEIGHT - AMMO_OFFSET - BULLET_Y_OFFSET * ((ammo - 1) / 10);
	bullet_drawn = 0;
	while (bullet_drawn < ammo)
	{
		draw_bullet(cub, bullet_sprite, screen);
		screen.x += bullet_sprite.width;
		bullet_drawn++;
		if (bullet_drawn % BULLET_PER_ROW == 0)
		{
			screen.y += BULLET_Y_OFFSET;
			screen.x = WIN_WIDTH - 100;
		}
	}
}

static void	draw_bullet(t_cub *cub, t_sprite sprite, t_vector screen)
{
	t_vector	texture;
	int			color;

	texture.y = 0;
	while (texture.y < sprite.height)
	{
		texture.x = 0;
		while (texture.x < sprite.width)
		{
			color = *(int *)(sprite.img_data.addr
					+ texture.x * sprite.img_data.bit_ratio
					+ texture.y * sprite.img_data.line_length);
			if (!(color & 0xFF000000))
				mlx_put_point(&cub->mlx_data->img_data,
					vector_add(screen, texture), color);
			texture.x++;
		}
		texture.y++;
	}
}
