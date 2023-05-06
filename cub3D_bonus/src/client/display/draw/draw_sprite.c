/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_collectible_sprite.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mururoah <mururoah@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 08:14:00 by mururoah          #+#    #+#             */
/*   Updated: 2023/05/05 08:14:00 by mururoah         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "collectible.h"
#include "draw.h"

static void			draw_stripe(t_cub *cub, t_draw_param dp);

void	draw_sprite(t_cub *cub, t_draw_param dp, t_fvector camera, const float *z_buffer)
{
	dp.screen.x = dp.draw_start.x;
	if (dp.screen.x < 0)
		dp.screen.x = 0;
	while (dp.screen.x < dp.draw_end.x && dp.screen.x < WIN_WIDTH)
	{
		if (dp.screen.x < WIN_WIDTH && dp.screen.x >= 0 && z_buffer[dp.screen.x] > camera.y)
		{
			dp.texture.x = (dp.screen.x - dp.draw_start.x)
				* dp.sprite.width / dp.width;
			draw_stripe(cub, dp);
		}
		dp.screen.x++;
	}
}

static void	draw_stripe(t_cub *cub, t_draw_param dp)
{
	dp.screen.y = dp.draw_start.y;
	if (dp.screen.y < 0)
		dp.screen.y = 0;
	while (dp.screen.y < dp.draw_end.y && dp.screen.y < WIN_HEIGHT)
	{
		dp.texture.y = (dp.screen.y - dp.draw_start.y)
			* dp.sprite.height / dp.height;
		dp.color = *(int *)(dp.sprite.img_data.addr
				+ dp.texture.x * dp.sprite.img_data.bit_ratio
				+ dp.texture.y * dp.sprite.img_data.line_length);
		if (!(dp.color & 0xFF000000))
			mlx_put_pixel(&cub->mlx_data->img_data,
				dp.screen.x, dp.screen.y, dp.color);
		dp.screen.y++;
	}
}
