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

void	draw_minimap(t_cub *cub)
{
	int			wall_width;
	size_t		i;
	size_t		j;
	t_rectangle	square;

	if (cub->map.width * WIN_WIDTH > cub->map.height * WIN_HEIGHT)
		wall_width = (int)((float) WIN_WIDTH / (float) cub->map.width);
	else
		wall_width = (int)((float) WIN_HEIGHT / (float) cub->map.height);
//	wall_width = 15;
	i = 0;
	while (i < cub->map.height)
	{
		j = 0;
		while (cub->map.map[i][j])
		{
			if (cub->map.map[i][j] == WALL)
			{
				square = set_square(set_point((int) j * wall_width, (int) i * wall_width), wall_width, 0xFFFFFF);
				draw_rectangle(&cub->mlx_data.img_data, square);
			}
			j++;
		}
		i++;
	}
}
