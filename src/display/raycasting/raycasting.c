/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 07:29:00 by edelage           #+#    #+#             */
/*   Updated: 2023/03/15 07:29:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "raycasting.h"

static t_ray	ray_init(t_cub *cub, float theta);
static float	init_ray_theta(float theta);
static void		ray_next_chunk(t_ray *ray);

float	ray_cast(t_cub *cub, float theta)
{
	t_ray	ray;
	char	**map;
	t_point	map_index;

	theta = init_ray_theta(theta);
	ray = ray_init(cub, theta);
	map = cub->map->map;
	map_index.x = (int) cub->player->pos.x;
	map_index.y = (int) cub->player->pos.y;
	if (ray.ray_chunk_length.x < ray.ray_chunk_length.y)
	{
		ray.ray_length += ray.ray_chunk_length.x;
		map_index.x += ray.step.x;
	}
	else
	{
		ray.ray_length += ray.ray_chunk_length.y;
		map_index.y += ray.step.y;
	}
	while (map[map_index.y][map_index.x] == FLOOR)
	{
		ray.ray_pos.x += (ray.ray_chunk_length.x * ray.step.x);
		ray.ray_pos.y += (ray.ray_chunk_length.y * ray.step.y);
		ray_next_chunk(&ray);
		if (ray.ray_chunk_length.x < ray.ray_chunk_length.y)
		{
			map_index.x += ray.step.x;
			if (ray.step.x== -1)
				ray.ray_pos.x += (int) ray.ray_pos.x;
			else
				ray.ray_pos.x += (int) (ray.ray_pos.x + 1);
			ray.ray_pos.y += (cosf(theta) * ray.ray_chunk_length.x * ray.step.y);
			if (map[map_index.y][map_index.x] == FLOOR)
				ray.ray_length += ray.ray_chunk_length.x;
		}
		else
		{
			map_index.y += ray.step.y;
			ray.ray_pos.x += (sinf(theta) * ray.ray_chunk_length.y * ray.step.x);
			if (ray.step.y == -1)
				ray.ray_pos.y += (int) ray.ray_pos.y;
			else
				ray.ray_pos.y += (int) (ray.ray_pos.y + 1);
			if (map[map_index.y][map_index.x] == FLOOR)
				ray.ray_length += ray.ray_chunk_length.y;
		}
	}
	return (ray.ray_length);
}

static void	ray_next_chunk(t_ray *ray)
{
	if (ray->step.x == 1)
		ray->ray_chunk_length.x = ((int)(ray->ray_pos.x) + 1 - ray->ray_pos.x) * ray->ray_unit_step.x;
	else
		ray->ray_chunk_length.x = (ray->ray_pos.x - (int) ray->ray_pos.x) * ray->ray_unit_step.x;
	if (ray->step.y == 1)
		ray->ray_chunk_length.y = ((int)(ray->ray_pos.y) + 1 - ray->ray_pos.y) * ray->ray_unit_step.y;
	else
		ray->ray_chunk_length.y = (ray->ray_pos.y - (int) ray->ray_pos.y) * ray->ray_unit_step.y;
}

static t_ray	ray_init(t_cub *cub, float theta)
{
	t_ray	ray;
	t_pos	delta;


	ray.ray_pos = cub->player->pos;
	delta.x = cosf(theta);
	delta.y = sinf(theta);
	ray.ray_unit_step.x = sqrtf(1 + (delta.y * delta.y) / (delta.x * delta.x));
	ray.ray_unit_step.y = sqrtf(1 + (delta.x * delta.x) / (delta.y * delta.y));
	ray.ray_length = 0;
	if (theta < M_PI_2 || theta > 3 * M_PI_2)
	{
		ray.step.x = 1;
		ray.ray_chunk_length.x = ((int) ray.ray_pos.x + 1 - ray.ray_pos.x) * ray.ray_unit_step.x;
	}
	else
	{
		ray.step.x = -1;
		ray.ray_chunk_length.x = (ray.ray_pos.x - (int) ray.ray_pos.x) * ray.ray_unit_step.x;
	}
	if (theta < M_PI)
	{
		ray.step.y = 1;
		ray.ray_chunk_length.y = ((int) ray.ray_pos.y + 1 - ray.ray_pos.y) * ray.ray_unit_step.y;
	}
	else
	{
		ray.step.y = -1;
		ray.ray_chunk_length.y = ( ray.ray_pos.y - (int) ray.ray_pos.y) * ray.ray_unit_step.y;
	}
	return (ray);
}

static float	init_ray_theta(float theta)
{
	if (theta > 2 * M_PI)
		while (theta > 2 * M_PI)
			theta -= 2.0 * M_PI;
	else if (theta < 0)
		while (theta < 0)
			theta += 2 * M_PI;
	return (theta);
}