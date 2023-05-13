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
static int	get_color_from_cell(char cell);
static bool	is_in_circle(t_vector screen, float radius);

void	draw_minimap_pixel(t_cub *cub, t_vector screen, t_fvector map_pos)
{
	int		color;

	if (is_in_circle(screen, MAP_RADIUS - BORDER_SIZE))
	{
		color = get_pixel_color(cub, map_pos);
		color = pixel_transparency(cub, screen, color);
		mlx_put_point(&cub->mlx_data->img_data, screen, color);
	}
	else if (is_in_circle(screen, MAP_RADIUS))
	{
		color = MAP_BORDER_COLOR;
		mlx_put_point(&cub->mlx_data->img_data, screen, color);
	}
}

static int	get_pixel_color(t_cub *cub, t_fvector map_pos)
{
	char			cell;
	unsigned int	color;

	if ((map_pos.x < 0 || map_pos.y < 0)
		|| (map_pos.x >= cub->map.width || map_pos.y >= cub->map.height))
		color = MAP_EMPTY_COLOR;
	else
	{
		cell = cub->map.map[(int)map_pos.y][(int)map_pos.x];
		if ((map_pos.x < cub->player_data.player.pos.x + PLAYER_OFFSET
				&& map_pos.x > cub->player_data.player.pos.x - PLAYER_OFFSET)
			&& (map_pos.y < cub->player_data.player.pos.y + PLAYER_OFFSET
				&& map_pos.y > cub->player_data.player.pos.y - PLAYER_OFFSET))
			color = MAP_PLAYER_COLOR;
		else
			color = get_color_from_cell(cell);
	}
	return (color | MAP_TRANSPARENCY);
}

static int	get_color_from_cell(char cell)
{
	if (cell == ' ')
		return (MAP_EMPTY_COLOR);
	else if (cell == WALL)
		return (MAP_WALL_COLOR);
	else if (cell == DOOR_CLOSE)
		return (MAP_DOOR_CLOSE_COLOR);
	else if (cell == DOOR_OPEN)
		return (MAP_DOOR_OPEN_COLOR);
	else
		return (MAP_FLOOR_COLOR);
}

static bool	is_in_circle(t_vector screen, float radius)
{
	t_vector	center;
	t_vector	relative_pos;

	center.x = WIN_WIDTH - (MAP_PIXEL_OFFSET + MAP_RADIUS);
	center.y = MAP_PIXEL_OFFSET + MAP_RADIUS;
	relative_pos = vector_sub(center, screen);
	return (relative_pos.x * relative_pos.x
		+ relative_pos.y * relative_pos.y < radius * radius);
}
