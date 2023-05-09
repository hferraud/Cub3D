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

static void	draw_minimap_cell(t_cub *cub, t_fvector cell_pos, t_vector screen_pos);

void    draw_minimap(t_cub *cub)
{
	int			row;
	int 		col;
	t_fvector	cell_pos;
	t_vector	screen_pos;

	cell_pos.x = cub->player_data.player.pos.x - CELL_PIXEL_SIZE * MAP_PIXEL_HALF_SIZE;
	cell_pos.y = cub->player_data.player.pos.y - CELL_PIXEL_SIZE * MAP_PIXEL_HALF_SIZE;
	screen_pos.x = MAP_PIXEL_OFFSET + MAP_PIXEL_SIZE;
	screen_pos.y = WIN_HEIGHT - (MAP_PIXEL_OFFSET + MAP_PIXEL_SIZE);
	while (row < MAP_SIZE)
	{
		while (col < MAP_SIZE)
		{
			draw_minimap_cell(cub, cell_pos, screen_pos);
			col++;
		}
		row++;
	}
}

static void	draw_minimap_cell(t_cub *cub, t_fvector cell_pos, t_vector screen_pos)
{
	t_fvector	cell_start;
	t_fvector	cell_end;

	cell_start = cell_pos;
	cell_end.x = ceilf(cell_start.x);
	cell_end.y = ceilf(cell_start.y);

}
