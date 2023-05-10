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

static void	draw_half_minimap(t_cub *cub, t_player player, int step);
static void draw_half_minimap_stripe(t_cub *cub, t_vector screen, t_fvector map_pos, int step);
static void	draw_minimap_pixel(t_cub *cub, t_vector screen, t_fvector map_pos);

void	draw_minimap(t_cub *cub)
{
	t_player	player;

	pthread_mutex_lock(cub->player_data.player_lock);
	player = cub->player_data.player;
	pthread_mutex_unlock(cub->player_data.player_lock);
	draw_half_minimap(cub, player, 1);
	draw_half_minimap(cub, player, -1);
}

static void	draw_half_minimap(t_cub *cub, t_player player, int step)
{
	t_vector	screen;
	t_fvector	map_pos;
	int			x_offset;

	screen.x = MAP_PIXEL_OFFSET + MAP_PIXEL_HALF_SIZE;
	screen.y = WIN_HEIGHT - (MAP_PIXEL_OFFSET + MAP_PIXEL_HALF_SIZE);
	x_offset = 0;
	while (x_offset < MAP_PIXEL_HALF_SIZE)
	{
		map_pos.x = player.pos.x
			+ (float)x_offset / MAP_PIXEL_HALF_SIZE * MAP_HALF_SIZE * step;
		map_pos.y = player.pos.y;
		draw_half_minimap_stripe(cub, screen, map_pos, 1);
		draw_half_minimap_stripe(cub, screen, map_pos, -1);
		screen.x += step;
		x_offset++;
	}
}

static void	draw_half_minimap_stripe(t_cub *cub, t_vector screen, t_fvector map_pos, int step)
{
	int		y_offset;
	float	map_step;

	y_offset = 0;
	map_step = (float)MAP_HALF_SIZE / MAP_PIXEL_HALF_SIZE * step;
	while (y_offset < MAP_PIXEL_HALF_SIZE)
	{
		map_pos.y += map_step;
		//printf("hms: %f\n", map_pos.y);
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
		|| (map_pos.x > cub->map.width || map_pos.y > cub->map.height))
		return ;
//	printf("map pos: %f / %zu %f / %zu\n", map_pos.x, cub->map.width, map_pos.y, cub->map.height);
//	printf("screen %d %d\n", screen.x, screen.y);
	cell = cub->map.map[(int)map_pos.y][(int)map_pos.x];
	if (cell == WALL)
		color = 0x0;
	else if (cell == DOOR_OPEN)
		color = 0x00FF00;
	else
		color = 0xFFFFFF;
	mlx_put_point(&cub->mlx_data->img_data, screen, color);
}
