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

static void	*draw_floor(void *arg);
static void	*draw_ceil(void *arg);
static void	draw_background_row(t_cub *cub, t_background_param bp);

void	draw_background(t_cub *cub)
{
	t_background		background;
	pthread_t			thread;
	bool				thread_create_failed;

	background.cub = cub;
	pthread_mutex_lock(cub->player_data.player_lock);
	background.bp.player = cub->player_data.player;
	pthread_mutex_unlock(cub->player_data.player_lock);
	background.bp.ray_right = fvector_sub(background.bp.player.rotation,
			cub->player_data.camera);
	background.bp.ray_left = fvector_add(background.bp.player.rotation,
			cub->player_data.camera);
	thread_create_failed
		= pthread_create(&thread, NULL, &draw_floor, &background) != 0;
	if (thread_create_failed)
		draw_floor(&background);
	draw_ceil(&background);
	if (thread_create_failed == false)
		pthread_join(thread, NULL);
}

static void	*draw_floor(void *arg)
{
	t_cub				*cub;
	t_background_param	bp;

	cub = ((t_background *)arg)->cub;
	bp = ((t_background *)arg)->bp;
	bp.sprite = cub->mlx_data->texture_sprite[FLOOR_ID];
	bp.screen.y = WIN_HEIGHT / 2;
	while (bp.screen.y < WIN_HEIGHT)
	{
		bp.row_dist = (WIN_HEIGHT * 0.5f)
			/ (bp.screen.y - WIN_HEIGHT / 2.f);
		draw_background_row(cub, bp);
		bp.screen.y++;
	}
	return (NULL);
}

static void	*draw_ceil(void *arg)
{
	t_cub				*cub;
	t_background_param	bp;

	cub = ((t_background *)arg)->cub;
	bp = ((t_background *)arg)->bp;
	bp.sprite = cub->mlx_data->texture_sprite[CEILING_ID];
	bp.screen.y = WIN_HEIGHT / 2;
	while (bp.screen.y--)
	{
		bp.row_dist = (WIN_HEIGHT * 0.5f)
			/ (WIN_HEIGHT / 2.f - bp.screen.y);
		draw_background_row(cub, bp);
	}
	return (NULL);
}

static void	draw_background_row(t_cub *cub, t_background_param bp)
{
	unsigned int		*mlx_img;
	const unsigned int	screen_y
		= bp.screen.y * ((cub->mlx_data->img_data.line_length) >> 2);

	mlx_img = (unsigned int *)cub->mlx_data->img_data.addr;
	bp.step = fvector_sub(bp.ray_right, bp.ray_left);
	bp.step = fvector_div(fvector_mul(bp.step, bp.row_dist), WIN_WIDTH);
	bp.cell.x = bp.player.pos.x + bp.row_dist * bp.ray_left.x;
	bp.cell.y = bp.player.pos.y + bp.row_dist * bp.ray_left.y;
	bp.screen.x = WIN_WIDTH;
	while (bp.screen.x-- > 0)
	{
		bp.texture.x = (int)(bp.sprite.width * (bp.cell.x - (int)bp.cell.x))
			& (bp.sprite.width - 1);
		bp.texture.y = (int)(bp.sprite.height * (bp.cell.y - (int)bp.cell.y))
			& (bp.sprite.height - 1);
		bp.cell = fvector_add(bp.cell, bp.step);
		bp.color = *(int *)(bp.sprite.img_data.addr
				+ bp.texture.x * bp.sprite.img_data.bit_ratio
				+ bp.texture.y * bp.sprite.img_data.line_length);
		mlx_img[screen_y + bp.screen.x] = bp.color;
	}
}
