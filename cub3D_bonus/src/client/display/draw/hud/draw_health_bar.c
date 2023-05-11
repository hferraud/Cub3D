/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_health_bar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mururoah <mururoah@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:57:00 by mururoah          #+#    #+#             */
/*   Updated: 2023/05/11 11:57:00 by mururoah         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "hud.h"
#include "draw.h"

void	draw_health_bar_pixel(t_cub *cub, t_vector offset, t_vector screen);

void	draw_health_bar(t_cub *cub)
{
	t_vector	screen;
	t_vector	offset;

	screen.x = WIN_WIDTH / 2 - HEALTH_BAR_WIDTH / 2;
	offset.x = 0;
	while (offset.x < HEALTH_BAR_WIDTH)
	{
		screen.y = WIN_HEIGHT - HEALTH_BAR_OFFSET - HEALTH_BAR_HEIGHT;
		offset.y = 0;
		while (offset.y < HEALTH_BAR_HEIGHT)
		{
			draw_health_bar_pixel(cub, offset, screen);
			screen.y++;
			offset.y++;
		}
		screen.x++;
		offset.x++;
	}
}

void	draw_health_bar_pixel(t_cub *cub, t_vector offset, t_vector screen)
{
	int		color;
	float	life_ratio;
	float	x_ratio;

	pthread_mutex_lock(cub->player_data.player_lock);
	life_ratio = cub->player_data.player_status.life / LIFE_MAX;
	pthread_mutex_unlock(cub->player_data.player_lock);
	x_ratio = offset.x / HEALTH_BAR_WIDTH;
	if (offset.x < BORDER_SIZE || offset.x >= HEALTH_BAR_WIDTH - BORDER_SIZE)
		color = 0x0;
	else if (offset.y < BORDER_SIZE || offset.y >= HEALTH_BAR_HEIGHT - BORDER_SIZE)
		color = 0x0;
	else if (x_ratio < life_ratio)
		color = 0x00FF00;
	else
		color = 0x808080;
	mlx_put_point(&cub->mlx_data->img_data, screen, color);
}
