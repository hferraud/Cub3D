/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_collectible.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:46:00 by ethan             #+#    #+#             */
/*   Updated: 2023/04/05 17:46:00 by ethan            ###   ########lyon.fr   */
/*  sd                                                                         */
/* ************************************************************************** */
#include <stdbool.h>
#include "collectible.h"
#include "cub.h"

static void		draw_collectible_sprite(t_cub *cub, t_collectible collectible);
static void		collectible_set_dist(t_cub *cub);
static void		sort_collectible(t_cub *cub);

void	draw_collectible(t_cub *cub)
{
	size_t	i;

	collectible_set_dist(cub);
	sort_collectible(cub);
	i = 0;
	while (i < cub->map.collectible_data.size)
	{
		draw_collectible_sprite(cub, cub->map.collectible_data.collectible[i]);
		i++;
	}
}

static void	draw_collectible_sprite(t_cub *cub, t_collectible collectible)
{
	t_fvector	sprite;
//	t_fvector	draw_start;
//	t_fvector	draw_end;
	float		sprite_screen_x;
	float		height;
	float		inverse_det;

	inverse_det = 1.f / (cub->player.camera.x * cub->player.rotation.y
			- cub->player.rotation.x * cub->player.camera.y);
	sprite.x = inverse_det * (cub->player.rotation.y * collectible.relative_pos.x
			- cub->player.rotation.x * collectible.relative_pos.y);
	sprite.y = inverse_det * (-cub->player.camera.y * collectible.relative_pos.x
			+ cub->player.camera.x * collectible.relative_pos.y);
	sprite_screen_x = (int)(WIN_HEIGHT / 2 * (1 + sprite.x / sprite.y));
	height = abs(((int) (WIN_HEIGHT / sprite.y)));
	printf("screen_x: %f height: %f dist: %f\n", sprite_screen_x, height, sprite.y);
	//printf("sprite %f %f\n", sprite.x, sprite.y);
}

/**
 * @brief Set the distance from the player of all collectibles
 */
static void collectible_set_dist(t_cub *cub)
{
	size_t			i;
	t_collectible	*collectibles;

	collectibles = cub->map.collectible_data.collectible;
	i = 0;
	while (i < cub->map.collectible_data.size)
	{
		collectibles[i].relative_pos = fvector_sub(cub->player.pos, collectibles->pos);
		collectibles[i].dist = collectibles->relative_pos.x * collectibles->relative_pos.x
				+ collectibles->relative_pos.y * collectibles->relative_pos.y;
		i++;
	}
}

/**
 * @brief Sort all collectibles from the nearest to the further away of the player
 */
static void	sort_collectible(t_cub *cub)
{
	t_collectible	*collectible;
	t_collectible	tmp;
	bool			flag;
	size_t			i;

	collectible = cub->map.collectible_data.collectible;
	flag = true;
	while (flag)
	{
		flag = false;
		i = 1;
		while (i < cub->map.collectible_data.size)
		{
			if (collectible[i].dist > collectible[i - 1].dist)
			{
				flag = true;
				tmp = collectible[i];
				collectible[i] = collectible[i - 1];
				collectible[i - 1] = tmp;
			}
			i++;
		}
	}
}
