/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_pixel.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mururoah <mururoah@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 21:28:00 by mururoah          #+#    #+#             */
/*   Updated: 2023/05/10 21:28:00 by mururoah         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "hud.h"
#include "draw.h"

static int	get_pixel_color(t_cub *cub, t_fvector map_pos);
static int	pixel_transparency(t_cub *cub, t_vector screen, int color);
//static void	pixel_rotate(t_fvector orientation, t_vector *screen);
static bool	is_in_circle(t_vector screen, float radius);

void	draw_minimap_pixel(t_cub *cub, t_vector screen, t_fvector map_pos)
{
	int		color;

	if (is_in_circle(screen, MAP_RADIUS - 2))
	{
		color = get_pixel_color(cub, map_pos);
//		pixel_rotate(cub->player_data.player.rotation, &screen);
		color = pixel_transparency(cub, screen, color);
		mlx_put_point(&cub->mlx_data->img_data, screen, color);
	}
	else if (is_in_circle(screen, MAP_RADIUS))
	{
		color = 0xDD000000;
		color = pixel_transparency(cub, screen, color);
		mlx_put_point(&cub->mlx_data->img_data, screen, color);
	}
}

static int	get_pixel_color(t_cub *cub, t_fvector map_pos)
{
	char	cell;
	int		color;

	if ((map_pos.x < 0 || map_pos.y < 0)
		|| (map_pos.x >= cub->map.width || map_pos.y >= cub->map.height))
		color = 0x80161616;
	else
	{
		cell = cub->map.map[(int)map_pos.y][(int)map_pos.x];
		if ((map_pos.x < cub->player_data.player.pos.x + PLAYER_OFFSET
				&& map_pos.x > cub->player_data.player.pos.x - PLAYER_OFFSET)
			&& (map_pos.y < cub->player_data.player.pos.y + PLAYER_OFFSET
				&& map_pos.y > cub->player_data.player.pos.y - PLAYER_OFFSET))
			color = 0x80FF0000;
		else if (cell == ' ')
			color = 0x80161616;
		else if (cell == WALL)
			color = 0x80000000;
		else if (cell == DOOR_CLOSE)
			color = 0x8000FF00;
		else
			color = 0x80FFFFFF;
	}
	return (color);
}

static int	pixel_transparency(t_cub *cub, t_vector screen, int color)
{
	float			transparency;
	float			inv_transparency;
	unsigned int	screen_color;
	unsigned int	new_color;

	transparency = (color & 0xFF000000) >> 24;
	transparency = transparency / 0xFF;
	inv_transparency = 1.f - transparency;
	screen_color = *(unsigned int *)(cub->mlx_data->img_data.addr
			+ screen.x * cub->mlx_data->img_data.bit_ratio
			+ screen.y * cub->mlx_data->img_data.line_length);
	new_color = 0;
	new_color |= ((unsigned int)(((color & 0xFF0000) >> 16) * transparency)
			+ (unsigned int)(((screen_color & 0xFF0000) >> 16) * inv_transparency)) << 16;
	new_color |= ((unsigned int)(((color & 0xFF00) >> 8) * transparency)
			+ (unsigned int)(((screen_color & 0xFF00) >> 8) * inv_transparency)) << 8;
	new_color |= ((unsigned int)((color & 0xFF) * transparency)
			+ (unsigned int)((screen_color & 0xFF) * inv_transparency));
	return (new_color);
}

//static void	pixel_rotate(t_fvector rotation, t_vector *screen)
//{
//	t_vector	center;
//	t_fvector	relative_pos;
//
//	center.x = MAP_PIXEL_OFFSET + MAP_RADIUS;
//	center.y = WIN_HEIGHT - (MAP_PIXEL_OFFSET + MAP_RADIUS);
//	relative_pos.x = center.x - screen->x;
//	relative_pos.y = center.y - screen->y;
//	relative_pos = fvector_rotate(relative_pos,
//			atan2f(rotation.x, rotation.y));
//	screen->x = round(center.x + relative_pos.x);
//	screen->y = round(center.y + relative_pos.y);
//}

static bool	is_in_circle(t_vector screen, float radius)
{
	t_vector	center;
	t_vector	relative_pos;

	center.x = MAP_PIXEL_OFFSET + MAP_RADIUS;
	center.y = MAP_PIXEL_OFFSET + MAP_RADIUS;
	relative_pos = vector_sub(center, screen);
	return (relative_pos.x * relative_pos.x
		+ relative_pos.y * relative_pos.y < radius * radius);
}
