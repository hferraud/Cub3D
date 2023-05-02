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
static float	get_abs_distance(t_player player, t_fvector pos);

int	draw_collectible_list(t_cub *cub, t_collectible_list *head)
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

static t_fvector	get_vect_distance(t_player player, t_fvector pos)
{
	return (fvector_sub(pos, player.pos));
}

static float	get_abs_distance(t_player player, t_fvector pos)
{
	t_fvector	vect;

	vect.x = fabsf(player.pos.x - pos.x);
	vect.y = fabsf(player.pos.x - pos.x);
	return (sqrtf(vect.x * vect.x + vect.y * vect.y));
}