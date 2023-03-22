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

static t_ray	ray_init(t_cub *cub, t_fvector ray_dir);
//static void		ray_next_chunk(t_ray *ray);

t_ray   ray_cast(t_cub *cub, t_fvector ray_dir)
{
	t_ray		ray;
	t_vector	map_index;

	ray = ray_init(cub, ray_dir);
	map_index = vector_init((int) cub->player->pos.x, (int) cub->player->pos.y);
	while (cub->map->map[map_index.y][map_index.x] == FLOOR)
	{
//		ray_next_chunk(&ray);
		if (ray.chunk_length.x < ray.chunk_length.y)
		{
			ray.ray.x += ray.chunk_length.x;
			map_index.x += ray.step.x;
		}
		else
		{
			ray.ray.y += ray.chunk_length.y;
			map_index.y += ray.step.y;
		}
	}
	if (ray.chunk_length.x < ray.chunk_length.y)
	{
		if (ray.step.x == 1)
			ray.wall_face = WEST;
		else
			ray.wall_face = EAST;
	}
	else
	{
		if (ray.step.y == 1)
			ray.wall_face = NORTH;
		else
			ray.wall_face = SOUTH;
	}
	if (ray.wall_face == WEST || ray.wall_face == EAST)
		ray.length = ray.ray.x - ray.chunk_length.x;
	else
		ray.length = ray.ray.y - ray.chunk_length.y;
	printf("length: %f\n", ray.length);
	return (ray);
}

//static void	ray_next_chunk(t_ray *ray)
//{
//	if (ray->step.x == 1)
//		ray->chunk_length.x = (floorf(ray->pos.x + 1) - ray->pos.x) * ray->unit_step.x;
//	else
//		ray->chunk_length.x = (ray->pos.x - ceilf(ray->pos.x - 1)) * ray->unit_step.x;
//	if (ray->step.y == 1)
//		ray->chunk_length.y = (floorf(ray->pos.y + 1) - ray->pos.y) * ray->unit_step.y;
//	else
//		ray->chunk_length.y = (ray->pos.y - ceilf(ray->pos.y - 1)) * ray->unit_step.y;
//}

static t_ray	ray_init(t_cub *cub, t_fvector ray_dir)
{
	t_ray	ray;

	ray.pos = cub->player->pos;
	ray.unit_step.x = fabsf(1 / ray_dir.x);
	ray.unit_step.y = fabsf(1 / ray_dir.y);
	ray.ray = fvector_init(0, 0);
	if (ray_dir.x > 0)
	{
		ray.step.x = 1;
		ray.chunk_length.x = ((int) ray.pos.x + 1 - ray.pos.x) * ray.unit_step.x;
	}
	else
	{
		ray.step.x = -1;
		ray.chunk_length.x = (ray.pos.x - (int) ray.pos.x) * ray.unit_step.x;
	}
	if (ray_dir.y > 0)
	{
		ray.step.y = 1;
		ray.chunk_length.y = ((int) ray.pos.y + 1 - ray.pos.y) * ray.unit_step.y;
	}
	else
	{
		ray.step.y = -1;
		ray.chunk_length.y = ( ray.pos.y - (int) ray.pos.y) * ray.unit_step.y;
	}
	return (ray);
}
