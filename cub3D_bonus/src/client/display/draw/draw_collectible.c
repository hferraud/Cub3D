/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_collectible.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:46:00 by ethan             #+#    #+#             */
/*   Updated: 2023/04/05 17:46:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "collectible.h"
#include "cub.h"

static int		draw_collectible(t_cub *cub, t_sprite sprite, float dist);
static float	dist_calculate(t_player player, t_fvector pos);

int	draw_collectible_list(t_cub *cub, t_collectible *head)
{
	t_sprite	sprite;
	float		dist;

	while (head)
	{
		sprite = cub->mlx_data->collectible_sprite[head->id];
		dist = dist_calculate(cub->player, head->pos);
		draw_collectible(cub, sprite, dist);
		head = head->next;
	}
}

static int	draw_collectible(t_cub *cub, t_sprite sprite, float dist)
{
	
}

static float	dist_calculate(t_player player, t_fvector pos)
{
	t_fvector	vect;

	vect.x = fabsf(player.pos.x - pos.x);
	vect.y = fabsf(player.pos.x - pos.x);
	return (sqrtf(vect.x * vect.x + vect.y * vect.y));
}