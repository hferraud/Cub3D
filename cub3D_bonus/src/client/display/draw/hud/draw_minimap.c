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
static void draw_half_minimap_stripe(t_cub *cub, t_vector screen, t_fvector map_pos, int step);
static void	draw_minimap_pixel(t_cub *cub, t_vector screen, t_fvector map_pos);

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

	screen.x = MAP_PIXEL_OFFSET + MAP_PIXEL_HALF_SIZE;
	screen.y = WIN_HEIGHT - (MAP_PIXEL_OFFSET + MAP_PIXEL_HALF_SIZE);
	x_offset = 0;
	while (x_offset < MAP_PIXEL_HALF_SIZE)
	{
		map_pos.x = cub->player_data.player.pos.x
			+ (float)x_offset / MAP_PIXEL_HALF_SIZE * MAP_HALF_SIZE * step;
		draw_half_minimap_stripe(cub, screen, map_pos, 1);
		draw_half_minimap_stripe(cub, screen, map_pos, -1);
		screen.x += step;
		x_offset++;
	}
}

static void	draw_half_minimap_stripe(t_cub *cub, t_vector screen, t_fvector map_pos, int step)
{
	int		y_offset;

	y_offset = 0;
	while (y_offset < MAP_PIXEL_HALF_SIZE)
	{
		map_pos.y = cub->player_data.player.pos.y
				+ (float)y_offset / MAP_PIXEL_HALF_SIZE * MAP_HALF_SIZE * step;
		draw_minimap_pixel(cub, screen, map_pos);
		screen.y += step;
		y_offset++;
	}
}

static void	draw_minimap_pixel(t_cub *cub, t_vector screen, t_fvector map_pos)
{
	char	cell;
	int		color;

	if ((map_pos.x < 0 || map_pos.y < 0)
		|| (map_pos.x >= cub->map.width || map_pos.y >= cub->map.height))
		color = 0x666666;
	else
	{
		cell = cub->map.map[(int)map_pos.y][(int)map_pos.x];
		if (map_pos.x < cub->player_data.player.pos.x + PLAYER_OFFSET
			&& map_pos.x > cub->player_data.player.pos.x - PLAYER_OFFSET
			&& map_pos.y < cub->player_data.player.pos.y + PLAYER_OFFSET
			&& map_pos.y > cub->player_data.player.pos.y - PLAYER_OFFSET)
			color = 0xFF0000;
		else if (cell == WALL)
			color = 0x0;
		else if (cell == DOOR_CLOSE)
			color = 0x00FF00;
		else
			color = 0xFFFFFF;
	}
	mlx_put_point(&cub->mlx_data->img_data, screen, color);
}
