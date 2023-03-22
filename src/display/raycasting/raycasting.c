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
#include "player.h"

static t_ray	ray_init(t_cub *cub, float theta);
static float	init_ray_theta(float theta);
static void		ray_next_chunk(t_ray *ray);

t_ray   ray_cast(t_cub *cub, float theta)
{
	t_ray	ray;
	char	**map;
	t_point	map_index;

	theta = init_ray_theta(theta);
	ray = ray_init(cub, theta);
	map = cub->map->map;
	map_index.x = (int) cub->player->pos.x;
	map_index.y = (int) cub->player->pos.y;
	while (map[map_index.y][map_index.x] == FLOOR)
	{
		ray_next_chunk(&ray);
		if (ray.ray_chunk_length.x < ray.ray_chunk_length.y)
		{
			if (ray.step.x == -1)
				ray.ray_pos.x = ceilf(ray.ray_pos.x - 1);
			else
				ray.ray_pos.x = floorf(ray.ray_pos.x + 1);
			ray.ray_pos.y += (sinf(theta) * ray.ray_chunk_length.x);
			ray.ray_length += ray.ray_chunk_length.x;
			if (ray.step.x == 1)
				ray.wall_face = WEST;
			else
				ray.wall_face = EAST;
			map_index.x += ray.step.x;
		}
		else
		{
			if (ray.step.y == -1)
				ray.ray_pos.y = ceilf(ray.ray_pos.y - 1);
			else
				ray.ray_pos.y = floorf(ray.ray_pos.y + 1);
			ray.ray_pos.x += (cosf(theta) * ray.ray_chunk_length.y);
			ray.ray_length += ray.ray_chunk_length.y;
			if (ray.step.y == 1)
				ray.wall_face = NORTH;
			else
				ray.wall_face = SOUTH;
			map_index.y += ray.step.y;
		}
	}
	ray.ray_length *= cosf(theta - cub->player->rotation);
	return (ray);
}

static void	ray_next_chunk(t_ray *ray)
{
	if (ray->step.x == 1)
		ray->ray_chunk_length.x = (floorf(ray->ray_pos.x + 1) - ray->ray_pos.x) * ray->ray_unit_step.x;
	else
		ray->ray_chunk_length.x = (ray->ray_pos.x - ceilf(ray->ray_pos.x - 1)) * ray->ray_unit_step.x;
	if (ray->step.y == 1)
		ray->ray_chunk_length.y = (floorf(ray->ray_pos.y + 1) - ray->ray_pos.y) * ray->ray_unit_step.y;
	else
		ray->ray_chunk_length.y = (ray->ray_pos.y - ceilf(ray->ray_pos.y - 1)) * ray->ray_unit_step.y;
}

static t_ray	ray_init(t_cub *cub, float theta)
{
	t_ray	ray;
	t_pos	delta;


	ray.ray_pos = cub->player->pos;
	delta.x = cosf(theta);
	delta.y = sinf(theta);
	ray.ray_unit_step.x = 1.0f / fabsf(delta.x);
	ray.ray_unit_step.y = 1.0f / fabsf(delta.y);
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