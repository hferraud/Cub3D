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

float	ray_cast(t_cub *cub, float theta)
{
	t_ray	ray;
	char	**map;
	t_point	map_index;

	ray = ray_init(cub, theta);
	map = cub->map->map;
	map_index.x = (int) cub->player->pos.x;
	map_index.y = (int) cub->player->pos.y;
	if (ray.ray_chunk_length.x < ray.ray_chunk_length.y)
	{
		ray.ray_length = ray.ray_chunk_length.x;
		if (map[map_index.y][map_index.x + ray.step.x] == WALL)
			return (ray.ray_length);
	}
	else
	{
		printf("%d %d\n", ray.step.x, ray.step.y);
		ray.ray_length = ray.ray_chunk_length.y;
		if (map[map_index.y + ray.step.y][map_index.x] == WALL)
			return (ray.ray_length);
	}
	return (0);
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
	if (theta < M_PI_2 || theta > 3 * M_PI_2)
	{
		ray.step.x = 1;
		ray.ray_chunk_length.x = fabsf(((int) ray.ray_pos.x + 1 - ray.ray_pos.x) * ray.ray_unit_step.x);
	}
	else
	{
		ray.step.x = -1;
		ray.ray_chunk_length.x = fabsf(((int) ray.ray_pos.x - ray.ray_pos.x) * ray.ray_unit_step.x);
	}
	if (theta < M_PI)
	{
		ray.step.y = 1;
		ray.ray_chunk_length.y = fabsf(((int) ray.ray_pos.y + 1 - ray.ray_pos.y) * ray.ray_unit_step.y);
	}
	else
	{
		ray.step.y = -1;
		ray.ray_chunk_length.y = fabsf(((int) ray.ray_pos.y - ray.ray_pos.y) * ray.ray_unit_step.y);
	}
	return (ray);
}
