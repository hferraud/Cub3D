/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mururoah <mururoah@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:04:00 by mururoah          #+#    #+#             */
/*   Updated: 2023/05/12 17:04:00 by mururoah         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "draw.h"

static void	draw_floor(t_cub *cub, t_background_param bp);
static void	draw_ceil(t_cub *cub, t_background_param bp);
static void	draw_background_row(t_cub *cub, t_background_param bp);

void	draw_background(t_cub *cub)
{
	t_background_param	bp;

	pthread_mutex_lock(cub->player_data.player_lock);
	bp.player = cub->player_data.player;
	pthread_mutex_unlock(cub->player_data.player_lock);
	bp.ray_left = fvector_sub(bp.player.rotation, cub->player_data.camera);
	bp.ray_right = fvector_add(bp.player.rotation, cub->player_data.camera);
	draw_floor(cub, bp);
	draw_ceil(cub, bp);
}

static void	draw_floor(t_cub *cub, t_background_param bp)
{
	bp.sprite = cub->mlx_data->texture_sprite[FLOOR_ID];
	bp.screen.y = WIN_HEIGHT / 2;
	while (bp.screen.y < WIN_HEIGHT)
	{
		bp.row_dist = (WIN_HEIGHT * 0.5f)
			/ (bp.screen.y - WIN_HEIGHT / 2.f);
		draw_background_row(cub, bp);
		bp.screen.y++;
	}
}

static void	draw_ceil(t_cub *cub, t_background_param bp)
{
	bp.sprite = cub->mlx_data->texture_sprite[CEILING_ID];
	bp.screen.y = 0;
	while (bp.screen.y < WIN_HEIGHT / 2)
	{
		bp.row_dist = (WIN_HEIGHT * 0.5f)
			/ (WIN_HEIGHT / 2.f - bp.screen.y);
		draw_background_row(cub, bp);
		bp.screen.y++;
	}
}

static void	draw_background_row(t_cub *cub, t_background_param bp)
{
	bp.step = fvector_sub(bp.ray_right, bp.ray_left);
	bp.step = fvector_div(fvector_mul(bp.step, bp.row_dist), WIN_WIDTH);
	bp.cell.x = bp.player.pos.x + bp.row_dist * bp.ray_left.x;
	bp.cell.y = bp.player.pos.y + bp.row_dist * bp.ray_left.y;
	bp.screen.x = 0;
	while (bp.screen.x < WIN_WIDTH)
	{
		bp.texture.x = (int)(bp.sprite.width * (bp.cell.x - (int)bp.cell.x))
			& (bp.sprite.width - 1);
		bp.texture.y = (int)(bp.sprite.height * (bp.cell.y - (int)bp.cell.y))
			& (bp.sprite.height - 1);
		bp.cell = fvector_add(bp.cell, bp.step);
		bp.color = *(int *)(bp.sprite.img_data.addr
				+ bp.texture.x * bp.sprite.img_data.bit_ratio
				+ bp.texture.y * bp.sprite.img_data.line_length);
		mlx_put_pixel(&cub->mlx_data->img_data, bp.screen.x, bp.screen.y, bp.color);
		//put point
		bp.screen.x++;
	}
}
