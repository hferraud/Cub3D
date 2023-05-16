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

static void	draw_red_screen(t_cub *cub, int color);
static void	draw_game_over(t_cub *cub, t_sprite sprite);

void	draw_death_screen(t_cub *cub)
{
	t_sprite	sprite;
	size_t		frame_player_died;
	float		transparency;
	int			life;
	int			color;

	pthread_mutex_lock(cub->player_data.player_lock);
	life = cub->player_data.player_status.life;
	frame_player_died = cub->player_data.player_status.frame_player_died;
	pthread_mutex_unlock(cub->player_data.player_lock);
	if (life < LIFE_MAX)
	{
		transparency = (1.f - cub->player_data.player_status.life
				/ (float)LIFE_MAX) * DEATH_SCREEN_TRANSPARENCY;
		color = DEATH_SCREEN_COLOR | ((int)transparency << 24);
		draw_red_screen(cub, color);
	}
	sprite = cub->mlx_data->hud_sprite.death_screen;
	if (frame_player_died < DEATH_SCREEN_DURATION)
	{
		color = DEATH_SCREEN_COLOR
			| ((int)(DEATH_SCREEN_TRANSPARENCY
					* (1.f - (float)frame_player_died
						/ DEATH_SCREEN_DURATION)) << 24);
		draw_red_screen(cub, color);
		draw_game_over(cub, sprite);
	}
}

static void	draw_red_screen(t_cub *cub, int color)
{
	register const unsigned int	*dest_limit
		= (unsigned int *)cub->mlx_data->img_data.addr
		+ (cub->mlx_data->img_data.line_length >> 2) * WIN_HEIGHT;
	register unsigned int		*dest;

	dest = (unsigned int *)cub->mlx_data->img_data.addr;
	while (dest < dest_limit)
	{
		*dest = color_transparency(*dest, color);
		dest++;
	}
}

static void	draw_game_over(t_cub *cub, t_sprite sprite)
{
	t_vector	texture;
	t_vector	screen;
	int			color;

	screen.y = WIN_HEIGHT / 2 - sprite.height / 2;
	texture.y = 0;
	while (texture.y < sprite.height && screen.y < WIN_HEIGHT)
	{
		screen.x = WIN_WIDTH / 2 - sprite.width / 2;
		texture.x = 0;
		while (texture.x < sprite.width && screen.x < WIN_WIDTH)
		{
			color = *(int *)(sprite.img_data.addr
					+ texture.x * sprite.img_data.bit_ratio
					+ texture.y * sprite.img_data.line_length);
			pixel_transparency(cub, screen, color);
			if (!(color & 0xFF000000))
				mlx_put_point(&cub->mlx_data->img_data, screen, color);
			texture.x++;
			screen.x++;
		}
		texture.y++;
		screen.y++;
	}
	cub->player_data.player_status.frame_player_died++;
}
