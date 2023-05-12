/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_weapon_view.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:04:00 by ethan             #+#    #+#             */
/*   Updated: 2023/05/12 17:04:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "hud.h"
#include "draw.h"

static t_sprite	get_sprite_from_weapon(t_hud_sprite hud_sprite, t_weapon weapon, size_t frame_since_last_shoot);
static void	draw_weapon_view_sprite(t_cub *cub, t_sprite sprite, t_vector screen);

void	draw_weapon_view(t_cub *cub)
{
	t_vector	screen;
	t_sprite	sprite;
	size_t		*frame_since_last_shoot;

	pthread_mutex_lock(cub->player_data.player_lock);
	frame_since_last_shoot = &cub->player_data.player_status.frame_since_last_shoot;
	sprite = get_sprite_from_weapon(cub->mlx_data->hud_sprite, cub->player_data.player_status.weapon_equipped, *frame_since_last_shoot);
	pthread_mutex_unlock(cub->player_data.player_lock);
	screen.x = WIN_WIDTH - sprite.width;
	screen.y = WIN_HEIGHT - sprite.height;
	draw_weapon_view_sprite(cub, sprite, screen);
	(*frame_since_last_shoot) = *frame_since_last_shoot + 1;
}

static void	draw_weapon_view_sprite(t_cub *cub, t_sprite sprite, t_vector screen)
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

static t_sprite	get_sprite_from_weapon(t_hud_sprite hud_sprite, t_weapon weapon, size_t frame_since_last_shoot)
{
	int index;

	if (weapon == KNIFE_INDEX)
	{
		index = (frame_since_last_shoot / 4);
		if (index >= NB_KNIFE_SPRITES)
			index = 0;
		return (hud_sprite.knife[index]);
	}
	else if (weapon == PISTOL_INDEX)
	{
		index = (frame_since_last_shoot / 3);
		if (index >= NB_PISTOL_SPRITES)
			index = 0;
		return (hud_sprite.pistol[index]);
	}
	else
	{
		index = (frame_since_last_shoot);
		if (index >= NB_AR_SPRITES)
			index = 0;
		return (hud_sprite.assault_rifle[index]);
	}
}