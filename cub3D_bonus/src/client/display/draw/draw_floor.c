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

void	draw_floor(t_cub *cub)
{
	t_player	player;
	t_vector	screen;
	t_vector	texture;
	t_fvector	floor;
	t_fvector	ray_dir_left;
	t_fvector	ray_dir_right;
	t_fvector	step;
	t_sprite	sprite;
	float		floor_dist;
	int 		color;

	sprite = cub->mlx_data->texture_sprite[FLOOR_ID];
	pthread_mutex_lock(cub->player_data.player_lock);
	player = cub->player_data.player;
	pthread_mutex_unlock(cub->player_data.player_lock);
	ray_dir_left = fvector_sub(player.rotation, cub->player_data.camera);
	ray_dir_right = fvector_add(player.rotation, cub->player_data.camera);
	screen.y = WIN_HEIGHT / 2;
	while (screen.y < WIN_HEIGHT)
	{
		floor_dist = (WIN_HEIGHT * 0.5f) / (float)(screen.y - WIN_HEIGHT / 2.f);
		step.x = (floor_dist * (ray_dir_right.x - ray_dir_left.x) / WIN_WIDTH);
		step.y = (floor_dist * (ray_dir_right.y - ray_dir_left.y) / WIN_WIDTH);
		floor.x = cub->player_data.player.pos.x + floor_dist * ray_dir_left.x;
		floor.y = cub->player_data.player.pos.y + floor_dist * ray_dir_left.y;
		screen.x = 0;
		while (screen.x < WIN_WIDTH)
		{
			texture.x = (int)(sprite.width * (floor.x - (int)floor.x));
			texture.y = (int)(sprite.height * (floor.y - (int)floor.y));
			floor = fvector_add(floor, step);
			color = *(int *)(sprite.img_data.addr
					+ texture.x * sprite.img_data.bit_ratio
					+ texture.y * sprite.img_data.line_length);
			mlx_put_pixel(&cub->mlx_data->img_data, screen.x, screen.y, color);
			screen.x++;
		}
		screen.y++;
	}
}

void	draw_ceil(t_cub *cub)
{
	t_player	player;
	t_vector	screen;
	t_vector	texture;
	t_fvector	floor;
	t_fvector	ray_dir_left;
	t_fvector	ray_dir_right;
	t_fvector	step;
	t_sprite	sprite;
	float		floor_dist;
	int 		color;

	sprite = cub->mlx_data->texture_sprite[CEILING_ID];
	pthread_mutex_lock(cub->player_data.player_lock);
	player = cub->player_data.player;
	pthread_mutex_unlock(cub->player_data.player_lock);
	ray_dir_left = fvector_sub(player.rotation, cub->player_data.camera);
	ray_dir_right = fvector_add(player.rotation, cub->player_data.camera);
	screen.y = 0;
	while (screen.y < WIN_HEIGHT / 2)
	{
		floor_dist = (WIN_HEIGHT * 0.5f) / (float)(WIN_HEIGHT / 2.f - screen.y);
		step.x = (floor_dist * (ray_dir_right.x - ray_dir_left.x) / WIN_WIDTH);
		step.y = (floor_dist * (ray_dir_right.y - ray_dir_left.y) / WIN_WIDTH);
		floor.x = player.pos.x + floor_dist * ray_dir_left.x;
		floor.y = player.pos.y + floor_dist * ray_dir_left.y;
		screen.x = 0;
		while (screen.x < WIN_WIDTH)
		{
			texture.x = (int)(sprite.width * (floor.x - (int)floor.x)) & (sprite.width - 1);
			texture.y = (int)(sprite.height * (floor.y - (int)floor.y)) & (sprite.height - 1);
			floor = fvector_add(floor, step);
			color = *(int *)(sprite.img_data.addr
					+ texture.x * sprite.img_data.bit_ratio
					+ texture.y * sprite.img_data.line_length);
			mlx_put_pixel(&cub->mlx_data->img_data, screen.x, screen.y, color);
			screen.x++;
		}
		screen.y++;
	}
}
