/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:11:00 by hferraud          #+#    #+#             */
/*   Updated: 2023/05/09 16:11:00 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "cub.h"
#include "draw.h"
#include "hud.h"

static void	draw_half_minimap(t_cub *cub, int step);
static void	draw_half_minimap_stripe(t_cub *cub, t_vector screen, t_fvector map_pos, int step);

void	draw_minimap(t_cub *cub)
{
	pthread_mutex_lock(cub->player_data.player_lock);
	draw_half_minimap(cub, 1);
	draw_half_minimap(cub, -1);
	pthread_mutex_unlock(cub->player_data.player_lock);
}

static void	draw_half_minimap(t_cub *cub, int step)
{
	t_vector	screen;
	t_fvector	map_pos;
	int			x_offset;

	screen.x = MAP_PIXEL_OFFSET + MAP_RADIUS;
	screen.y = MAP_PIXEL_OFFSET + MAP_RADIUS;
	if (step == -1)
	{
		screen.x += step;
		x_offset = 1;
	}
	else
		x_offset = 0;
	while (x_offset < MAP_RADIUS)
	{
		map_pos.x = cub->player_data.player.pos.x
			+ (float)x_offset / MAP_RADIUS * MAP_HALF_SIZE * step;
		draw_half_minimap_stripe(cub, screen, map_pos, 1);
		draw_half_minimap_stripe(cub, screen, map_pos, -1);
		screen.x += step;
		x_offset++;
	}
}

static void	draw_half_minimap_stripe(t_cub *cub, t_vector screen, t_fvector map_pos, int step)
{
	int		y_offset;

	if (step == -1)
	{
		screen.y += step;
		y_offset = 1;
	}
	else
		y_offset = 0;
	while (y_offset < MAP_RADIUS)
	{
		map_pos.y = cub->player_data.player.pos.y
			+ (float)y_offset / MAP_RADIUS * MAP_HALF_SIZE * step;
		draw_minimap_pixel(cub, screen, map_pos);
		screen.y += step;
		y_offset++;
	}
}
