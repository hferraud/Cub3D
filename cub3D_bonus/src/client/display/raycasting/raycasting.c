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

t_ray	ray_cast(t_cub *cub, t_fvector ray_dir)
{
	t_ray		ray;
	t_vector	map_index;

	ray = ray_init(cub, ray_dir);
	map_index = vector_init((int) cub->player.pos.x, (int) cub->player.pos.y);
	while (cub->map.map[map_index.y][map_index.x] != WALL
		&& cub->map.map[map_index.y][map_index.x] != DOOR_CLOSE)
	{
		if (is_collectible(cub->map.map[map_index.y][map_index.x]))
		{
			if (collectible_append(&ray.collectible_hit,
					cub->map.map[map_index.y][map_index.x],
				fvector_init(map_index.x + 0.5, map_index.y + 0.5)) == -1)
			{
				collectible_clear(ray.collectible_hit);
				cub_exit(cub);
			}
		}
		if (ray.ray.x < ray.ray.y)
		{
			map_index.x += ray.step.x;
			ray.ray.x += ray.unit_step.x;
			if (ray.step.x == 1)
				ray.wall_face = WEST;
			else
				ray.wall_face = EAST;
		}
		else
		{
			map_index.y += ray.step.y;
			ray.ray.y += ray.unit_step.y;
			if (ray.step.y == 1)
				ray.wall_face = NORTH;
			else
				ray.wall_face = SOUTH;
		}
	}
	if (ray.wall_face == WEST || ray.wall_face == EAST)
	{
		ray.length = ray.ray.x - ray.unit_step.x;
		ray.pos.y = cub->player.pos.y + ray.length * ray_dir.y;
	}
	else
	{
		ray.length = ray.ray.y - ray.unit_step.y;
		ray.pos.x = cub->player.pos.x + ray.length * ray_dir.x;
	}
	return (ray);
}

static t_ray	ray_init(t_cub *cub, t_fvector ray_dir)
{
	t_ray	ray;

	ray.pos = cub->player.pos;
	ray.unit_step.x = fabsf(1 / ray_dir.x);
	ray.unit_step.y = fabsf(1 / ray_dir.y);
	ray.ray = fvector_init(0, 0);
	ray.collectible_hit = NULL;
	if (ray_dir.x > 0)
	{
		ray.step.x = 1;
		ray.ray.x = ((int) ray.pos.x + 1 - ray.pos.x) * ray.unit_step.x;
	}
	else
	{
		ray.step.x = -1;
		ray.ray.x = (ray.pos.x - (int) ray.pos.x) * ray.unit_step.x;
	}
	if (ray_dir.y > 0)
	{
		ray.step.y = 1;
		ray.ray.y = ((int) ray.pos.y + 1 - ray.pos.y) * ray.unit_step.y;
	}
	else
	{
		ray.step.y = -1;
		ray.ray.y = (ray.pos.y - (int) ray.pos.y) * ray.unit_step.y;
	}
	return (ray);
}

static int ray_add_collectible(char **map, t_ray ray, t_vector map_index)
{
	t_fvector	pos;
	if (!is_collectible(map[map_index.y][map_index.x]))
		return (0);
	collectible_append(&ray.collectible_hit, map[map_index.y][map_index.x], )
}
