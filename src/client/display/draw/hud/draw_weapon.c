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

static void		draw_weapon_sprite(t_cub *cub, t_sprite sprite, t_vector start);
static t_vector	get_draw_start(t_weapon weapon, t_sprite sprite);

void	draw_weapon(t_cub *cub)
{
	t_sprite	sprite;
	t_weapon	weapon_index;
	t_vector	draw_start;

	pthread_mutex_lock(cub->player_data.player_lock);
	weapon_index = cub->player_data.player_status.weapon_equipped;
	pthread_mutex_unlock(cub->player_data.player_lock);
	sprite = cub->mlx_data->hud_sprite.weapon[weapon_index];
	draw_start = get_draw_start(weapon_index, sprite);
	draw_weapon_sprite(cub, sprite, draw_start);
}

static void	draw_weapon_sprite(t_cub *cub, t_sprite sprite, t_vector start)
{
	t_vector	screen;
	t_vector	texture;
	int			color;

	screen.y = start.y;
	texture.y = 0;
	while (texture.y < sprite.height)
	{
		screen.x = start.x;
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

static t_vector	get_draw_start(t_weapon weapon, t_sprite sprite)
{
	t_vector	draw_start;

	if (weapon == KNIFE_INDEX)
	{
		draw_start.x = KNIFE_OFFSET_X;
		draw_start.y = WIN_HEIGHT - (sprite.height + KNIFE_OFFSET_Y);
	}
	else if (weapon == PISTOL_INDEX)
	{
		draw_start.x = PISTOL_OFFSET_X;
		draw_start.y = WIN_HEIGHT - (sprite.height + PISTOL_OFFSET_Y);
	}
	else
	{
		draw_start.x = AR_OFFSET_X;
		draw_start.y = WIN_HEIGHT - sprite.height;
	}
	return (draw_start);
}
