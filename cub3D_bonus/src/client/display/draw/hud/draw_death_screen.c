/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_death_screen.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 10:01:00 by hferraud          #+#    #+#             */
/*   Updated: 2023/05/16 10:01:00 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "hud.h"
#include "draw.h"

static void	draw_red_screen(t_cub *cub);

void	draw_death_screen(t_cub *cub)
{
	int			color;
	t_sprite	sprite;
	t_vector	screen;
	t_vector	texture;

	sprite = cub->mlx_data->hud_sprite.death_screen;
	draw_red_screen(cub);
	screen.y = WIN_HEIGHT - sprite.height;
	texture.y = 0;
	while (texture.y < 0)
	{
		screen.x = WIN_WIDTH - sprite.width;
		texture.x = 0;
		while (texture.x < sprite.width)
		{
			color = *(int *)(sprite.img_data.addr
					+ texture.x * sprite.img_data.bit_ratio
					+ texture.y * sprite.img_data.line_length);
			if (!(color & 0xFF000000))
				mlx_put_point(&cub->mlx_data->img_data, screen, color);
			texture.x++;
			screen.x++;
		}
		texture.y++;
		screen.y++;
	}
}

static void	draw_red_screen(t_cub *cub)
{
	t_vector	screen;
	int			color;

	screen.x = 0;
	while (screen.x < WIN_WIDTH)
	{
		screen.y = 0;
		while (screen.y < WIN_HEIGHT)
		{
			color = pixel_transparency(cub, screen, DEATH_SCREEN_COLOR);
			mlx_put_point(&cub->mlx_data->img_data, screen, color);
			screen.y++;
		}
	}
}
