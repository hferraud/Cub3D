/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 13:13:00 by ethan             #+#    #+#             */
/*   Updated: 2023/03/14 13:13:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "draw.h"

static void	draw_player(t_cub *cub, int wall_width);

void	draw_minimap(t_cub *cub)
{
	int			wall_width;
	size_t		i;
	size_t		j;
	t_rectangle	square;

	if (cub->map->width * WIN_WIDTH > cub->map->height * WIN_HEIGHT)
		wall_width = (int)((float) WIN_WIDTH / (float) cub->map->width);
	else
		wall_width = (int)((float) WIN_HEIGHT / (float) cub->map->height);
	i = 0;
	while (i < cub->map->height)
	{
		j = 0;
		while (cub->map->map[i][j])
		{
			if (cub->map->map[i][j] == WALL)
			{
				square = set_square(set_point((int) j * wall_width,
							(int) i * wall_width), wall_width, 0xFFFFFF);
				draw_rectangle(&cub->mlx_data->img_data, square);
			}
			else if (cub->map->map[i][j] == FLOOR)
			{
				square = set_square(set_point((int) j * wall_width,
											  (int) i * wall_width), wall_width, 0x0);
				draw_rectangle(&cub->mlx_data->img_data, square);
			}
			j++;
		}
		i++;
	}
	square = set_square(set_point((int) cub->map->spawn.x * wall_width,
				(int) cub->map->spawn.y * wall_width), wall_width / 5, 0x00FF00);
	draw_rectangle(&cub->mlx_data->img_data, square);
	draw_player(cub, wall_width);
}

static void	draw_player(t_cub *cub, int wall_width)
{
	t_rectangle	square;

	square = set_square(set_point((cub->player->x - PLAYER_OFFSET) * wall_width,
								  (cub->player->y - PLAYER_OFFSET) * wall_width), wall_width * 2 * PLAYER_OFFSET, 0xFF00FF);
	draw_rectangle(&cub->mlx_data->img_data, square);
}
