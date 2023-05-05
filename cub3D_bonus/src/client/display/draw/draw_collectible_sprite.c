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

static void			draw_collectible_stripe(t_cub *cub, t_draw_param dp);
static t_fvector	camera_projetion(t_cub *cub, t_collectible collectible);

void	draw_collectible_sprite(t_cub *cub, t_collectible collectible,
			const float *z_buffer)
{
	t_draw_param	dp;
	t_fvector		camera;
	int				scale;

	dp.sprite = cub->mlx_data->collectible_sprite[MEDIC_KIT_ID];
	camera = camera_projetion(cub, collectible);
	dp.width = WIN_WIDTH / (camera.y * 4);
	dp.height = WIN_HEIGHT / (camera.y * 4);
	dp.screen.x = (WIN_WIDTH / 2.f) * (1 + camera.x / camera.y);
	dp.draw_start.x = dp.screen.x - dp.width / 2;
	dp.draw_end.x = dp.screen.x + dp.width / 2;
	scale = abs((int)(WIN_HEIGHT / camera.y / 2));
	dp.draw_start.y = WIN_HEIGHT / 2 + scale - dp.height;
	if (dp.draw_start.y > WIN_HEIGHT)
		dp.draw_start.y = WIN_HEIGHT - 1;
	dp.draw_end.y = WIN_HEIGHT / 2 + scale;
	if (dp.draw_end.y < 0)
		dp.draw_end.y = 0;
	dp.screen.x = dp.draw_start.x;
	while (dp.screen.x < dp.draw_end.x)
	{
		if (dp.screen.x < WIN_WIDTH && dp.screen.x >= 0 && z_buffer[dp.screen.x] > camera.y)
		{
			dp.texture.x = (dp.screen.x - dp.draw_start.x)
						   * dp.sprite.width / dp.width;
			draw_collectible_stripe(cub, dp);
		}
		dp.screen.x++;
	}
}

static void	draw_collectible_stripe(t_cub *cub, t_draw_param dp)
{
	dp.screen.y = dp.draw_start.y;
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

static t_fvector	camera_projetion(t_cub *cub, t_collectible collectible)
{
	float		inverse_det;
	t_fvector	camera;

	pthread_mutex_lock(cub->player_data.player_lock);
	inverse_det = -1.f / (cub->player_data.camera.x * cub->player_data.player.rotation.y
			- cub->player_data.player.rotation.x * cub->player_data.camera.y);
	camera.x = inverse_det * (
			cub->player_data.player.rotation.y * collectible.relative_pos.x
			- cub->player_data.player.rotation.x * collectible.relative_pos.y);
	pthread_mutex_unlock(cub->player_data.player_lock);
	camera.y = inverse_det * (
			-cub->player_data.camera.y * collectible.relative_pos.x
			+ cub->player_data.camera.x * collectible.relative_pos.y);
	return (camera);
}